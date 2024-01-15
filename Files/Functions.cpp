#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <thread>
#include <mutex>
#include "Functions.h"
#include "../Classes/Settings.h"
#include "GameView.h"
#include "Game.h"
#include "MenuView.h"



void showSettings(sf::RenderWindow& window) {
    std::cout << "SettingsFunction";
}

void showCredits(sf::RenderWindow& window) {
    std::cout << "CreditsFunction";
}

void showSave(sf::RenderWindow& window) {
    std::cout << "SaveFunction";
}

void showLoad(sf::RenderWindow& window) {
    std::cout << "LoadFunction";
}


void showClock(sf::RenderWindow& window) {
    std::filesystem::path currentPath = std::filesystem::path(__FILE__).parent_path().parent_path();
    // Define font and text for menu options
    sf::Font font_arial;
    if (!font_arial.loadFromFile((currentPath / "Resources" / "arial.ttf").string())) {
        std::cerr << "Error loading font." << std::endl;
    }

    sf::Text timeElapsed("Time Elapsed: ", font_arial, 30);
    timeElapsed.setOutlineThickness(2);
    timeElapsed.setPosition(700, 50);

    std::mutex mtx;

    int time_elapsed = 0;

    while (1) {
        mtx.lock();
        timeElapsed.setString("Time Elapsed: " + std::to_string(time_elapsed));
        window.draw(timeElapsed);
        mtx.unlock();

        time_elapsed++;

    }
}