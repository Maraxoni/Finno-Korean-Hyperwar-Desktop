#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "MenuView.h"
#include "GameView.h"
#include "Functions.h"
#include "Game.h"
#include "../Classes/Settings.h"
#include "../Classes/Country.h"
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

    //std::thread gameViewThread(showGame, std::ref(window), std::ref(Finland), std::ref(Korea));
    std::thread gameLogicThread(game, std::ref(Finland), std::ref(Korea));
    //std::thread clockThread(showClock, std::ref(window));
    std::cout << "Bazinga2\n";
    //gameViewThread.join();
    //clockThread.join();
    showGame(window, Finland, Korea);
    gameLogicThread.join();
    std::cout << "Bazinga3\n";

}

void showGame(sf::RenderWindow& window, Country& PlayerCountry, Country& EnemyCountry) {
    extern Settings globalSettings;
    std::filesystem::path currentPath = std::filesystem::path(__FILE__).parent_path().parent_path();
    std::mutex mtx;
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

    //Flag - Korea
    sf::Texture koreaFlagTexture;
    if (!koreaFlagTexture.loadFromFile((currentPath / "Resources" / "Flag_of_South_Korea.png").string())) {
        std::cerr << "Error loading Korea flag texture." << std::endl;
    }
    sf::Sprite flagSprite(finlandFlagTexture);
    sf::Text countryName("Proto-Finnic Khaganate", font_arial, 20);

    if (globalSettings.getChosenCountry() == "Finland") {
        flagSprite.setTexture(finlandFlagTexture);
        flagSprite.setScale(150.f / finlandFlagTexture.getSize().x, 100.f / finlandFlagTexture.getSize().y);
        countryName.setString("Proto-Finnic Khaganate");
    }
    else {
        flagSprite.setTexture(koreaFlagTexture);
        flagSprite.setScale(150.f / koreaFlagTexture.getSize().x, 100.f / koreaFlagTexture.getSize().y);
        countryName.setString("Great Hwan Empire");
    }
    flagSprite.setPosition(2, 2);
    countryName.setOutlineThickness(2);
    countryName.setPosition(348, 25 / 2);

    //Icon - Grain
    sf::Texture grainIconTexture;
    if (!grainIconTexture.loadFromFile((currentPath / "Resources" / "icon_grain.png").string())) {
        std::cerr << "Error loading grain icon texture." << std::endl;
    }
    sf::Sprite grainIconSprite(grainIconTexture);
    grainIconSprite.setScale(25.f / grainIconTexture.getSize().x, 25.f / grainIconTexture.getSize().y);
    grainIconSprite.setPosition(210, 50 + (25 / 2));

    //Icon - Metal
    sf::Texture metalIconTexture;
    if (!metalIconTexture.loadFromFile((currentPath / "Resources" / "icon_metal.png").string())) {
        std::cerr << "Error loading metal icon texture." << std::endl;
    }
    sf::Sprite metalIconSprite(metalIconTexture);
    metalIconSprite.setScale(25.f / metalIconTexture.getSize().x, 25.f / metalIconTexture.getSize().y);
    metalIconSprite.setPosition(293, 50 + (25 / 2));

    //Icon - Uranium
    sf::Texture uraniumIconTexture;
    if (!uraniumIconTexture.loadFromFile((currentPath / "Resources" / "icon_uranium.png").string())) {
        std::cerr << "Error loading uranium icon texture." << std::endl;
    }
    sf::Sprite uraniumIconSprite(uraniumIconTexture);
    uraniumIconSprite.setScale(25.f / uraniumIconTexture.getSize().x, 25.f / uraniumIconTexture.getSize().y);
    uraniumIconSprite.setPosition(376, 50 + (25 / 2));

    sf::Texture cityIconTexture;
    if (!cityIconTexture.loadFromFile((currentPath / "Resources" / "icon_city.png").string())) {
        std::cerr << "Error loading city icon texture." << std::endl;
    }

    sf::Texture cityDestroyedIconTexture;
    if (!cityDestroyedIconTexture.loadFromFile((currentPath / "Resources" / "icon_city_destroyed.png").string())) {
        std::cerr << "Error loading city_destroyed icon texture." << std::endl;
    }

    sf::Texture cityUpgradingIconTexture;
    if (!cityDestroyedIconTexture.loadFromFile((currentPath / "Resources" / "icon_city_upgrading.png").string())) {
        std::cerr << "Error loading city_upgrading icon texture." << std::endl;
    }

    // Create sprite tables for each "tab"
    sf::Sprite cityFinlandIconSprites[5];
    sf::Sprite cityKoreaIconSprites[5];

    // Initialize sprites in the first "tab" (cityFinland)
    for (int i = 0; i < 5; ++i) {
        cityFinlandIconSprites[i].setTexture(cityIconTexture);
        cityFinlandIconSprites[i].setScale(15.f / cityIconTexture.getSize().x, 15.f / cityIconTexture.getSize().y);
    }

    // Initialize sprites in the second "tab" (cityKorea)
    for (int i = 0; i < 5; ++i) {
        cityKoreaIconSprites[i].setTexture(cityIconTexture);
        cityKoreaIconSprites[i].setScale(15.f / cityIconTexture.getSize().x, 15.f / cityIconTexture.getSize().y);
    }

    cityFinlandIconSprites[0].setPosition(180, 185);
    cityFinlandIconSprites[1].setPosition(180, 215);
    cityFinlandIconSprites[2].setPosition(100, 260);
    cityFinlandIconSprites[3].setPosition(145, 290);
    cityFinlandIconSprites[4].setPosition(180, 310);
    cityKoreaIconSprites[0].setPosition(550, 340);
    cityKoreaIconSprites[1].setPosition(520, 380);
    cityKoreaIconSprites[2].setPosition(420, 380);
    cityKoreaIconSprites[3].setPosition(440, 300);
    cityKoreaIconSprites[4].setPosition(490, 220);

    sf::Text cityFinlandNames[5];
    sf::Text cityKoreaNames[5];

    cityFinlandNames[0].setString("Helsinki");
    cityFinlandNames[1].setString("Tallinn");
    cityFinlandNames[2].setString("Den Haag");
    cityFinlandNames[3].setString("Rome");
    cityFinlandNames[4].setString("Istanbul");
    cityKoreaNames[0].setString("Seul");
    cityKoreaNames[1].setString("Nanjing");
    cityKoreaNames[2].setString("Lhasa");
    cityKoreaNames[3].setString("Tuuva");
    cityKoreaNames[4].setString("Yakuck");

    cityFinlandNames[0].setPosition(cityFinlandIconSprites[0].getPosition().x + cityFinlandIconSprites[0].getLocalBounds().width / 2, cityFinlandIconSprites[0].getPosition().y + cityFinlandIconSprites[0].getLocalBounds().height);
    cityFinlandNames[1].setPosition(100, 200);
    cityFinlandNames[2].setPosition(100, 200);
    cityFinlandNames[3].setPosition(100, 200);
    cityFinlandNames[4].setPosition(100, 200);
    cityKoreaNames[0].setPosition(100, 200);
    cityKoreaNames[1].setPosition(100, 200);
    cityKoreaNames[2].setPosition(100, 200);
    cityKoreaNames[3].setPosition(100, 200);
    cityKoreaNames[4].setPosition(100, 200);

    //Text
    sf::Text topBarText0("Food", font_arial, 20);
    topBarText0.setOutlineThickness(2);
    topBarText0.setPosition(255, (75 + 50) / 2);
    sf::Text topBarText1("Metal", font_arial, 20);
    topBarText1.setOutlineThickness(2);
    topBarText1.setPosition(348, (75 + 50) / 2);
    sf::Text topBarText2("Uranium", font_arial, 20);
    topBarText2.setOutlineThickness(2);
    topBarText2.setPosition(431, (75 + 50) / 2);
    sf::Text topBarText3("Nukes", font_arial, 20);
    topBarText3.setOutlineThickness(2);
    topBarText3.setPosition(550, (75 + 50) / 2);
    sf::Text topBarText4("Cities", font_arial, 20);
    topBarText4.setOutlineThickness(2);
    topBarText4.setPosition(600, (75 + 50) / 2);



    // Set the color of the rectangle
    sf::Color colorGray(128, 128, 128);

    // Top
    sf::RectangleShape topFlagRectangle(sf::Vector2f(150, 100)); // Set the size of the rectangle
    topFlagRectangle.setPosition(2, 2);
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
    int refresh_variable = 1;
    int stockpile_status_food = 0;
    int stockpile_status_metal = 0;
    int stockpile_status_uranium = 0;
    int selected_city = 0;
    int selected_menu = 0;
    int selected_tab = 0;
    while (window.isOpen()) {

        if ((stockpile_status_food != PlayerCountry.getMetalStockpile()) || (stockpile_status_metal != PlayerCountry.getMetalStockpile()) || (stockpile_status_uranium != PlayerCountry.getMetalStockpile())) {
            refresh_variable = 1;
        }
        stockpile_status_food = PlayerCountry.getMetalStockpile();
        stockpile_status_metal = PlayerCountry.getMetalStockpile();
        stockpile_status_uranium = PlayerCountry.getMetalStockpile();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                refresh_variable = 1;
                for(int i = 0; i < PlayerCountry.getNumberOfCities(); i++){
                    if(cityFinlandIconSprites[i].getGlobalBounds().contains(mousePos)){
                        selected_city = i;
                    }
                    if(cityKoreaIconSprites[i].getGlobalBounds().contains(mousePos)){
                        selected_city = i + 5;
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (cityFinlandIconSprites[0].getGlobalBounds().contains(mousePos)) {
                        std::cout << "cityFinland0IconSprite\n";
                        showMap(window);
                    }
                    if (cityFinlandIconSprites[1].getGlobalBounds().contains(mousePos)) {
                        std::cout << "cityFinland1IconSprite\n";
                    }
                    if (cityFinlandIconSprites[2].getGlobalBounds().contains(mousePos)) {
                        std::cout << "cityFinland2IconSprite\n";
                    }
                    if (cityFinlandIconSprites[3].getGlobalBounds().contains(mousePos)) {
                        std::cout << "cityFinland3IconSprite\n";
                    }
                    if (cityFinlandIconSprites[4].getGlobalBounds().contains(mousePos)) {
                        std::cout << "cityFinland4IconSprite\n";
                        return;
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    if (showGameMenu(window)) {
                        return;
                    }
                }
                else if (event.key.code == sf::Keyboard::Up) {
                    selected_tab = 0;
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    selected_tab = 1;
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    selected_city = (selected_city + 1) % 10;
                }
                else if (event.key.code == sf::Keyboard::Left) {
                    selected_city = (selected_city - 1 + 10) % 10;
                }
                else if (event.key.code == globalSettings.getKeyConfirm()) {
                    // If Enter key is pressed, perform the action associated with the selected option
                    switch (selected_city) {
                    case 0:
                        std::cout << "Enter New Game\n";
                        showMap(window);
                        break;
                    case 1:
                        showLoad(window);
                        break;
                    case 2:
                        showSettings(window);
                        break;
                    case 3:
                        showCredits(window);
                        break;
                    case 4:
                        std::cout << "Enter Exit\n";
                        return;
                        break;
                    }
                }
            }
        }

        if (refresh_variable) {
            topBarText0.setString(std::to_string(PlayerCountry.getFoodStockpile()) + "+(" + std::to_string(PlayerCountry.getFoodIncome()) + ")");
            topBarText1.setString(std::to_string(PlayerCountry.getMetalStockpile()) + "+(" + std::to_string(PlayerCountry.getMetalIncome()) + ")");
            topBarText2.setString(std::to_string(PlayerCountry.getUraniumStockpile()) + "+(" + std::to_string(PlayerCountry.getUraniumIncome()) + ")");
            topBarText3.setString("" + std::to_string(PlayerCountry.getFoodIncome()));
            topBarText4.setString("" + std::to_string(PlayerCountry.getFoodIncome()));
            window.clear();
            window.draw(mapSprite);
            window.draw(topFlagRectangle);
            window.draw(topCountryRectangle);
            window.draw(topResourcesRectangle);
            window.draw(topClockRectangle);
            window.draw(flagSprite);
            window.draw(countryName);
            window.draw(bottomLogRectangle);
            window.draw(bottomChoiceRectangle);
            window.draw(bottomInfoRectangle);
            window.draw(bottomTooltipRectangle);

            window.draw(grainIconSprite);
            window.draw(topBarText0);
            window.draw(metalIconSprite);
            window.draw(topBarText1);
            window.draw(uraniumIconSprite);
            window.draw(topBarText2);

            window.draw(topBarText3);
            window.draw(topBarText4);

            for (int u = 0; u < PlayerCountry.getNumberOfCities(); u++) {
                window.draw(cityFinlandIconSprites[u]);
                window.draw(cityFinlandNames[u]);
                window.draw(cityKoreaIconSprites[u]);
                window.draw(cityKoreaNames[u]);
            }

            switch (selected_tab) {
            case 0:
                switch (selected_city) {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    break;
                case 6:
                    break;
                case 7:
                    break;
                case 8:
                    break;
                case 9:
                    break;
                default:
                    break;
                }
                break;
            case 1:
                switch (selected_city) {

                }
                break;
            default:
                break;
            }


            window.display();
        }
        refresh_variable = 0;
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
                        showSave(window);
                    }
                    if (gameMenuText2.getGlobalBounds().contains(mousePos)) {
                        // If "Start" is clicked, open a new window (e.g., showMap)
                        std::cout << "Mouse Load\n";
                        showLoad(window);
                    }
                    if (gameMenuText3.getGlobalBounds().contains(mousePos)) {
                        // If "Start" is clicked, open a new window (e.g., showMap)
                        std::cout << "Mouse Settings\n";
                        showSettings(window);
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