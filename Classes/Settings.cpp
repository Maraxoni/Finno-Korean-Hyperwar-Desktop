#include "Settings.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

const int MAX_SPEED = 5;
const int MIN_SPEED = 1;
const int MAX_DIFFICULTY = 3;
const int MIN_DIFFICULTY = 1;

Settings::Settings() {
    loadFromFile();
    saveToFile();
}

void Settings::loadFromFile() {
    std::ifstream file(settingsFilename);
    if (file.is_open()) {
        nlohmann::json jsonSettings;
        file >> jsonSettings;

        keyUp = static_cast<sf::Keyboard::Key>(jsonSettings["keyUp"]);
        keyDown = static_cast<sf::Keyboard::Key>(jsonSettings["keyDown"]);
        keyLeft = static_cast<sf::Keyboard::Key>(jsonSettings["keyLeft"]);
        keyRight = static_cast<sf::Keyboard::Key>(jsonSettings["keyRight"]);
        keyConfirm = static_cast<sf::Keyboard::Key>(jsonSettings["keyConfirm"]);
        chosenCountry = jsonSettings["chosenCountry"].get<std::string>();
        speed = jsonSettings["speed"];
        difficulty = jsonSettings["difficulty"];

        file.close();
    }
    else {
        std::cerr << "Error reading file: " << settingsFilename << std::endl;
    }
}

void Settings::saveToFile() {
    std::ofstream file(settingsFilename);
    if (file.is_open()) {
        nlohmann::json jsonSettings;
        jsonSettings["keyUp"] = static_cast<int>(keyUp);
        jsonSettings["keyDown"] = static_cast<int>(keyDown);
        jsonSettings["keyLeft"] = static_cast<int>(keyLeft);
        jsonSettings["keyRight"] = static_cast<int>(keyRight);
        jsonSettings["keyConfirm"] = static_cast<int>(keyConfirm);
        jsonSettings["chosenCountry"] = chosenCountry;
        jsonSettings["speed"] = speed;
        jsonSettings["difficulty"] = difficulty;

        file << jsonSettings.dump(2);  // Pretty-print with an indentation of 2 spaces
        file.close();
    }
    else {
        std::cerr << "Error writing file: " << settingsFilename << std::endl;
    }
}

sf::Keyboard::Key Settings::getKeyUp() const {
    return keyUp;
}

void Settings::setKeyUp(sf::Keyboard::Key key) {
    keyUp = key;
}

sf::Keyboard::Key Settings::getKeyDown() const {
    return keyDown;
}

void Settings::setKeyDown(sf::Keyboard::Key key) {
    keyDown = key;
}

sf::Keyboard::Key Settings::getKeyLeft() const {
    return keyLeft;
}

void Settings::setKeyLeft(sf::Keyboard::Key key) {
    keyLeft = key;
}

sf::Keyboard::Key Settings::getKeyRight() const {
    return keyRight;
}

void Settings::setKeyRight(sf::Keyboard::Key key) {
    keyRight = key;
}

sf::Keyboard::Key Settings::getKeyConfirm() const {
    return keyConfirm;
}

void Settings::setKeyConfirm(sf::Keyboard::Key key) {
    keyConfirm = key;
}

std::string Settings::getChosenCountry() const {
    return chosenCountry;
}

void Settings::setChosenCountry(const std::string& country) {
    chosenCountry = country;
}

int Settings::getSpeed() const {
    return speed;
}

void Settings::setSpeed(int newSpeed) {
    speed = std::clamp(newSpeed, MIN_SPEED, MAX_SPEED);
}

void Settings::increaseSpeed() {
    setSpeed(speed + 1);
}

void Settings::decreaseSpeed() {
    setSpeed(speed - 1);
}

int Settings::getDifficulty() const {
    return difficulty;
}

void Settings::setDifficulty(int newDifficulty) {
    difficulty = std::clamp(newDifficulty, MIN_DIFFICULTY, MAX_DIFFICULTY);
}

void Settings::increaseDifficulty() {
    setDifficulty(difficulty + 1);
}

void Settings::decreaseDifficulty() {
    setDifficulty(difficulty - 1);
}