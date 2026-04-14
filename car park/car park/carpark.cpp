#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

class Vehicle {
private:
    string model;
    int year;
    float speed;
protected:
    int id;
    static int nextId;
public:
    Vehicle(string model, int year) {
        this->model = model;
        this->year = year;
        this->speed = 0;
        this->id = nextId++;
    }
    ~Vehicle() {}

    void set_speed(float speed) {
        if (speed <= 250 && speed >= 0)
            this->speed = speed;
    }

    float get_speed() const { return speed; }
    int get_id() const { return id; }
    string get_model() const { return model; }
    int get_year() const { return year; }

    virtual void displayInfo() const = 0;
    virtual void accelerate(float delta) {
        if (delta > 0) {
            speed += delta;
            if (speed > 250) speed = 250;
        }
    }

    virtual void brake(float delta) {
        if (delta > 0) {
            speed -= delta;
            if (speed < 0) speed = 0;
        }
    }
};

int Vehicle::nextId = 1000;

class Car : public Vehicle {
private:
    int doorCount;
    string bodyType;
public:
    Car(string model, int year, int doorCount, string bodyType) : Vehicle(model, year) {
        this->doorCount = doorCount;
        this->bodyType = bodyType;
    }
    ~Car() {}

    void displayInfo() const override {
        cout << get_model();
        cout << get_year();
        cout << bodyType;
        cout << doorCount;
        cout << get_speed();
    }

    void accelerate(float delta) override {
        if (delta > 0) {
            float newSpeed = get_speed() + min(delta, 15.0f);
            set_speed(newSpeed);
        }
    }

    int getDoorCount() const { return doorCount; }
    string getBodyType() const { return bodyType; }
};

class Truck : public Vehicle {
private:
    float loadCapacity;
    int axlesCount;
    bool flagTons;
public:
    Truck(string model, int year, float loadCapacity, int axlesCount) : Vehicle(model, year) {
        this->axlesCount = axlesCount;
        this->loadCapacity = loadCapacity;
        this->flagTons = false;
    }

    ~Truck() {}

    void displayInfo() const override {
        cout << get_model();
        cout << get_year();
        cout << get_speed();
        cout << loadCapacity;
        cout << axlesCount;
    }

    void accelerate(float delta) override {
        if (delta > 0) {
            float newSpeed = get_speed() + min(delta, 5.0f);

            if (flagTons && newSpeed > 70)
                newSpeed = 70;
            if (newSpeed > 250)
                newSpeed = 250;

            set_speed(newSpeed);
        }
    }

    bool loadCargo(float tons) {
        if (tons <= loadCapacity) {
            flagTons = false;
            return true;
        }
        else {
            flagTons = true;
            return false;
        }
    }

    float getLoadCapacity() const { return loadCapacity; }
    int getAxlesCount() const { return axlesCount; }
};

class Motorcycle : public Vehicle {
private:
    bool hasSidecar;
    int engineVolume;
public:
    Motorcycle(string model, int year, int engineVolume, bool hasSidecar) : Vehicle(model, year) {
        this->hasSidecar = hasSidecar;
        this->engineVolume = engineVolume;
    }

    void displayInfo() const override {
        cout << get_speed();
        cout << engineVolume;
        cout << get_year();
    }

    ~Motorcycle() {}

    void accelerate(float delta) override {
        if (delta > 0) {
            float newSpeed = get_speed() + min(delta, 30.0f);
            if (newSpeed > 220)
                newSpeed = 220;
            set_speed(newSpeed);
        }
    }

    void set_hasSidecar(bool hasSidecar) {
        this->hasSidecar = hasSidecar;
    }

    int get_engineVolume() const { return engineVolume; }
    bool get_hasSidecar() const { return hasSidecar; }
};

class Fleet {
private:
    vector<Vehicle*> vehicles;

public:
    Fleet() {}

    ~Fleet() {
        for (Vehicle* v : vehicles) {
            delete v;
        }
        vehicles.clear();
    }

    void addVehicle(Vehicle* v) {
        if (v != nullptr) {
            vehicles.push_back(v);
            cout << v->get_id() << endl;
        }
    }

    bool removeVehicle(int id) {
        for (auto it = vehicles.begin(); it != vehicles.end(); ++it) {
            if ((*it)->get_id() == id) {
                delete* it;
                vehicles.erase(it);
                cout << id << endl;
                return true;
            }
        }
        cout << id << endl;
        return false;
    }

    void showAll() const {
        if (vehicles.empty()) {
            return;
        }

        cout << "\n========== FLEET LIST ==========" << endl;
        for (const auto& v : vehicles) {
            v->displayInfo();
        }
        cout << "================================\n" << endl;
    }

    void findByModel(const string& substr) const {
        bool found = false;
        cout << substr << endl;

        for (const auto& v : vehicles) {
            if (v->get_model().find(substr) != string::npos) {
                v->displayInfo();
                found = true;
            }
        }

        if (!found) {
            cout << substr << endl;
        }
    }

    Vehicle* findById(int id) const {
        for (auto& v : vehicles) {
            if (v->get_id() == id) {
                return v;
            }
        }
        return nullptr;
    }

    bool accelerateVehicle(int id, float delta) {
        Vehicle* v = findById(id);
        if (v != nullptr) {
            v->accelerate(delta);
            cout << id << delta
                << ". New speed: " << v->get_speed() << " km/h" << endl;
            return true;
        }
        cout << "Vehicle ID " << id << " not found!" << endl;
        return false;
    }

