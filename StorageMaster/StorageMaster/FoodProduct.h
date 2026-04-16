#ifndef FOODPRODUCT_H
#define FOODPRODUCT_H

#include "Product.h"
#include <string>
#include <ctime>
#include <sstream>
#include <iostream>
#include <iomanip>

class FoodProduct : public Product {
private:
    std::string expirationDate;
    bool isPerishable;
    int storageTemperature;

    std::string getCurrentDate() const;
    std::tm parseDate(const std::string& date) const;

public:
    FoodProduct(int id, const std::string& name, double basePrice, int quantity,
        const std::string& expirationDate, bool isPerishable,
        int storageTemperature = 20);

    ~FoodProduct();

    void setExpirationDate(const std::string& date);
    void setIsPerishable(bool isPerishable);
    void setStorageTemperature(int temperature);

    std::string getExpirationDate() const;
    bool getIsPerishable() const;
    int getStorageTemperature() const;

    bool isExpired() const;
    int daysUntilExpiration() const;

    double getFinalPrice() const override;
    std::string getType() const override;
    void printInfo() const override;
};

#endif