#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "GameView.h"
#include "Game.h"
#include "Functions.h"
#include "MenuView.h"
#include "../Classes/Settings.cpp"
#include <thread>

void showMap(sf::RenderWindow& window) {
    extern Settings globalSettings;

    Country Finland;
    Country Korea;

    Country* PlayerCountry = nullptr;
	Country* EnemyCountry = nullptr;

    if (globalSettings.getChosenCountry() == "Finland") {
		PlayerCountry = &Finland;
		EnemyCountry = &Korea;
	}
	else if (globalSettings.getChosenCountry() == "Korea") {
		PlayerCountry = &Korea;
		EnemyCountry = &Finland;
	}

    if (globalSettings.getDifficulty() == 1) {
		EnemyCountry->setFoodStockpile(0);
		EnemyCountry->setMetalStockpile(0);
		EnemyCountry->setUraniumStockpile(0);
	}
	else if (globalSettings.getDifficulty() == 2) {
		EnemyCountry->setFoodStockpile(20);
		EnemyCountry->setMetalStockpile(20);
		EnemyCountry->setUraniumStockpile(20);
	}
	else if (globalSettings.getDifficulty() == 3) {
		EnemyCountry->setFoodStockpile(20);
		EnemyCountry->setMetalStockpile(20);
		EnemyCountry->setUraniumStockpile(20);
		EnemyCountry->setNukes(1);
	}

    std::cout << "GameFunction\n";
    std::cout << "Bazinga1\n";
    std::thread gameViewThread(showGame, std::ref(window), std::ref(Finland), std::ref(Korea));
    std::thread gameLogicThread(game, std::ref(Finland), std::ref(Korea));
    std::thread clockThread(showClock, std::ref(window));
    std::cout << "Bazinga2\n";
    gameViewThread.join();
    gameLogicThread.join();
    clockThread.join();
    std::cout << "Bazinga3\n";
    
}

