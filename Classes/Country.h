#pragma once
#include "City.h"
class Country {
private:
    int limit = 100;
    int food_stockpile = 0;
    int metal_stockpile = 0;
    int uranium_stockpile = 0;
    int nukes = 0;

public:
    City cities[5];

    // Getters and setters

    int getFoodStockpile() const;
    void setFoodStockpile(int value);

    int getMetalStockpile() const;
    void setMetalStockpile(int value);

    int getUraniumStockpile() const;
    void setUraniumStockpile(int value);

    int getNukes() const;
    void setNukes(int value);

    // Incomes
    int getFoodIncome() const;
    int getMetalIncome() const;
    int getUraniumIncome() const;

    // Other
    int getNumberOfCities();

    void showCity();
};