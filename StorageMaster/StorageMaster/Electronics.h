#ifndef ELECTRONICS_H
#define ELECTRONICS_H

#include "Product.h"
#include <string>
#include <iostream>

class Electronics : public Product {
private:
    int warrantyMonths;
    bool hasBattery;
    bool isImported;

public:
    Electronics(int id, const std::string& name, double basePrice, int quantity,
        int warrantyMonths, bool hasBattery, bool isImported = false);

    ~Electronics();

    void set_warrantyMonths(int months);
    void set_hasBattery(bool hasBattery);
    void set_isImported(bool isImported);

    int get_warrantyMonths() const;
    bool get_hasBattery() const;
    bool get_isImported() const;

    double calculateWarrantyCost() const;
    bool needsSpecialDelivery() const;

    double getFinalPrice() const override;
    std::string getType() const override;
    void printInfo() const override;
};

#endif