#pragma once
// Warehouse.h
#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "Product.h"
#include <vector>
#include <memory>
#include <string>

class Warehouse {
private:
    std::vector<std::unique_ptr<Product>> items;

public:
    Warehouse();
    ~Warehouse();

    void addProduct(std::unique_ptr<Product> product);
    bool removeProduct(int id);
    Product* findProduct(int id) const;
    double calculateTotalValue() const;
    void printAllProducts() const;
    size_t getSize() const;
    void clear();
};

#endif