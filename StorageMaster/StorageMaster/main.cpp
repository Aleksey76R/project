#include "Electronics.h"
#include "Clothing.h"
#include "FoodProduct.h"
#include "PerishableProduct.h"
#include "Warehouse.h"
#include <iostream>
#include <memory>

int main() {
    setlocale(LC_ALL, "Russian");

    Warehouse warehouse;

    warehouse.addProduct(std::make_unique<Electronics>(1, "iPhone 15", 80000, 10, 24, true, true));
    warehouse.addProduct(std::make_unique<Electronics>(2, "Samsung TV", 50000, 5, 12, false, false));
    warehouse.addProduct(std::make_unique<Clothing>(3, "Koza Куртка", 5000, 7, "XL", "koza", true));
    warehouse.addProduct(std::make_unique<Clothing>(4, "Futbolka", 1500, 20, "L", "hlopok", false));
    warehouse.addProduct(std::make_unique<FoodProduct>(5, "Moloko", 89.99, 50, "2026-04-25", true, 4));
    warehouse.addProduct(std::make_unique<FoodProduct>(6, "Hleb", 45.00, 30, "2026-04-18", true, 20));
    warehouse.addProduct(std::make_unique<FoodProduct>(7, "Tushenka", 250.0, 100, "2028-01-01", false, 20));
    warehouse.addProduct(std::make_unique<PerishableProduct>(8, "Svezhaya ryba", 450.0, 15, "2026-04-20", -18, "Hranit v morozilke", true));

    warehouse.printAllProducts();

    Product* found = warehouse.findProduct(1);
    if (found) {
        std::cout << "\n Nayden tovar: " << found->get_name()
            << ", tip: " << found->getType() << std::endl;
    }

    warehouse.removeProduct(2);

    std::cout << "\n Posle udaleniya:" << std::endl;
    warehouse.printAllProducts();

    std::cout << "\n Obshaya stoimost sklada: " << warehouse.calculateTotalValue() << " rub" << std::endl;
    std::cout << " Kolichestvo tovarov na sklade: " << warehouse.getSize() << std::endl;

    return 0;
}