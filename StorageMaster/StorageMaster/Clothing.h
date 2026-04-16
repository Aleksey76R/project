#pragma once
// Clothing.h
#ifndef CLOTHING_H
#define CLOTHING_H

#include "Product.h"
#include <string>

class Clothing : public Product {
private:
    std::string size;
    std::string material;
    bool isLuxury;

public:
    Clothing(int id, const std::string& name, double basePrice, int quantity,
        const std::string& size, const std::string& material, bool isLuxury = false);

    ~Clothing();

    void set_size(const std::string& size);
    void set_material(const std::string& material);
    void setIsLuxury(bool isLuxury);

    std::string get_size() const;
    std::string get_material() const;
    bool getIsLuxury() const;

    double getFinalPrice() const override;
    std::string getType() const override;
    void printInfo() const override;
};

#endif