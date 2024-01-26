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
    extern Settings globalSettings;
    std::filesystem::path currentPath = std::filesystem::path(__FILE__).parent_path().parent_path();
    std::cout << currentPath << "\n";

    // Define font and text for menu options
    sf::Font font_arial;
    if (!font_arial.loadFromFile((currentPath / "Resources" / "arial.ttf").string())) {
        std::cerr << "Error loading font." << std::endl;
    }

    sf::Texture creditsBackgroundTexture;
    if (!creditsBackgroundTexture.loadFromFile((currentPath / "Resources" / "menu_background.jpg").string())) {
        std::cerr << "Error loading creditsBackground." << std::endl;
    }
    sf::Sprite creditsBackgroundSprite(creditsBackgroundTexture);

    // Get the original size of the texture
    sf::Vector2u originalSize = creditsBackgroundTexture.getSize();
    // Get the window size
    sf::Vector2u windowSize = window.getSize();

    // Calculate the scale factor to fit the image into the window
    float scaleX = static_cast<float>(windowSize.x) / originalSize.x;
    float scaleY = static_cast<float>(windowSize.y) / originalSize.y;
    // Set the scale of the sprite
    creditsBackgroundSprite.setScale(scaleX, scaleY);

    sf::Text creditsTitleText("Credits", font_arial, 50);
    creditsTitleText.setOutlineThickness(2);
    creditsTitleText.setPosition((window.getSize().x - creditsTitleText.getGlobalBounds().width) / 2, 0);
    creditsTitleText.setFillColor(sf::Color::Red);

    sf::Text creditsText0("Dev Team:", font_arial, 40);
    creditsText0.setOutlineThickness(2);
    creditsText0.setPosition((window.getSize().x - creditsText0.getGlobalBounds().width) / 2, 300);

    sf::Text creditsText1("Creator: Mateusz Zaczeniuk", font_arial, 40);
    creditsText1.setOutlineThickness(2);
    creditsText1.setPosition((window.getSize().x - creditsText1.getGlobalBounds().width) / 2, 350);

    sf::Text creditsText2("Emotional Support: Teo", font_arial, 40);
    creditsText2.setOutlineThickness(2);
    creditsText2.setPosition((window.getSize().x - creditsText2.getGlobalBounds().width) / 2, 400);

    sf::Text creditsTextReturn("Return", font_arial, 40);
    creditsTextReturn.setOutlineThickness(2);
    creditsTextReturn.setPosition((window.getSize().x - creditsTextReturn.getGlobalBounds().width) / 2, 500);

    sf::Text highlightedOption("", font_arial, 40);
    highlightedOption.setFillColor(sf::Color::Red);

    std::cout << "SettingsFunction";
    int selected_option = -1;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (creditsTextReturn.getGlobalBounds().contains(mousePos)) {
                    selected_option = 0;
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == globalSettings.getKeyEscape()) {
                    break;
                }
                else if (event.key.code == globalSettings.getKeyConfirm()) {
                    break;
                }
                else if (event.key.code == globalSettings.getKeyDown()) {
                    selected_option = selected_option + 1 % 1;
                }
                else if (event.key.code == globalSettings.getKeyUp()) {
                    selected_option = selected_option - 1 + 1 % 1;
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (creditsTextReturn.getGlobalBounds().contains(mousePos)) {
                        std::cout << "Mouse Return\n";
                        break;
                    }
                }
            }
        }

        switch (selected_option) {
        case 0:
            highlightedOption.setString(creditsTextReturn.getString());
            highlightedOption.setPosition(creditsTextReturn.getPosition());
            break;
        default:
            break;
        }

        if (selected_option = 0) {
            window.draw(highlightedOption);
        }
        window.clear();
        window.draw(creditsBackgroundSprite);
        window.draw(creditsText0);
        window.draw(creditsText1);
        window.draw(creditsText2);
        window.draw(creditsTitleText);
        window.draw(creditsTextReturn);
        window.draw(highlightedOption);
        window.display();
    }
}

