// PerishableProduct.cpp
#include "PerishableProduct.h"
#include <iostream>

PerishableProduct::PerishableProduct(int id, const std::string& name, double basePrice, int quantity,
    const std::string& expirationDate, int storageTemperature,
    const std::string& storageInstructions, bool needsRefrigeration)
    : FoodProduct(id, name, basePrice, quantity, expirationDate, true, storageTemperature),
    storageInstructions(storageInstructions),
    needsRefrigeration(needsRefrigeration) {
}

PerishableProduct::~PerishableProduct() {}

void PerishableProduct::setStorageInstructions(const std::string& instructions) {
    storageInstructions = instructions;
}

void PerishableProduct::setNeedsRefrigeration(bool needs) {
    needsRefrigeration = needs;
}

std::string PerishableProduct::getStorageInstructions() const {
    return storageInstructions;
}

bool PerishableProduct::getNeedsRefrigeration() const {
    return needsRefrigeration;
}

double PerishableProduct::getFinalPrice() const {
    double price = FoodProduct::getFinalPrice();

    if (price == 0.0) return 0.0;

    if (needsRefrigeration) {
        price *= 1.2;
    }

    return price;
}

std::string PerishableProduct::getType() const {
    return "PerishableProduct";
}

void PerishableProduct::printInfo() const {
    FoodProduct::printInfo();
    std::cout << "Instrukciya po hraneniyu: " << storageInstructions << std::endl;
    std::cout << "Nuzhdaetsya v holodilnike: " << (needsRefrigeration ? "Da" : "Net") << std::endl;
}