    bool brakeVehicle(int id, float delta) {
        Vehicle* v = findById(id);
        if (v != nullptr) {
            v->brake(delta);
            cout << "Vehicle ID " << id << " braked by " << delta
                << ". New speed: " << v->get_speed() << " km/h" << endl;
            return true;
        }
        cout << "Vehicle ID " << id << " not found!" << endl;
        return false;
    }

    bool loadCargoToTruck(int id, float tons) {
        Vehicle* v = findById(id);
        if (v == nullptr) {
            cout << "Vehicle not found!" << endl;
            return false;
        }

        Truck* truck = dynamic_cast<Truck*>(v);
        if (truck != nullptr) {
            return truck->loadCargo(tons);
        }
        else {
            cout << "Vehicle ID " << id << " is not a truck!" << endl;
            return false;
        }
    }

    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Cannot open file for writing!" << endl;
            return;
        }

        file << vehicles.size() << endl;

        for (const auto& v : vehicles) {
            if (dynamic_cast<Car*>(v)) {
                file << "Car" << endl;
                Car* car = dynamic_cast<Car*>(v);
                file << car->get_id() << endl;
                file << car->get_model() << endl;
                file << car->get_year() << endl;
                file << car->get_speed() << endl;
                file << car->getDoorCount() << endl;
                file << car->getBodyType() << endl;
            }
            else if (dynamic_cast<Truck*>(v)) {
                file << "Truck" << endl;
                Truck* truck = dynamic_cast<Truck*>(v);
                file << truck->get_id() << endl;
                file << truck->get_model() << endl;
                file << truck->get_year() << endl;
                file << truck->get_speed() << endl;
                file << truck->getLoadCapacity() << endl;
                file << truck->getAxlesCount() << endl;
            }
            else if (dynamic_cast<Motorcycle*>(v)) {
                file << "Motorcycle" << endl;
                Motorcycle* bike = dynamic_cast<Motorcycle*>(v);
                file << bike->get_id() << endl;
                file << bike->get_model() << endl;
                file << bike->get_year() << endl;
                file << bike->get_speed() << endl;
                file << bike->get_engineVolume() << endl;
                file << bike->get_hasSidecar() << endl;
            }
        }

        file.close();
        cout << filename << endl;
    }

    int getCount() const {
        return vehicles.size();
    }
};

int main() {
    cout << "========== VEHICLE FLEET MANAGEMENT SYSTEM ==========\n" << endl;

    Fleet myFleet;

    cout << "1. Adding vehicles to fleet:" << endl;
    cout << "----------------------------------------" << endl;

    Car* car1 = new Car("Toyota Camry", 2020, 4, "Sedan");
    Car* car2 = new Car("BMW X5", 2022, 4, "SUV");
    Car* car3 = new Car("Tesla Model 3", 2023, 4, "Sedan");

    myFleet.addVehicle(car1);
    myFleet.addVehicle(car2);
    myFleet.addVehicle(car3);

    Truck* truck1 = new Truck("Volvo FH", 2021, 20.0f, 3);
    Truck* truck2 = new Truck("MAN TGX", 2020, 25.0f, 4);

    myFleet.addVehicle(truck1);
    myFleet.addVehicle(truck2);

    Motorcycle* bike1 = new Motorcycle("Yamaha R1", 2022, 998, false);
    Motorcycle* bike2 = new Motorcycle("Harley Davidson", 2021, 1200, true);

    myFleet.addVehicle(bike1);
    myFleet.addVehicle(bike2);

    cout << "\nTotal vehicles in fleet: " << myFleet.getCount() << endl;

    myFleet.showAll();

    cout << "\n2. Testing acceleration and braking:" << endl;
    cout << "----------------------------------------" << endl;

    myFleet.accelerateVehicle(1000, 30);
    myFleet.accelerateVehicle(1002, 50);
    myFleet.accelerateVehicle(1004, 20);
    myFleet.accelerateVehicle(1006, 60);

    cout << endl;
    myFleet.brakeVehicle(1000, 10);
    myFleet.brakeVehicle(1006, 30);

    cout << "\n3. Testing truck cargo loading:" << endl;
    cout << "----------------------------------------" << endl;

    myFleet.loadCargoToTruck(1004, 15.0f);
    myFleet.loadCargoToTruck(1004, 25.0f);
    myFleet.accelerateVehicle(1004, 50);

    cout << "\n4. Searching vehicles:" << endl;
    cout << "----------------------------------------" << endl;
    myFleet.findByModel("Toyota");
    myFleet.findByModel("BMW");

    cout << "\n5. Removing a vehicle:" << endl;
    cout << "----------------------------------------" << endl;
    myFleet.removeVehicle(1002);
    myFleet.showAll();

    cout << "\n6. Saving to file:" << endl;
    cout << "----------------------------------------" << endl;
    myFleet.saveToFile("fleet_data.txt");

    cout << "\n7. Additional tests:" << endl;
    cout << "----------------------------------------" << endl;

    cout << "Demonstrating polymorphism:" << endl;
    Vehicle* vehicles[] = { car1, truck1, bike1 };
    for (int i = 0; i < 3; i++) {
        cout << "Vehicle " << i + 1 << " type: ";
        vehicles[i]->displayInfo();
    }

    cout << "\n========== PROGRAM FINISHED ==========" << endl;

    return 0;
}