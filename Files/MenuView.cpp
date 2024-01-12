#include <bits/stdc++.h>
#include <string.h>
#include <string>
#include <SFML/Graphics.hpp>
#include "MenuView.h"

void showMenu(sf::RenderWindow& window){
    // Define font and text for menu options
    sf::Font font;
    if (!font.loadFromFile("D:\\Maraxowanie\\Programowanie\\KCK\\Finno-Korean Hyperwar Desktop\\Resources\\arial.ttf")) {
        std::cerr << "Error loading font." << std::endl;
    }

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("D:/Maraxowanie/Programowanie/KCK/Finno-Korean Hyperwar Desktop/Resources/menu_background.jpg")) {
        std::cerr << "Error loading font." << std::endl;
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    sf::Text option1("Start", font, 30);
    sf::Text option2("Options", font, 30);
    sf::Text option3("Credits", font, 30);
    sf::Text option4("Exit", font, 30);

    sf::Text titleText("Finno-Korean Hyperwar", font, 50);
    titleText.setFillColor(sf::Color::Red);

    // Set initial positions for menu options
    titleText.setPosition(30, 0);
    option1.setPosition(260, 200);
    option2.setPosition(260, 250);
    option3.setPosition(260, 300);
    option4.setPosition(260, 350);

    // Highlighted option
    sf::Text highlightedOption("", font, 30);
    highlightedOption.setFillColor(sf::Color::Red);

    int selectedOption = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle key presses for menu navigation
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    selectedOption = (selectedOption - 1 + 4) % 4;
                } else if (event.key.code == sf::Keyboard::Down) {
                    selectedOption = (selectedOption + 1) % 4;
                } else if (event.key.code == sf::Keyboard::Enter) {
                    // If Enter key is pressed, perform the action associated with the selected option
                    switch (selectedOption) {
                        case 0:
                            showMap(window);
                            break;
                        // Add cases for other options if needed
                    }
                }
            }

            // Handle mouse movement for menu navigation
            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (option1.getGlobalBounds().contains(mousePos)) {
                    selectedOption = 0;
                } else if (option2.getGlobalBounds().contains(mousePos)) {
                    selectedOption = 1;
                } else if (option3.getGlobalBounds().contains(mousePos)) {
                    selectedOption = 2;
                } else if (option4.getGlobalBounds().contains(mousePos)) {
                    selectedOption = 3;
                }
            }

            // Handle mouse click
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (option1.getGlobalBounds().contains(mousePos)) {
                        // If "Start" is clicked, open a new window (e.g., showMap)
                        showMap(window);
                    }
                }
            }
        }

        // Set highlighted text based on selected option
        switch (selectedOption) {
        case 0:
            highlightedOption.setString(option1.getString());
            highlightedOption.setPosition(option1.getPosition());
            break;
        case 1:
            highlightedOption.setString(option2.getString());
            highlightedOption.setPosition(option2.getPosition());
            break;
        case 2:
            highlightedOption.setString(option3.getString());
            highlightedOption.setPosition(option3.getPosition());
            break;
        case 3:
            highlightedOption.setString(option4.getString());
            highlightedOption.setPosition(option4.getPosition());
            break;
    }

        window.clear();
        window.draw(backgroundSprite);
        window.draw(titleText);
        // Draw menu options
        window.draw(option1);
        window.draw(option2);
        window.draw(option3);
        window.draw(option4);

        // Draw highlighted option
        window.draw(highlightedOption);

        window.display();
    }
}