void showCredits(sf::RenderWindow& window) {
    extern Settings globalSettings;
    std::filesystem::path currentPath = std::filesystem::path(__FILE__).parent_path().parent_path();
    std::cout << currentPath << "\n";

    // Define font and text for menu options
    sf::Font font_arial;
    if (!font_arial.loadFromFile((currentPath / "Resources" / "arial.ttf").string())) {
        std::cerr << "Error loading font." << std::endl;
    }

    sf::Texture creditsBackgroundTexture;
    if (!creditsBackgroundTexture.loadFromFile((currentPath / "Resources" / "menu_background.jpg").string())) {
        std::cerr << "Error loading creditsBackground." << std::endl;
    }
    sf::Sprite creditsBackgroundSprite(creditsBackgroundTexture);

    // Get the original size of the texture
    sf::Vector2u originalSize = creditsBackgroundTexture.getSize();
    // Get the window size
    sf::Vector2u windowSize = window.getSize();

    // Calculate the scale factor to fit the image into the window
    float scaleX = static_cast<float>(windowSize.x) / originalSize.x;
    float scaleY = static_cast<float>(windowSize.y) / originalSize.y;
    // Set the scale of the sprite
    creditsBackgroundSprite.setScale(scaleX, scaleY);

    sf::Text creditsTitleText("Credits", font_arial, 50);
    creditsTitleText.setOutlineThickness(2);
    creditsTitleText.setPosition((window.getSize().x - creditsTitleText.getGlobalBounds().width) / 2, 0);
    creditsTitleText.setFillColor(sf::Color::Red);

    sf::Text creditsText0("Dev Team:", font_arial, 40);
    creditsText0.setOutlineThickness(2);
    creditsText0.setPosition((window.getSize().x - creditsText0.getGlobalBounds().width) / 2, 100);

    sf::Text creditsText1("Creator: Mateusz Zaczeniuk", font_arial, 40);
    creditsText1.setOutlineThickness(2);
    creditsText1.setPosition((window.getSize().x - creditsText1.getGlobalBounds().width) / 2, 150);

    sf::Text creditsText2("Emotional Support: Teo", font_arial, 40);
    creditsText2.setOutlineThickness(2);
    creditsText2.setPosition((window.getSize().x - creditsText2.getGlobalBounds().width) / 2, 200);

    sf::Text creditsTextReturn("Return", font_arial, 40);
    creditsTextReturn.setOutlineThickness(2);
    creditsTextReturn.setPosition((window.getSize().x - creditsTextReturn.getGlobalBounds().width) / 2, 500);

    sf::Text highlightedOption("", font_arial, 40);
    highlightedOption.setFillColor(sf::Color::Red);

    std::cout << "CreditsFunction";
    int selected_option = -1;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (creditsTextReturn.getGlobalBounds().contains(mousePos)) {
                    selected_option = 0;
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == globalSettings.getKeyEscape()) {
                    return;
                }
                else if (event.key.code == globalSettings.getKeyConfirm()) {
                    if(selected_option = 0){
                        return;
                    }
                }
                else if (event.key.code == globalSettings.getKeyDown()) {
                    selected_option = selected_option + 1 % 1;
                }
                else if (event.key.code == globalSettings.getKeyUp()) {
                    selected_option = selected_option - 1 + 1 % 1;
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (creditsTextReturn.getGlobalBounds().contains(mousePos)) {
                        std::cout << "Mouse Return\n";
                        return;
                    }
                }
            }
        }

        switch (selected_option) {
        case 0:
            highlightedOption.setString(creditsTextReturn.getString());
            highlightedOption.setPosition(creditsTextReturn.getPosition());
            break;
        default:
            break;
        }

        if (selected_option = 0) {
            window.draw(highlightedOption);
        }
        window.clear();
        window.draw(creditsBackgroundSprite);
        window.draw(creditsText0);
        window.draw(creditsText1);
        window.draw(creditsText2);
        window.draw(creditsTitleText);
        window.draw(creditsTextReturn);
        window.draw(highlightedOption);
        window.display();
    }
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

    sf::Text timeElapsed("Year: ", font_arial, 30);
    timeElapsed.setOutlineThickness(2);
    timeElapsed.setPosition(700, 50);

    sf::Text timeInGame("Real Time: ", font_arial, 16);
    timeInGame.setOutlineThickness(2);
    timeInGame.setPosition(220, (80 + 50) / 2);

    std::mutex mtx;

    int time_elapsed = 0;
    std::cout << "ClockFunction";

    while (window.isOpen()) {

        timeElapsed.setString("Year: " + std::to_string(time_elapsed));
        window.draw(timeElapsed);

        std::this_thread::sleep_for(std::chrono::seconds(1));
        time_elapsed++;
    }
}