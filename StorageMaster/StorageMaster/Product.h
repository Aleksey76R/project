// Product.h
#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private:
    int id;
    std::string name;
    double basePrice;
    int quantity;

public:
    Product(int id, const std::string& name, double basePrice, int quantity);
    virtual ~Product();

    void set_id(int id);
    void set_name(const std::string& name);
    void set_basePrice(double basePrice);
    void set_quantity(int quantity);

    int get_id() const;
    std::string get_name() const;
    double get_basePrice() const;
    int get_quantity() const;

    virtual double getFinalPrice() const = 0;
    virtual std::string getType() const = 0;
    virtual void printInfo() const = 0;
};

#endif