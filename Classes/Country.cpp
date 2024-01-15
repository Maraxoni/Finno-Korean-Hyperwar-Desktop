#include <fstream>
#include <iostream>
#include <string>
#include "Country.h"
#include "../Files/Functions.h"
#include "City.h"

// Getter and setter implementations
int Country::getFoodStockpile() const {
    return food_stockpile;
}

void Country::setFoodStockpile(int value) {
    if (value > limit) {
        value -= (value - limit);
    }
    food_stockpile = value;
}

int Country::getMetalStockpile() const {
    return metal_stockpile;
}

void Country::setMetalStockpile(int value) {
    if (value > limit) {
        value -= (value - limit);
    }
    metal_stockpile = value;
}

int Country::getUraniumStockpile() const {
    return uranium_stockpile;
}

void Country::setUraniumStockpile(int value) {
    if (value > limit) {
        value -= (value - limit);
    }
    uranium_stockpile = value;
}

int Country::getNukes() const {
    return nukes;
}

void Country::setNukes(int value) {
    nukes = value;
}

int Country::getFoodIncome() const {
    int sum = 0;

    for (int i = 0; i < 5; i++) {
        sum += cities[i].getFarms() - (cities[i].getMines() + cities[i].getReactors());
    }

    return sum;
}

int Country::getMetalIncome() const {
    int sum = 0;

    for (int i = 0; i < 5; i++) {
        sum += cities[i].getMines();
    }

    return sum;
}

int Country::getUraniumIncome() const {
    int sum = 0;

    for (int i = 0; i < 5; i++) {
        sum += cities[i].getReactors();
    }

    return sum;
}

int Country::getNumberOfCities() {
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        if (cities[i].getIsDestroyed() == false) {
            sum++;
        }
    }
    return sum;
}

void Country::showUpgradingCity() {
    // Implement the function as needed
    // For example, you can add code to show the upgrading city.
}