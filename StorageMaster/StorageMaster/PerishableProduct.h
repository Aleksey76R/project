#pragma once
// PerishableProduct.h (3 уровень наследования)
#ifndef PERISHABLEPRODUCT_H
#define PERISHABLEPRODUCT_H

#include "FoodProduct.h"
#include <string>

class PerishableProduct : public FoodProduct {
private:
    std::string storageInstructions;
    bool needsRefrigeration;

public:
    PerishableProduct(int id, const std::string& name, double basePrice, int quantity,
        const std::string& expirationDate, int storageTemperature,
        const std::string& storageInstructions, bool needsRefrigeration);

    ~PerishableProduct();

    void setStorageInstructions(const std::string& instructions);
    void setNeedsRefrigeration(bool needs);

    std::string getStorageInstructions() const;
    bool getNeedsRefrigeration() const;

    double getFinalPrice() const override;
    std::string getType() const override;
    void printInfo() const override;
};

#endif