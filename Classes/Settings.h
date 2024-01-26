#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
class Settings {
private:
    sf::Keyboard::Key keyUp = sf::Keyboard::W;
    sf::Keyboard::Key keyDown = sf::Keyboard::S;
    sf::Keyboard::Key keyLeft = sf::Keyboard::A;
    sf::Keyboard::Key keyRight = sf::Keyboard::D;
    sf::Keyboard::Key keyConfirm = sf::Keyboard::Enter;
    sf::Keyboard::Key keyEscape = sf::Keyboard::Escape;
    sf::Keyboard::Key keyTab = sf::Keyboard::Tab;
    std::string chosenCountry = "Finland";
    int speed = 1;
    int difficulty = 2;

    std::filesystem::path currentPath = std::filesystem::path(__FILE__).parent_path().parent_path();
    std::string settingsFilename = (currentPath / "Resources" / "Settings.json").string();

public:
    // Constructor
    Settings();

    // Load function
    void loadFromFile();

    // Write function
    void saveToFile();

    // Getters and setters
    sf::Keyboard::Key getKeyUp() const;
    void setKeyUp(sf::Keyboard::Key key);

    sf::Keyboard::Key getKeyDown() const;
    void setKeyDown(sf::Keyboard::Key key);

    sf::Keyboard::Key getKeyLeft() const;
    void setKeyLeft(sf::Keyboard::Key key);

    sf::Keyboard::Key getKeyRight() const;
    void setKeyRight(sf::Keyboard::Key key);

    sf::Keyboard::Key getKeyConfirm() const;
    void setKeyConfirm(sf::Keyboard::Key key);

    sf::Keyboard::Key getKeyEscape() const;
    void setKeyEscape(sf::Keyboard::Key key);

    sf::Keyboard::Key getKeyTab() const;
    void setKeyTab(sf::Keyboard::Key key);

    std::string getChosenCountry() const;
    void setChosenCountry(const std::string& country);

    int getSpeed() const;
    void setSpeed(int newSpeed);
    void increaseSpeed();
    void decreaseSpeed();

    int getDifficulty() const;
    void setDifficulty(int newDifficulty);
    void increaseDifficulty();
    void decreaseDifficulty();
};

