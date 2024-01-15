#include "City.h"

City::City() : is_destroyed(false), is_upgraded(false), farms(2), mines(1), reactors(1) {
    // Constructor implementation, if needed
}

bool City::getIsDestroyed() const {
    return is_destroyed;
}

void City::setIsDestroyed(bool value) {
    is_destroyed = value;
}

bool City::getIsUpgraded() const {
    return is_upgraded;
}

void City::setIsUpgraded(bool value) {
    is_upgraded = value;
}

int City::getFarms() const {
    return farms;
}

void City::setFarms(int value) {
    farms = value;
}

int City::getMines() const {
    return mines;
}

void City::setMines(int value) {
    mines = value;
}

int City::getReactors() const {
    return reactors;
}

void City::setReactors(int value) {
    reactors = value;
}