// Warehouse.cpp
#include "Warehouse.h"
#include <iostream>
#include <algorithm>

Warehouse::Warehouse() {}

Warehouse::~Warehouse() {
    clear();
}

void Warehouse::addProduct(std::unique_ptr<Product> product) {
    items.push_back(std::move(product));
    std::cout << "Tovar dobavlen na sklad. Vsego tovarov: " << items.size() << std::endl;
}

bool Warehouse::removeProduct(int id) {
    auto it = std::find_if(items.begin(), items.end(),
        [id](const std::unique_ptr<Product>& p) {
            return p->get_id() == id;
        });

    if (it != items.end()) {
        std::cout << "Tovar s ID " << id << " udalen so sklada" << std::endl;
        items.erase(it);
        return true;
    }

    std::cout << "Tovar s ID " << id << " ne nayden" << std::endl;
    return false;
}

Product* Warehouse::findProduct(int id) const {
    for (const auto& item : items) {
        if (item->get_id() == id) {
            return item.get();
        }
    }
    return nullptr;
}

double Warehouse::calculateTotalValue() const {
    double total = 0;
    for (const auto& item : items) {
        total += item->getFinalPrice() * item->get_quantity();
    }
    return total;
}

void Warehouse::printAllProducts() const {
    if (items.empty()) {
        std::cout << "Sklad pust" << std::endl;
        return;
    }

    std::cout << "\n========== SKLAD ==========" << std::endl;
    std::cout << "Vsego tovarov: " << items.size() << std::endl;

    for (const auto& item : items) {
        item->printInfo();
    }

    std::cout << "\nObshaya stoimost: " << calculateTotalValue() << " rub" << std::endl;
    std::cout << "===========================" << std::endl;
}

size_t Warehouse::getSize() const {
    return items.size();
}

void Warehouse::clear() {
    items.clear();
}