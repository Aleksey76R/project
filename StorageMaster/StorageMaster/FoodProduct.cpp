#include "FoodProduct.h"

FoodProduct::FoodProduct(int id, const std::string& name, double basePrice, int quantity,
    const std::string& expirationDate, bool isPerishable,
    int storageTemperature)
    : Product(id, name, basePrice, quantity),
    expirationDate(expirationDate),
    isPerishable(isPerishable),
    storageTemperature(storageTemperature) {
}

FoodProduct::~FoodProduct() {}

void FoodProduct::setExpirationDate(const std::string& date) {
    expirationDate = date;
}

void FoodProduct::setIsPerishable(bool isPerishable) {
    this->isPerishable = isPerishable;
}

void FoodProduct::setStorageTemperature(int temperature) {
    storageTemperature = temperature;
}

std::string FoodProduct::getExpirationDate() const {
    return expirationDate;
}

bool FoodProduct::getIsPerishable() const {
    return isPerishable;
}

int FoodProduct::getStorageTemperature() const {
    return storageTemperature;
}

std::string FoodProduct::getCurrentDate() const {
    time_t now = time(nullptr);
    tm* local = localtime(&now);

    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", local);
    return std::string(buffer);
}

std::tm FoodProduct::parseDate(const std::string& date) const {
    int year, month, day;
    char dash1, dash2;
    std::stringstream ss(date);
    ss >> year >> dash1 >> month >> dash2 >> day;

    std::tm tm = { 0 };
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = 0;
    tm.tm_min = 0;
    tm.tm_sec = 0;

    return tm;
}

bool FoodProduct::isExpired() const {
    return expirationDate < getCurrentDate();
}

int FoodProduct::daysUntilExpiration() const {
    if (isExpired()) return -1;

    std::tm expTm = parseDate(expirationDate);
    std::tm curTm = parseDate(getCurrentDate());

    std::time_t expTime = std::mktime(&expTm);
    std::time_t curTime = std::mktime(&curTm);

    double diffSeconds = std::difftime(expTime, curTime);
    int daysLeft = static_cast<int>(diffSeconds / (60 * 60 * 24));

    return daysLeft;
}

double FoodProduct::getFinalPrice() const {
    if (isExpired()) {
        return 0.0;
    }

    double price = get_basePrice() * 1.05;

    if (isPerishable) {
        price *= 1.15;
    }

    int daysLeft = daysUntilExpiration();
    if (daysLeft >= 0 && daysLeft < 7) {
        price *= 0.7;
    }

    if (storageTemperature < 0) {
        price *= 1.1;
    }

    return price;
}

std::string FoodProduct::getType() const {
    return "FoodProduct";
}

void FoodProduct::printInfo() const {
    std::cout << "\n========================================" << std::endl;
    std::cout << "Тип: " << getType() << std::endl;
    std::cout << "ID: " << get_id() << std::endl;
    std::cout << "Название: " << get_name() << std::endl;
    std::cout << "Базовая цена: " << get_basePrice() << " руб" << std::endl;
    std::cout << "Итоговая цена: " << getFinalPrice() << " руб" << std::endl;
    std::cout << "Количество: " << get_quantity() << " шт" << std::endl;
    std::cout << "Срок годности: " << expirationDate;

    if (isExpired()) {
        std::cout << " (ПРОСРОЧЕН!)" << std::endl;
    }
    else {
        int days = daysUntilExpiration();
        std::cout << " (осталось " << days << " дней)" << std::endl;
    }

    std::cout << "Скоропортящийся: " << (isPerishable ? "Да" : "Нет") << std::endl;
    std::cout << "Температура хранения: " << storageTemperature << " C" << std::endl;
    std::cout << "========================================" << std::endl;
}