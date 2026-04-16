// Product.cpp
#include "Product.h"

Product::Product(int id, const std::string& name, double basePrice, int quantity)
    : id(id), name(name), basePrice(basePrice), quantity(quantity) {
}

Product::~Product() {}

void Product::set_id(int id) {
    this->id = id;
}

void Product::set_name(const std::string& name) {
    this->name = name;
}

void Product::set_basePrice(double basePrice) {
    this->basePrice = basePrice;
}

void Product::set_quantity(int quantity) {
    this->quantity = quantity;
}

int Product::get_id() const {
    return id;
}

std::string Product::get_name() const {
    return name;
}

double Product::get_basePrice() const {
    return basePrice;
}

int Product::get_quantity() const {
    return quantity;
}