void showGame(sf::RenderWindow& window, Country& PlayerCountry, Country& EnemyCountry){
    std::filesystem::path currentPath = std::filesystem::path(__FILE__).parent_path().parent_path();

    // Define font and text for menu options
    sf::Font font_arial;
    if (!font_arial.loadFromFile((currentPath / "Resources" / "arial.ttf").string())) {
        std::cerr << "Error loading font." << std::endl;
    }
    //Map
    sf::Texture mapTexture;
    if (!mapTexture.loadFromFile((currentPath / "Resources" / "map.png").string())) {
        std::cerr << "Error loading font." << std::endl;
    }
    sf::Sprite mapSprite(mapTexture);

    sf::Vector2u originalSize = mapTexture.getSize();
    sf::Vector2u windowSize = window.getSize();
    float scaleX = static_cast<float>(800) / originalSize.x;
    float scaleY = static_cast<float>(600) / originalSize.y;
    mapSprite.setScale(scaleX, scaleY);

    //Flag - Finland
    sf::Texture finlandFlagTexture;
    if (!finlandFlagTexture.loadFromFile((currentPath / "Resources" / "Flag_of_Finland.png").string())) {
        std::cerr << "Error loading Finland flag texture." << std::endl;
    }
    sf::Sprite finlandFlagSprite(finlandFlagTexture);
    finlandFlagSprite.setScale(150.f / finlandFlagTexture.getSize().x, 100.f / finlandFlagTexture.getSize().y);
    finlandFlagSprite.setPosition(2, 2);

    //Flag - Korea
    sf::Texture koreaFlagTexture;
    if (!koreaFlagTexture.loadFromFile((currentPath / "Resources" / "Flag_of_South_Korea.png").string())) {
        std::cerr << "Error loading Korea flag texture." << std::endl;
    }
    sf::Sprite koreaFlagSprite(koreaFlagTexture);
    koreaFlagSprite.setScale(50.f / koreaFlagTexture.getSize().x, 50.f / koreaFlagTexture.getSize().y);

    //Icon - Grain
    sf::Texture grainIconTexture;
    if (!grainIconTexture.loadFromFile((currentPath / "Resources" / "icon_grain.png").string())) {
        std::cerr << "Error loading grain icon texture." << std::endl;
    }
    sf::Sprite grainIconSprite(grainIconTexture);
    grainIconSprite.setScale(50.f / grainIconTexture.getSize().x, 50.f / grainIconTexture.getSize().y);
    grainIconSprite.setPosition(160, 75);

    //Icon - Metal
    sf::Texture metalIconTexture;
    if (!metalIconTexture.loadFromFile((currentPath / "Resources" / "icon_metal.png").string())) {
        std::cerr << "Error loading metal icon texture." << std::endl;
    }
    sf::Sprite metalIconSprite(metalIconTexture);
    metalIconSprite.setScale(50.f / metalIconTexture.getSize().x, 50.f / metalIconTexture.getSize().y);
    grainIconSprite.setPosition(200, 75);

    //Icon - Uranium
    sf::Texture uraniumIconTexture;
    if (!uraniumIconTexture.loadFromFile((currentPath / "Resources" / "icon_uranium.png").string())) {
        std::cerr << "Error loading uranium icon texture." << std::endl;
    }
    sf::Sprite uraniumIconSprite(uraniumIconTexture);
    uraniumIconSprite.setScale(50.f / uraniumIconTexture.getSize().x, 50.f / uraniumIconTexture.getSize().y);
    grainIconSprite.setPosition(300, 75);

    //Text
    sf::Text topBarText0("Food", font_arial, 20);
    sf::Text topBarText1("Metal", font_arial, 20);
    sf::Text topBarText2("Uranium", font_arial, 20);
    sf::Text topBarText3("Nukes", font_arial, 20);
    sf::Text topBarText4("Cities", font_arial, 20);
    //sf::Text topBarText5("Exit Game", font_arial, 20);
    topBarText0.setOutlineThickness(2);
    topBarText1.setOutlineThickness(2);
    topBarText2.setOutlineThickness(2);
    topBarText3.setOutlineThickness(2);
    topBarText4.setOutlineThickness(2);
    //topBarText5.setOutlineThickness(2);

    // Set the color of the rectangle
    sf::Color colorGray(128, 128, 128);

    //Rectangle
    // sf::RectangleShape topRectangle(sf::Vector2f(800, 100)); // Set the size of the rectangle
    // topRectangle.setPosition(0, 0);
    // topRectangle.setFillColor(colorGray);
    // topRectangle.setOutlineThickness(2);
    // topRectangle.setOutlineColor(sf::Color::Black);
    // Top
    sf::RectangleShape topFlagRectangle(sf::Vector2f(150, 100)); // Set the size of the rectangle
    topFlagRectangle.setPosition(2, 2);
    //topFlagRectangle.setFillColor(colorGray);
    topFlagRectangle.setOutlineThickness(2);
    topFlagRectangle.setOutlineColor(sf::Color::Black);

    sf::RectangleShape topCountryRectangle(sf::Vector2f(498, 50)); // Set the size of the rectangle
    topCountryRectangle.setPosition(154, 2);
    topCountryRectangle.setFillColor(colorGray);
    topCountryRectangle.setOutlineThickness(2);
    topCountryRectangle.setOutlineColor(sf::Color::Black);

    sf::RectangleShape topResourcesRectangle(sf::Vector2f(498, 50)); // Set the size of the rectangle
    topResourcesRectangle.setPosition(154, 52);
    topResourcesRectangle.setFillColor(colorGray);
    topResourcesRectangle.setOutlineThickness(2);
    topResourcesRectangle.setOutlineColor(sf::Color::Black);

    sf::RectangleShape topClockRectangle(sf::Vector2f(150, 100)); // Set the size of the rectangle
    topClockRectangle.setPosition(652, 2);
    topClockRectangle.setFillColor(colorGray);
    topClockRectangle.setOutlineThickness(2);
    topClockRectangle.setOutlineColor(sf::Color::Black);

    //Bottom
    sf::RectangleShape bottomLogRectangle(sf::Vector2f(150, 75)); // Set the size of the rectangle
    bottomLogRectangle.setPosition(2, 500);
    bottomLogRectangle.setFillColor(colorGray);
    bottomLogRectangle.setOutlineThickness(2);
    bottomLogRectangle.setOutlineColor(sf::Color::Black);

    sf::RectangleShape bottomChoiceRectangle(sf::Vector2f(500, 75)); // Set the size of the rectangle
    bottomChoiceRectangle.setPosition(152, 500);
    bottomChoiceRectangle.setFillColor(colorGray);
    bottomChoiceRectangle.setOutlineThickness(2);
    bottomChoiceRectangle.setOutlineColor(sf::Color::Black);

    sf::RectangleShape bottomInfoRectangle(sf::Vector2f(150, 75)); // Set the size of the rectangle
    bottomInfoRectangle.setPosition(652, 500);
    bottomInfoRectangle.setFillColor(colorGray);
    bottomInfoRectangle.setOutlineThickness(2);
    bottomInfoRectangle.setOutlineColor(sf::Color::Black);

    sf::RectangleShape bottomTooltipRectangle(sf::Vector2f(798, 25)); // Set the size of the rectangle
    bottomTooltipRectangle.setPosition(2, 575);
    bottomTooltipRectangle.setFillColor(colorGray);
    bottomTooltipRectangle.setOutlineThickness(2);
    bottomTooltipRectangle.setOutlineColor(sf::Color::Black);

    std::cout << "GameViewFunction\n";

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            }

            if (event.type == sf::Event::MouseButtonPressed) {

            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    if (showGameMenu(window)) {
                        return;
                    }
                }
            }
        }
        window.clear();
        window.draw(mapSprite);
        //window.draw(topRectangle);
        window.draw(topFlagRectangle);
        window.draw(topCountryRectangle);
        window.draw(topResourcesRectangle);
        window.draw(topClockRectangle);

        window.draw(bottomLogRectangle);
        window.draw(bottomChoiceRectangle);
        window.draw(bottomInfoRectangle);
        window.draw(bottomTooltipRectangle);

        window.draw(finlandFlagSprite);
        window.draw(grainIconSprite);
        window.draw(metalIconSprite);
        window.draw(uraniumIconSprite);

        window.display();
    }
}

