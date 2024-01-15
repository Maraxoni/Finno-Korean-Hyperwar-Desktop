#include <bits/stdc++.h>
#include <string.h>
#include <string>
#include <SFML/Graphics.hpp>
#include "MenuView.h"
#include "GameView.h"
#include "Functions.h"
#include "../Classes/Settings.cpp"

void showMenu(sf::RenderWindow& window) {
    extern Settings globalSettings;
    // Path
    std::filesystem::path currentPath = std::filesystem::path(__FILE__).parent_path().parent_path();
    std::cout << currentPath << "\n";

    // Define font and text for menu options
    sf::Font font_arial;
    if (!font_arial.loadFromFile((currentPath / "Resources" / "arial.ttf").string())) {
        std::cerr << "Error loading font." << std::endl;
    }

    sf::Texture menuBackgroundTexture;
    if (!menuBackgroundTexture.loadFromFile((currentPath / "Resources" / "menu_background.jpg").string())) {
        std::cerr << "Error loading menuBackground." << std::endl;
    }
    sf::Sprite menuBackgroundSprite(menuBackgroundTexture);

    // Get the original size of the texture
    sf::Vector2u originalSize = menuBackgroundTexture.getSize();
    // Get the window size
    sf::Vector2u windowSize = window.getSize();

    // Calculate the scale factor to fit the image into the window
    float scaleX = static_cast<float>(windowSize.x) / originalSize.x;
    float scaleY = static_cast<float>(windowSize.y) / originalSize.y;
    // Set the scale of the sprite
    menuBackgroundSprite.setScale(scaleX, scaleY);

    sf::Text titleText("Finno-Korean Hyperwar", font_arial, 50);
    titleText.setOutlineThickness(2);

    sf::Text menuText0("New Game", font_arial, 30);
    sf::Text menuText1("Load Game", font_arial, 30);
    sf::Text menuText2("Settings", font_arial, 30);
    sf::Text menuText3("Credits", font_arial, 30);
    sf::Text menuText4("Exit", font_arial, 30);

    menuText0.setOutlineThickness(2);
    menuText1.setOutlineThickness(2);
    menuText2.setOutlineThickness(2);
    menuText3.setOutlineThickness(2);
    menuText4.setOutlineThickness(2);

    titleText.setFillColor(sf::Color::Red);

    // Set initial positions for menu options
    titleText.setPosition((window.getSize().x - titleText.getGlobalBounds().width) / 2, 0);
    menuText0.setPosition((window.getSize().x - menuText0.getGlobalBounds().width) / 2, 180);
    menuText1.setPosition((window.getSize().x - menuText1.getGlobalBounds().width) / 2, 230);
    menuText2.setPosition((window.getSize().x - menuText2.getGlobalBounds().width) / 2, 280);
    menuText3.setPosition((window.getSize().x - menuText3.getGlobalBounds().width) / 2, 330);
    menuText4.setPosition((window.getSize().x - menuText4.getGlobalBounds().width) / 2, 380);
    // Highlighted option
    sf::Text highlightedOption("", font_arial, 30);
    highlightedOption.setFillColor(sf::Color::Red);
    // highlightedOption.setOutlineThickness(2);

    std::cout << "MenuFunction\n";

    int selectedOption = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle key presses for menu navigation
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    selectedOption = (selectedOption - 1 + 5) % 5;
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    selectedOption = (selectedOption + 1) % 5;
                }
                else if (event.key.code == globalSettings.getKeyConfirm()) {
                    // If Enter key is pressed, perform the action associated with the selected option
                    switch (selectedOption) {
                    case 0:
                        std::cout << "Enter New Game\n";
                        showMap(window);
                        break;
                    case 1:
                        std::cout << "Enter Load Game\n";
                        break;
                    case 2:
                        std::cout << "Enter Options\n";
                        break;
                    case 3:
                        std::cout << "Enter Credits\n";
                        break;
                    case 4:
                        std::cout << "Enter Exit\n";
                        return;
                        break;
                    }
                }
            }

            // Handle mouse movement for menu navigation
            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (menuText0.getGlobalBounds().contains(mousePos)) {
                    selectedOption = 0;
                }
                else if (menuText1.getGlobalBounds().contains(mousePos)) {
                    selectedOption = 1;
                }
                else if (menuText2.getGlobalBounds().contains(mousePos)) {
                    selectedOption = 2;
                }
                else if (menuText3.getGlobalBounds().contains(mousePos)) {
                    selectedOption = 3;
                }
                else if (menuText4.getGlobalBounds().contains(mousePos)) {
                    selectedOption = 4;
                }
            }

            // Handle mouse click
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (menuText0.getGlobalBounds().contains(mousePos)) {
                        std::cout << "Mouse New Game\n";
                        showMap(window);
                    }
                    if (menuText1.getGlobalBounds().contains(mousePos)) {
                        std::cout << "Mouse Load Game\n";
                    }
                    if (menuText2.getGlobalBounds().contains(mousePos)) {
                        std::cout << "Mouse Options\n";
                    }
                    if (menuText3.getGlobalBounds().contains(mousePos)) {
                        std::cout << "Mouse Credits\n";
                    }
                    if (menuText4.getGlobalBounds().contains(mousePos)) {
                        std::cout << "Mouse Exit\n";
                        return;
                    }
                }
            }
        }

        // Set highlighted text based on selected option
        switch (selectedOption) {
        case 0:
            highlightedOption.setString(menuText0.getString());
            highlightedOption.setPosition(menuText0.getPosition());
            break;
        case 1:
            highlightedOption.setString(menuText1.getString());
            highlightedOption.setPosition(menuText1.getPosition());
            break;
        case 2:
            highlightedOption.setString(menuText2.getString());
            highlightedOption.setPosition(menuText2.getPosition());
            break;
        case 3:
            highlightedOption.setString(menuText3.getString());
            highlightedOption.setPosition(menuText3.getPosition());
            break;
        case 4:
            highlightedOption.setString(menuText4.getString());
            highlightedOption.setPosition(menuText4.getPosition());
            break;
        }

        window.clear();
        window.draw(menuBackgroundSprite);
        window.draw(titleText);
        // Draw menu options
        window.draw(menuText0);
        window.draw(menuText1);
        window.draw(menuText2);
        window.draw(menuText3);
        window.draw(menuText4);
        // Draw highlighted option
        window.draw(highlightedOption);

        window.display();
    }
}
