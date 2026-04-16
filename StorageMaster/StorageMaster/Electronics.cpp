#include "Electronics.h"
#include <iomanip>

Electronics::Electronics(int id, const std::string& name, double basePrice, int quantity,
    int warrantyMonths, bool hasBattery, bool isImported)
    : Product(id, name, basePrice, quantity),
    warrantyMonths(warrantyMonths),
    hasBattery(hasBattery),
    isImported(isImported) {
}


Electronics::~Electronics() {}

void Electronics::set_warrantyMonths(int months) {
    warrantyMonths = (months >= 0) ? months : 0;
}

void Electronics::set_hasBattery(bool hasBattery) {
    this->hasBattery = hasBattery;
}

void Electronics::set_isImported(bool isImported) {
    this->isImported = isImported;
}

int Electronics::get_warrantyMonths() const {
    return warrantyMonths;
}

bool Electronics::get_hasBattery() const {
    return hasBattery;
}

bool Electronics::get_isImported() const {
    return isImported;
}


double Electronics::calculateWarrantyCost() const {
    double cost = get_basePrice() * 0.05;
    return cost * (warrantyMonths / 12.0);
}

bool Electronics::needsSpecialDelivery() const {
    return hasBattery || isImported;
}

double Electronics::getFinalPrice() const {
    double price = get_basePrice();

    price *= 1.20;

    if (hasBattery) {
        price += 500;
    }

    if (isImported) {
        price *= 1.15;
    }

    if (warrantyMonths > 24) {
        price *= 0.95;
    }

    return static_cast<int>(price * 100) / 100.0;
}

std::string Electronics::getType() const {
    return "Electronics";
}

void Electronics::printInfo() const {
    std::cout << "          ELECTRONICS PRODUCT          " << std::endl;
    std::cout << std::endl;
    std::cout << "ID:          " << std::setw(27) << get_id() << std::endl;
    std::cout << "Название:    " << std::setw(27) << get_name() << std::endl;
    std::cout << "Базовая цена:" << std::setw(25) << get_basePrice() << std::endl;
    std::cout << "Итоговая:    " << std::setw(25) << getFinalPrice() << std::endl;
    std::cout << "Количество:  " << std::setw(27) << get_quantity() << std::endl;
    std::cout << "Гарантия:    " << std::setw(27) << warrantyMonths << std::endl;
    std::cout << "Батарея:     " << std::setw(27) << (hasBattery ? "Да" : "Нет") << std::endl;
    std::cout << "Импортный:   " << std::setw(27) << (isImported ? "Да" : "Нет") << std::endl;

    if (warrantyMonths > 24) {
        std::cout << "СКИДКА 5% за длительную гарантию!" << std::endl;
    }

}