//Function

bool showGameMenu(sf::RenderWindow& window) {
    std::filesystem::path currentPath = std::filesystem::path(__FILE__).parent_path().parent_path();

    // Define font and text for menu options
    sf::Font font_arial;
    if (!font_arial.loadFromFile((currentPath / "Resources" / "arial.ttf").string())) {
        std::cerr << "Error loading font." << std::endl;
    }
    sf::Color colorGray(128, 128, 128);

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
    gameMenuText0.setPosition((800 - gameMenuText0.getGlobalBounds().width) / 2, 180);
    gameMenuText1.setPosition((800 - gameMenuText1.getGlobalBounds().width) / 2, 230);
    gameMenuText2.setPosition((800 - gameMenuText2.getGlobalBounds().width) / 2, 280);
    gameMenuText3.setPosition((800 - gameMenuText3.getGlobalBounds().width) / 2, 330);
    gameMenuText4.setPosition((800 - gameMenuText4.getGlobalBounds().width) / 2, 380);
    gameMenuText5.setPosition((800 - gameMenuText5.getGlobalBounds().width) / 2, 430);

    float rectangleX = (gameMenuText4.getGlobalBounds().width) + 1;
    float rectangleY = (430 - 180 + 20 + 5);
    sf::RectangleShape gameMenuRectangle(sf::Vector2f(rectangleX, rectangleY)); // Set the size of the rectangle

    gameMenuRectangle.setPosition(((800 - gameMenuRectangle.getGlobalBounds().width) / 2) - 2, 180);

    // Set the color of the rectangle
    gameMenuRectangle.setFillColor(colorGray);
    gameMenuRectangle.setOutlineThickness(2);

    std::cout << "GameMenuFunction\n";

    int selectedOption = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            // Handle mouse movement for menu navigation
            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (gameMenuText0.getGlobalBounds().contains(mousePos)) {
                    selectedOption = 0;
                }
                else if (gameMenuText1.getGlobalBounds().contains(mousePos)) {
                    selectedOption = 1;
                }
                else if (gameMenuText2.getGlobalBounds().contains(mousePos)) {
                    selectedOption = 2;
                }
                else if (gameMenuText3.getGlobalBounds().contains(mousePos)) {
                    selectedOption = 3;
                }
                else if (gameMenuText4.getGlobalBounds().contains(mousePos)) {
                    selectedOption = 4;
                }
            }
            // Handle mouse click
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (gameMenuText0.getGlobalBounds().contains(mousePos)) {
                        // If "Start" is clicked, open a new window (e.g., showMap)
                        std::cout << "Mouse Resume\n";
                        window.clear();
                        return 0;
                    }
                    if (gameMenuText1.getGlobalBounds().contains(mousePos)) {
                        // If "Start" is clicked, open a new window (e.g., showMap)
                        std::cout << "Mouse Save\n";
                    }
                    if (gameMenuText2.getGlobalBounds().contains(mousePos)) {
                        // If "Start" is clicked, open a new window (e.g., showMap)
                        std::cout << "Mouse Load\n";
                    }
                    if (gameMenuText3.getGlobalBounds().contains(mousePos)) {
                        // If "Start" is clicked, open a new window (e.g., showMap)
                        std::cout << "Mouse Settings\n";
                    }
                    if (gameMenuText4.getGlobalBounds().contains(mousePos)) {
                        // If "Start" is clicked, open a new window (e.g., showMap)
                        std::cout << "Mouse Main Menu\n";
                        return 1;
                        break;
                    }
                    if (gameMenuText5.getGlobalBounds().contains(mousePos)) {
                        // If "Start" is clicked, open a new window (e.g., showMap)
                        std::cout << "Mouse Exit Game\n";
                        window.close();
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
    return 0;
}