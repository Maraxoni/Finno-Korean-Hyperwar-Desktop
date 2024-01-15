#include <fstream>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include "Country.h"
#include "../Files/Functions.h"


const int MAX_SPEED = 5;
const int MIN_SPEED = 1;
const int MAX_DIFFICULTY = 3;
const int MIN_DIFFICULTY = 1;

class Settings {
private:
    sf::Keyboard::Key keyUp = sf::Keyboard::W;
    sf::Keyboard::Key keyDown = sf::Keyboard::S;
    sf::Keyboard::Key keyLeft = sf::Keyboard::A;
    sf::Keyboard::Key keyRight = sf::Keyboard::D;
    sf::Keyboard::Key keyConfirm = sf::Keyboard::Enter;
    std::string chosenCountry = "Finland";
    int speed = 1;
    int difficulty = 2;

    std::filesystem::path currentPath = std::filesystem::path(__FILE__).parent_path().parent_path();
    std::string settingsFilename = (currentPath / "Resources" / "Settings.json").string();
public:
    //Constructor
    Settings() {
        loadFromFile();
        saveToFile();
    }
    // Load function
    void loadFromFile() {
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

    // Write function
    void saveToFile() {
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

public:
    // Getter
    char getKeyUp() const {
        return keyUp;
    }

    void setKeyUp(sf::Keyboard::Key key) {
        keyUp = key;
    }

    // Getter
    char getKeyDown() const {
        return keyDown;
    }

    void setKeyDown(sf::Keyboard::Key key) {
        keyDown = key;
    }
    // Getter
    char getKeyLeft() const {
        return keyLeft;
    }

    void setKeyLeft(sf::Keyboard::Key key) {
        keyLeft = key;
    }

    // Getter
    char getKeyRight() const {
        return keyRight;
    }

    void setKeyRight(sf::Keyboard::Key key) {
        keyRight = key;
    }
    // Getter
    char getKeyConfirm() const {
        return keyConfirm;
    }

    void setKeyConfirm(sf::Keyboard::Key key) {
        keyConfirm = key;
    }

    //Country selection

    std::string getChosenCountry() const {
        return chosenCountry;
    }

    void setChosenCountry(const std::string& country) {
        chosenCountry = country;
    }

    //Speed
    int getSpeed() const {
        return speed;
    }

    void setSpeed(int newSpeed) {
        if (newSpeed < MIN_SPEED || newSpeed > MAX_SPEED) {
            speed = MAX_SPEED;
        }
        else {
            speed = newSpeed;
        }
    }

    //Difficulty
    int getDifficulty() const {
        return difficulty;
    }

    void setDifficulty(int newDifficulty) {
        if (newDifficulty < MIN_DIFFICULTY || newDifficulty > MAX_DIFFICULTY) {
            difficulty = MIN_DIFFICULTY;
        }
        else {
            difficulty = newDifficulty;
        }
    }

};