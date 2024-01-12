#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "GameView.h"
#include "MenuView.h"

void showMap(sf::RenderWindow& window){
    std::filesystem::path currentPath = std::filesystem::path(__FILE__).parent_path().parent_path();

    sf::Texture mapTexture;
    if (!mapTexture.loadFromFile((currentPath / "Resources" / "map.jpg").string())) {
        std::cerr << "Error loading font." << std::endl;
    }
    sf::Sprite mapSprite(mapTexture);

    // Get the original size of the texture
    sf::Vector2u originalSize = mapTexture.getSize();
    // Get the window size
    sf::Vector2u windowSize = window.getSize();

    // Calculate the scale factor to fit the image into the window
    float scaleX = static_cast<float>(windowSize.x) / originalSize.x;
    float scaleY = static_cast<float>(windowSize.y) / originalSize.y;
    // Set the scale of the sprite
    mapSprite.setScale(scaleX, scaleY);

    std::cout << "GameFunction\n";

    while(window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            }

            if (event.type == sf::Event::MouseButtonPressed) {

            }

            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Escape){
                    showGameMenu(window);
                }
            }
        }
        window.clear();
        window.draw(mapSprite);
        window.display();
    }
}

void showGameMenu(sf::RenderWindow& window){
    std::filesystem::path currentPath = std::filesystem::path(__FILE__).parent_path().parent_path();

    // Define font and text for menu options
    sf::Font font_arial;
    if (!font_arial.loadFromFile((currentPath / "Resources" / "arial.ttf").string())) {
        std::cerr << "Error loading font." << std::endl;
    }

    sf::Text gameMenuText0("Resume", font_arial, 20);
    sf::Text gameMenuText1("Save", font_arial, 20);
    sf::Text gameMenuText2("Load", font_arial, 20);
    sf::Text gameMenuText3("Settings", font_arial, 20);
    sf::Text gameMenuText4("Main Menu", font_arial, 20);
    sf::Text gameMenuText5("Exit Game", font_arial, 20);

    gameMenuText0.setOutlineThickness(2);
    gameMenuText1.setOutlineThickness(2);
    gameMenuText2.setOutlineThickness(2);
    gameMenuText3.setOutlineThickness(2);
    gameMenuText4.setOutlineThickness(2);
    gameMenuText5.setOutlineThickness(2);

    // Set initial positions for menu options
    gameMenuText0.setPosition((window.getSize().x - gameMenuText0.getGlobalBounds().width) / 2, 180);
    gameMenuText1.setPosition((window.getSize().x - gameMenuText1.getGlobalBounds().width) / 2, 230);
    gameMenuText2.setPosition((window.getSize().x - gameMenuText2.getGlobalBounds().width) / 2, 280);
    gameMenuText3.setPosition((window.getSize().x - gameMenuText3.getGlobalBounds().width) / 2, 330);
    gameMenuText4.setPosition((window.getSize().x - gameMenuText4.getGlobalBounds().width) / 2, 380);
    gameMenuText5.setPosition((window.getSize().x - gameMenuText5.getGlobalBounds().width) / 2, 430);

    float rectangleX = (gameMenuText4.getGlobalBounds().width);
    float rectangleY = (430 - 180 + 20 + 5);
    sf::RectangleShape gameMenuRectangle(sf::Vector2f(rectangleX, rectangleY)); // Set the size of the rectangle
    
    gameMenuRectangle.setPosition((window.getSize().x - gameMenuRectangle.getGlobalBounds().width)/2, 180);

    // Set the color of the rectangle
    gameMenuRectangle.setFillColor(sf::Color::Magenta);
    gameMenuRectangle.setOutlineThickness(2);

    std::cout << "GameMenuFunction\n";

    int selectedOption = 0;

    while(window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            // Handle mouse movement for menu navigation
            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (gameMenuText0.getGlobalBounds().contains(mousePos)) {
                    selectedOption = 0;
                } else if (gameMenuText1.getGlobalBounds().contains(mousePos)) {
                    selectedOption = 1;
                } else if (gameMenuText2.getGlobalBounds().contains(mousePos)) {
                    selectedOption = 2;
                } else if (gameMenuText3.getGlobalBounds().contains(mousePos)) {
                    selectedOption = 3;
                } else if (gameMenuText4.getGlobalBounds().contains(mousePos)) {
                    selectedOption = 4;
                }
            }
            // Handle mouse click
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (gameMenuText0.getGlobalBounds().contains(mousePos)) {
                        // If "Start" is clicked, open a new window (e.g., showMap)
                        window.clear();
                        return;
                    }
                    if (gameMenuText1.getGlobalBounds().contains(mousePos)) {
                        // If "Start" is clicked, open a new window (e.g., showMap)
                        std::cout << "Save";
                    }
                    if (gameMenuText2.getGlobalBounds().contains(mousePos)) {
                        // If "Start" is clicked, open a new window (e.g., showMap)
                        std::cout << "Load";
                    }
                    if (gameMenuText3.getGlobalBounds().contains(mousePos)) {
                        // If "Start" is clicked, open a new window (e.g., showMap)
                        std::cout << "Settings";
                    }
                    if (gameMenuText4.getGlobalBounds().contains(mousePos)) {
                        // If "Start" is clicked, open a new window (e.g., showMap)
                        showMenu(window);
                        break;
                    }
                    if (gameMenuText5.getGlobalBounds().contains(mousePos)) {
                        // If "Start" is clicked, open a new window (e.g., showMap)
                        std::cout << "Exit Game";
                        break;
                    }
                }
            }
        }

        //window.clear();
        window.draw(gameMenuRectangle); 
        window.draw(gameMenuText0);
        window.draw(gameMenuText1);
        window.draw(gameMenuText2);
        window.draw(gameMenuText3);
        window.draw(gameMenuText4);
        window.draw(gameMenuText5);

        //window.draw(gameMenuText0);
        window.display();
    }
}