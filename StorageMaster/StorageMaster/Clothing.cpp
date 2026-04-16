// Clothing.cpp
#include "Clothing.h"
#include <iostream>
#include <iomanip>

Clothing::Clothing(int id, const std::string& name, double basePrice, int quantity,
    const std::string& size, const std::string& material, bool isLuxury)
    : Product(id, name, basePrice, quantity),
    size(size),
    material(material),
    isLuxury(isLuxury) {
}

Clothing::~Clothing() {}

void Clothing::set_size(const std::string& size) {
    this->size = size;
}

void Clothing::set_material(const std::string& material) {
    this->material = material;
}

void Clothing::setIsLuxury(bool isLuxury) {
    this->isLuxury = isLuxury;
}

std::string Clothing::get_size() const {
    return size;
}

std::string Clothing::get_material() const {
    return material;
}

bool Clothing::getIsLuxury() const {
    return isLuxury;
}

double Clothing::getFinalPrice() const {
    double price = get_basePrice();

    if (material == "koza") {
        price *= 0.7;
    }

    if (size == "XL" || size == "XXL") {
        price *= 0.9;
    }

    if (isLuxury) {
        price *= 1.5;
    }

    return price;
}

std::string Clothing::getType() const {
    return "Clothing";
}

void Clothing::printInfo() const {
    std::cout << "\n========================================" << std::endl;
    std::cout << "Tip: " << getType() << std::endl;
    std::cout << "ID: " << get_id() << std::endl;
    std::cout << "Nazvanie: " << get_name() << std::endl;
    std::cout << "Bazovaya cena: " << get_basePrice() << " rub" << std::endl;
    std::cout << "Itogovaya cena: " << getFinalPrice() << " rub" << std::endl;
    std::cout << "Kolichestvo: " << get_quantity() << " sht" << std::endl;
    std::cout << "Razmer: " << size << std::endl;
    std::cout << "Material: " << material << std::endl;
    std::cout << "Luxury: " << (isLuxury ? "Da" : "Net") << std::endl;
    std::cout << "========================================" << std::endl;
}