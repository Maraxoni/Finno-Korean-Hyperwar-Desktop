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

    std::thread gameLogicThread(game, std::ref(window), std::ref(*PlayerCountry), std::ref(*EnemyCountry));
    std::cout << "Bazinga2\n";

    showGame(window, *PlayerCountry, *EnemyCountry);
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

    if (globalSettings.getChosenCountry() == "Korea") {
        flagSprite.setTexture(koreaFlagTexture);
        flagSprite.setScale(150.f / koreaFlagTexture.getSize().x, 100.f / koreaFlagTexture.getSize().y);
        countryName.setString("Great Hwan Empire");
    }
    else {
        flagSprite.setTexture(finlandFlagTexture);
        flagSprite.setScale(150.f / finlandFlagTexture.getSize().x, 100.f / finlandFlagTexture.getSize().y);
        countryName.setString("Proto-Finnic Khaganate");
    }
    flagSprite.setPosition(2, 2);

    countryName.setOutlineThickness(2);
    countryName.setPosition((800 - countryName.getGlobalBounds().width) / 2, 25 / 2);

    //Icon - Grain
    sf::Texture grainIconTexture;
    if (!grainIconTexture.loadFromFile((currentPath / "Resources" / "icon_grain.png").string())) {
        std::cerr << "Error loading grain icon texture." << std::endl;
    }
    sf::Sprite grainIconSprite(grainIconTexture);
    grainIconSprite.setScale(25.f / grainIconTexture.getSize().x, 25.f / grainIconTexture.getSize().y);
    grainIconSprite.setPosition(190, 50 + (25 / 2));
    sf::Sprite grainMenuIconSprite(grainIconTexture);
    grainMenuIconSprite.setScale(40.f / grainIconTexture.getSize().x, 40.f / grainIconTexture.getSize().y);
    grainMenuIconSprite.setPosition(225, 500 + (40 / 2));
    sf::Sprite grainLogIconSprite(grainIconTexture);
    grainLogIconSprite.setScale(15.f / grainIconTexture.getSize().x, 15.f / grainIconTexture.getSize().y);

    //Icon - Metal
    sf::Texture metalIconTexture;
    if (!metalIconTexture.loadFromFile((currentPath / "Resources" / "icon_metal.png").string())) {
        std::cerr << "Error loading metal icon texture." << std::endl;
    }
    sf::Sprite metalIconSprite(metalIconTexture);
    metalIconSprite.setScale(25.f / metalIconTexture.getSize().x, 25.f / metalIconTexture.getSize().y);
    metalIconSprite.setPosition(315, 50 + (25 / 2));
    sf::Sprite metalMenuIconSprite(metalIconTexture);
    metalMenuIconSprite.setScale(40.f / metalIconTexture.getSize().x, 40.f / metalIconTexture.getSize().y);
    metalMenuIconSprite.setPosition(375, 500 + (40 / 2));
    sf::Sprite metalLogIconSprite(metalIconTexture);
    metalLogIconSprite.setScale(15.f / metalIconTexture.getSize().x, 15.f / metalIconTexture.getSize().y);

    //Icon - Uranium
    sf::Texture uraniumIconTexture;
    if (!uraniumIconTexture.loadFromFile((currentPath / "Resources" / "icon_uranium.png").string())) {
        std::cerr << "Error loading uranium icon texture." << std::endl;
    }
    sf::Sprite uraniumIconSprite(uraniumIconTexture);
    uraniumIconSprite.setScale(25.f / uraniumIconTexture.getSize().x, 25.f / uraniumIconTexture.getSize().y);
    uraniumIconSprite.setPosition(450, 50 + (25 / 2));
    sf::Sprite uraniumMenuIconSprite(uraniumIconTexture);
    uraniumMenuIconSprite.setScale(40.f / uraniumIconTexture.getSize().x, 40.f / uraniumIconTexture.getSize().y);
    uraniumMenuIconSprite.setPosition(525, 500 + (40 / 2));
    sf::Sprite uraniumLogIconSprite(uraniumIconTexture);
    uraniumLogIconSprite.setScale(15.f / uraniumIconTexture.getSize().x, 15.f / uraniumIconTexture.getSize().y);


    //Nuke
    sf::Texture nukeIconTexture;
    if (!nukeIconTexture.loadFromFile((currentPath / "Resources" / "nuke_icon.png").string())) {
        std::cerr << "Error loading nukeIcon texture." << std::endl;
    }
    sf::Sprite nukeIconSprite(nukeIconTexture);
    nukeIconSprite.setScale(40.f / nukeIconTexture.getSize().x, 40.f / nukeIconTexture.getSize().y);
    sf::Sprite nukeMenuIconSprite(nukeIconTexture);
    nukeMenuIconSprite.setScale(25.f / nukeIconTexture.getSize().x, 25.f / nukeIconTexture.getSize().y);

    //Nuke
    sf::Texture cityBombedIconTexture;
    if (!cityBombedIconTexture.loadFromFile((currentPath / "Resources" / "bomb_city.png").string())) {
        std::cerr << "Error loading cityBombedIcon texture." << std::endl;
    }
    sf::Sprite cityBombedIconSprite(cityBombedIconTexture);
    cityBombedIconSprite.setScale(40.f / cityBombedIconTexture.getSize().x, 40.f / cityBombedIconTexture.getSize().y);


    //Nuke
    sf::Texture nukeBuildIconTexture;
    if (!nukeBuildIconTexture.loadFromFile((currentPath / "Resources" / "build_nuke_icon.png").string())) {
        std::cerr << "Error loading nukeBuild texture." << std::endl;
    }
    sf::Sprite nukeBuildIconflagSprite(nukeBuildIconTexture);
    nukeBuildIconflagSprite.setScale(40.f / nukeBuildIconTexture.getSize().x, 40.f / nukeBuildIconTexture.getSize().y);

    nukeBuildIconflagSprite.setPosition(225, 500 + (40 / 2));
    nukeIconSprite.setPosition(375, 500 + (40 / 2));
    cityBombedIconSprite.setPosition(525, 500 + (40 / 2));

    // Create sprite tables for each "tab"
    sf::Sprite cityFinlandIconSprites[5];
    sf::Sprite cityKoreaIconSprites[5];
    sf::Sprite cityFinlandDestroyedIconSprites[5];
    sf::Sprite cityKoreaDestroyedIconSprites[5];
    sf::Sprite cityFinlandUpgradedIconSprites[5];
    sf::Sprite cityKoreaUpgradedIconSprites[5];
    sf::Sprite cityFinlandBombedIconSprites[5];
    sf::Sprite cityKoreaBombedIconSprites[5];

    sf::Texture cityIconTexture;
    if (!cityIconTexture.loadFromFile((currentPath / "Resources" / "icon_city.png").string())) {
        std::cerr << "Error loading city icon texture." << std::endl;
    }
    sf::Sprite citiesSprite(cityIconTexture);
    citiesSprite.setScale(25.f / cityIconTexture.getSize().x, 25.f / cityIconTexture.getSize().y);

    citiesSprite.setPosition(610, 50 + (25 / 2));
    nukeMenuIconSprite.setPosition(570, 50 + (25 / 2));

    //city
    for (int i = 0; i < 5; ++i) {
        cityFinlandIconSprites[i].setTexture(cityIconTexture);
        cityFinlandIconSprites[i].setScale(15.f / cityIconTexture.getSize().x, 15.f / cityIconTexture.getSize().y);
        cityKoreaIconSprites[i].setTexture(cityIconTexture);
        cityKoreaIconSprites[i].setScale(15.f / cityIconTexture.getSize().x, 15.f / cityIconTexture.getSize().y);
    }

    //sample
    int numFramesX = 0;
    int numFramesY = 0;
    int frameWidth = 0;
    int frameHeight = 0;

    //upg
    sf::Texture cityUpgradingIconTexture;
    if (!cityUpgradingIconTexture.loadFromFile((currentPath / "Resources" / "city_construction_sprite_pack.png").string())) {
        std::cerr << "Error loading city_construction icon texture." << std::endl;
    }
    numFramesX = 4;
    numFramesY = 1;
    frameWidth = cityUpgradingIconTexture.getSize().x / numFramesX; // numFrames is the number of frames in the sprite sheet
    frameHeight = cityUpgradingIconTexture.getSize().y / numFramesY;
    std::vector<sf::IntRect> upgradingFrames;
    for (int i = 0; i < numFramesX; ++i) {
        upgradingFrames.push_back(sf::IntRect(i * frameWidth, 0, frameWidth, frameHeight));
    }

    for (int i = 0; i < 5; ++i) {
        cityFinlandUpgradedIconSprites[i].setTexture(cityUpgradingIconTexture);
        cityFinlandUpgradedIconSprites[i].setScale(15.f / frameWidth, 15.f / frameHeight);
        cityKoreaUpgradedIconSprites[i].setTexture(cityUpgradingIconTexture);
        cityKoreaUpgradedIconSprites[i].setScale(15.f / frameWidth, 15.f / frameHeight);
    }

    //des
    sf::Texture cityDestroyedIconTexture;
    if (!cityDestroyedIconTexture.loadFromFile((currentPath / "Resources" / "city_destroyed_sprite_pack.png").string())) {
        std::cerr << "Error loading city_destroyed sprite pack texture." << std::endl;
    }
    numFramesX = 3;
    numFramesY = 3;
    frameWidth = cityDestroyedIconTexture.getSize().x / numFramesX; // numFrames is the number of frames in the sprite sheet
    frameHeight = cityDestroyedIconTexture.getSize().y / numFramesY;
    std::vector<sf::IntRect> destroyedFrames;
    for (int i = 0; i < numFramesX; ++i) {
        destroyedFrames.push_back(sf::IntRect(0, i * frameHeight, frameWidth, frameHeight));
    }
    for (int i = 0; i < 5; ++i) {
        cityFinlandDestroyedIconSprites[i].setTexture(cityDestroyedIconTexture);
        cityFinlandDestroyedIconSprites[i].setScale(15.f / frameWidth, 15.f / frameHeight);
        cityKoreaDestroyedIconSprites[i].setTexture(cityDestroyedIconTexture);
        cityKoreaDestroyedIconSprites[i].setScale(15.f / frameWidth, 15.f / frameHeight);
    }

    //exp
    sf::Texture explosionTexture;
    if (!explosionTexture.loadFromFile((currentPath / "Resources" / "explosion_sprite_pack.png").string())) {
        std::cerr << "Error loading explosion sprite pack texture." << std::endl;
    }
    numFramesX = 5;
    numFramesY = 3;
    frameWidth = explosionTexture.getSize().x / numFramesX; // numFrames is the number of frames in the sprite sheet
    frameHeight = explosionTexture.getSize().y / numFramesY;
    std::vector<sf::IntRect> explosionFrames;
    for (int i = 0; i < numFramesX; ++i) {
        explosionFrames.push_back(sf::IntRect(i * frameWidth, 0, frameWidth, frameHeight));
    }
    for (int i = 0; i < 5; ++i) {
        cityFinlandBombedIconSprites[i].setTexture(explosionTexture);
        cityFinlandBombedIconSprites[i].setScale(15.f / frameWidth, 15.f / frameHeight);
        cityKoreaBombedIconSprites[i].setTexture(explosionTexture);
        cityKoreaBombedIconSprites[i].setScale(15.f / frameWidth, 15.f / frameHeight);
    }

    sf::Sprite soldierFSprites[3];
    sf::Sprite soldierKSprites[3];

    //soldier
    sf::Texture soldierTexture;
    if (!soldierTexture.loadFromFile((currentPath / "Resources" / "soldier_sprite_pack.png").string())) {
        std::cerr << "Error loading soldier texture." << std::endl;
    }
    numFramesX = 8;
    numFramesY = 6;
    frameWidth = soldierTexture.getSize().x / numFramesX; // numFrames is the number of frames in the sprite sheet
    frameHeight = soldierTexture.getSize().y / numFramesY;
    std::vector<sf::IntRect> soldierFFrames;
    std::vector<sf::IntRect> soldierKFrames;
    for (int i = 0; i < numFramesY; ++i) {
        soldierFFrames.push_back(sf::IntRect(6 * frameWidth, i * frameHeight, frameWidth, frameHeight));
        soldierKFrames.push_back(sf::IntRect(2 * frameWidth, i * frameHeight, frameWidth, frameHeight));
    }
    for (int i = 0; i < 3; ++i) {
        soldierFSprites[i].setTexture(soldierTexture);
        soldierFSprites[i].setScale(15.f / frameWidth, 15.f / frameHeight);
        soldierKSprites[i].setTexture(soldierTexture);
        soldierKSprites[i].setScale(15.f / frameWidth, 15.f / frameHeight);
    }

    soldierFSprites[0].setPosition(330, 170);
    soldierFSprites[1].setPosition(340, 220);
    soldierFSprites[2].setPosition(330, 270);
    soldierKSprites[0].setPosition(390, 190);
    soldierKSprites[1].setPosition(400, 240);
    soldierKSprites[2].setPosition(380, 290);

    //hourglassTexture
    sf::Texture hourglassTexture;
    sf::Sprite hourglassSprite;
    if (!hourglassTexture.loadFromFile((currentPath / "Resources" / "hourglass_sprite_pack.png").string())) {
        std::cerr << "Error loading hourglass texture." << std::endl;
    }
    numFramesX = 3;
    numFramesY = 2;
    frameWidth = hourglassTexture.getSize().x / numFramesX; // numFrames is the number of frames in the sprite sheet
    frameHeight = hourglassTexture.getSize().y / numFramesY;
    std::vector<sf::IntRect> hourglassFrames;
    for (int i = 0; i < numFramesY; ++i) {
        for (int j = 0; j < numFramesX; ++j) {
            hourglassFrames.push_back(sf::IntRect(j * frameWidth, i * frameHeight, frameWidth, frameHeight));
        }
    }

    hourglassSprite.setTexture(hourglassTexture);
    hourglassSprite.setScale(80.f / frameWidth, 80.f / frameHeight);
    hourglassSprite.setPosition(685, 10);

    // Initialize sprites in the first "tab" (cityFinland)

    // f0
    cityFinlandIconSprites[0].setPosition(180, 185);
    cityFinlandDestroyedIconSprites[0].setPosition(180, 185);
    cityFinlandUpgradedIconSprites[0].setPosition(180, 185);
    cityFinlandBombedIconSprites[0].setPosition(180, 185);
    // f1
    cityFinlandIconSprites[1].setPosition(180, 215);
    cityFinlandDestroyedIconSprites[1].setPosition(180, 215);
    cityFinlandUpgradedIconSprites[1].setPosition(180, 215);
    cityFinlandBombedIconSprites[1].setPosition(180, 215);
    // f2
    cityFinlandIconSprites[2].setPosition(100, 260);
    cityFinlandDestroyedIconSprites[2].setPosition(100, 260);
    cityFinlandUpgradedIconSprites[2].setPosition(100, 260);
    cityFinlandBombedIconSprites[2].setPosition(100, 260);
    // f3
    cityFinlandIconSprites[3].setPosition(145, 290);
    cityFinlandDestroyedIconSprites[3].setPosition(145, 290);
    cityFinlandUpgradedIconSprites[3].setPosition(145, 290);
    cityFinlandBombedIconSprites[3].setPosition(145, 290);
    // f4
    cityFinlandIconSprites[4].setPosition(180, 310);
    cityFinlandDestroyedIconSprites[4].setPosition(180, 310);
    cityFinlandUpgradedIconSprites[4].setPosition(180, 310);
    cityFinlandBombedIconSprites[4].setPosition(180, 310);
    // k0
    cityKoreaIconSprites[0].setPosition(550, 340);
    cityKoreaDestroyedIconSprites[0].setPosition(550, 340);
    cityKoreaUpgradedIconSprites[0].setPosition(550, 340);
    cityKoreaBombedIconSprites[0].setPosition(550, 340);
    // k1
    cityKoreaIconSprites[1].setPosition(520, 380);
    cityKoreaDestroyedIconSprites[1].setPosition(520, 380);
    cityKoreaUpgradedIconSprites[1].setPosition(520, 380);
    cityKoreaBombedIconSprites[1].setPosition(520, 380);
    // k2
    cityKoreaIconSprites[2].setPosition(420, 380);
    cityKoreaDestroyedIconSprites[2].setPosition(420, 380);
    cityKoreaUpgradedIconSprites[2].setPosition(420, 380);
    cityKoreaBombedIconSprites[2].setPosition(420, 380);
    // k3
    cityKoreaIconSprites[3].setPosition(440, 300);
    cityKoreaDestroyedIconSprites[3].setPosition(440, 300);
    cityKoreaUpgradedIconSprites[3].setPosition(440, 300);
    cityKoreaBombedIconSprites[3].setPosition(440, 300);
    // k4
    cityKoreaIconSprites[4].setPosition(490, 220);
    cityKoreaDestroyedIconSprites[4].setPosition(490, 220);
    cityKoreaUpgradedIconSprites[4].setPosition(490, 220);
    cityKoreaBombedIconSprites[4].setPosition(490, 220);

    //Text
    sf::Text topBarText0("Food", font_arial, 16);
    topBarText0.setOutlineThickness(2);
    topBarText0.setPosition(220, (80 + 50) / 2);
    sf::Text topBarText1("Metal", font_arial, 16);
    topBarText1.setOutlineThickness(2);
    topBarText1.setPosition(345, (80 + 50) / 2);
    sf::Text topBarText2("Uranium", font_arial, 16);
    topBarText2.setOutlineThickness(2);
    topBarText2.setPosition(480, (80 + 50) / 2);
    sf::Text topBarText3("Nukes", font_arial, 20);
    topBarText3.setOutlineThickness(2);
    topBarText3.setPosition(598, (75 + 50) / 2);
    sf::Text topBarText4("Cities", font_arial, 20);
    topBarText4.setOutlineThickness(2);
    topBarText4.setPosition(636, (75 + 50) / 2);
    sf::Text logBarText0("0", font_arial, 20);
    logBarText0.setOutlineThickness(2);
    logBarText0.setPosition(30, 500);
    sf::Text logBarText1("0", font_arial, 20);
    logBarText1.setOutlineThickness(2);
    logBarText1.setPosition(30, 520);
    sf::Text logBarText2("0", font_arial, 20);
    logBarText2.setOutlineThickness(2);
    logBarText2.setPosition(30, 540);

    // Set the color of the rectangle
    sf::Color outlineColor(255, 255, 0);
    sf::Color outlineIconColor(255, 0, 0);
    sf::Color colorGray(128, 128, 128);
    float outlineThickness = 2.0f;
    sf::RectangleShape outlineShape(sf::Vector2f(cityKoreaIconSprites[0].getGlobalBounds().width, cityKoreaIconSprites[0].getGlobalBounds().height));
    sf::RectangleShape outlineCityShape(sf::Vector2f(cityKoreaIconSprites[0].getGlobalBounds().width, cityKoreaIconSprites[0].getGlobalBounds().height));
    sf::RectangleShape outlineIconShape(sf::Vector2f(uraniumMenuIconSprite.getGlobalBounds().width, uraniumMenuIconSprite.getGlobalBounds().height));
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

    int currentSoldierFrame = 0;
    int currentFrameDestroyedCity = 0;
    int currentFrameUpgradedCity = 0;
    int currentFrameBombedCity = 0;
    int currentFrameHourglass = 0;
    sf::Clock cityAnimationClock;
    sf::Clock soldierAnimationClock;
    float frameDuration = 0.4f;

    std::cout << "GameViewFunction\n";
    int refresh_variable = 1;
    int stockpile_status_food = 0;
    int stockpile_status_metal = 0;
    int stockpile_status_uranium = 0;
    int selected_city = -1;
    int selected_icon = -1;
    int selected_tab = 0;

    sf::Text logInfoText0("", font_arial, 16);
    logInfoText0.setOutlineThickness(2);
    logInfoText0.setPosition(660, 500);
    sf::Text logCostText0("", font_arial, 16);
    logCostText0.setOutlineThickness(2);
    logCostText0.setPosition(680, 518);
    sf::Text logCostText1("", font_arial, 16);
    logCostText1.setOutlineThickness(2);
    logCostText1.setPosition(680, 534);
    sf::Text logCostText2("", font_arial, 16);
    logCostText2.setOutlineThickness(2);
    logCostText2.setPosition(680, 550);

    grainLogIconSprite.setPosition(660, 522);
    metalLogIconSprite.setPosition(660, 538);
    uraniumLogIconSprite.setPosition(660, 554);

    int log_cost_grain = 0;
    int log_cost_metal = 0;
    int log_cost_uranium = 0;

    outlineCityShape.setFillColor(colorGray);
    outlineIconShape.setFillColor(colorGray);
    outlineShape.setFillColor(colorGray);

    int cityBombedTimer[10];
    int cityUpgradedTimer[10];

    sf::Text bottomText("", font_arial, 15);
    bottomText.setPosition((800 - bottomText.getGlobalBounds().width) / 2, 575);
    bottomText.setOutlineThickness(1);

    sf::Text cityFinlandNames[5];
    sf::Text cityKoreaNames[5];

    sf::Text bazinga("", font_arial, 16);

    int fontSize = 7; // Adjust this according to your needs
    for (int i = 0; i < 5; ++i) {
        cityFinlandNames[i].setFont(font_arial);
        cityKoreaNames[i].setFont(font_arial);
        cityFinlandNames[i].setCharacterSize(fontSize);
        cityKoreaNames[i].setCharacterSize(fontSize);
        cityFinlandNames[i].setOutlineThickness(1);
        cityKoreaNames[i].setOutlineThickness(1);
    }

    cityFinlandNames[0].setString("Helsinki");
    cityFinlandNames[1].setString("Tallinn");
    cityFinlandNames[2].setString("Den Haag");
    cityFinlandNames[3].setString("Istria");
    cityFinlandNames[4].setString("Istanbul");
    cityKoreaNames[0].setString("Seul");
    cityKoreaNames[1].setString("Nanjing");
    cityKoreaNames[2].setString("Lhasa");
    cityKoreaNames[3].setString("Tuuva");
    cityKoreaNames[4].setString("Yakuck");

    for (int i = 0; i < 5; ++i) {
        cityFinlandNames[i].setPosition(cityFinlandIconSprites[i].getPosition().x - cityFinlandNames[i].getLocalBounds().width / 2, cityFinlandIconSprites[i].getPosition().y + 15);
        cityKoreaNames[i].setPosition(cityKoreaIconSprites[i].getPosition().x - cityKoreaNames[i].getLocalBounds().width / 2, cityKoreaIconSprites[i].getPosition().y + 15);
    }

    while (window.isOpen()) {
        bottomText.setString("Key Up: " + std::to_string(globalSettings.getKeyUp()) +
            " Key Down: " + std::to_string(globalSettings.getKeyDown()) +
            " Key Right: " + std::to_string(globalSettings.getKeyRight()) +
            " Key Left: " + std::to_string(globalSettings.getKeyLeft()));

        bottomText.setString(bottomText.getString() +
            " Key Confirm: " + std::to_string(globalSettings.getKeyConfirm()) +
            " Key Tab: " + std::to_string(globalSettings.getKeyTab()) +
            " Key Escape: " + std::to_string(globalSettings.getKeyEscape()));
        bottomText.setPosition((800 - bottomText.getGlobalBounds().width) / 2, 575);

        refresh_variable = 1;
        sf::Color originalColor = sf::Color::Black;
        sf::Color highlightColor = sf::Color(255, 255, 0); // Yellow highlight color
        sf::Color currentColor = originalColor;

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
                if (grainMenuIconSprite.getGlobalBounds().contains(mousePos)) {
                    selected_icon = 10;
                    refresh_variable = 1;
                }
                else if (metalMenuIconSprite.getGlobalBounds().contains(mousePos)) {
                    selected_icon = 11;
                    refresh_variable = 1;
                }
                else if (uraniumMenuIconSprite.getGlobalBounds().contains(mousePos)) {
                    selected_icon = 12;
                    refresh_variable = 1;
                }
                else for (int i = 0; i < 5; i++) {
                    if (cityFinlandIconSprites[i].getGlobalBounds().contains(mousePos)) {
                        selected_icon = i;
                        refresh_variable = 1;
                        break;
                    }

                    if (cityKoreaIconSprites[i].getGlobalBounds().contains(mousePos)) {
                        selected_icon = i + 5;
                        refresh_variable = 1;
                        break;
                    }
                    selected_icon = -1;
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    for (int i = 0; i < 5; i++) {
                        if (cityFinlandIconSprites[i].getGlobalBounds().contains(mousePos)) {
                            selected_city = i;
                            refresh_variable = 1;
                        }
                        if (cityKoreaIconSprites[i].getGlobalBounds().contains(mousePos)) {
                            selected_city = i + 5;
                            refresh_variable = 1;
                        }
                        if (globalSettings.getChosenCountry() == "Finland") {
                            if (selected_city >= 0 && selected_city < 5) {
                                if (grainMenuIconSprite.getGlobalBounds().contains(mousePos)) {
                                    if (PlayerCountry.getMetalStockpile() > 50) {
                                        PlayerCountry.cities[selected_city].setFarms(PlayerCountry.cities[selected_city].getFarms() + 1);
                                        PlayerCountry.setMetalStockpile(PlayerCountry.getMetalStockpile() - 50);
                                        cityUpgradedTimer[selected_city] = 1;
                                        PlayerCountry.cities[selected_city].setIsUpgraded(true);
                                    }
                                    else {

                                    }
                                }
                                if (metalMenuIconSprite.getGlobalBounds().contains(mousePos)) {
                                    if (PlayerCountry.getMetalStockpile() > 50) {
                                        PlayerCountry.cities[selected_city].setMines(PlayerCountry.cities[selected_city].getMines() + 1);
                                        PlayerCountry.setMetalStockpile(PlayerCountry.getMetalStockpile() - 50);
                                        cityUpgradedTimer[selected_city] = 1;
                                        PlayerCountry.cities[selected_city].setIsUpgraded(true);
                                    }
                                    else {

                                    }
                                }
                                if (uraniumMenuIconSprite.getGlobalBounds().contains(mousePos)) {
                                    if (PlayerCountry.getMetalStockpile() > 50) {
                                        PlayerCountry.cities[selected_city].setReactors(PlayerCountry.cities[selected_city].getReactors() + 1);
                                        PlayerCountry.setMetalStockpile(PlayerCountry.getMetalStockpile() - 50);
                                        cityUpgradedTimer[selected_city] = 1;
                                        PlayerCountry.cities[selected_city].setIsUpgraded(true);
                                    }
                                    else {

                                    }
                                }

                            }

                            if (selected_city >= 5 && selected_city < 10) {
                                if (grainMenuIconSprite.getGlobalBounds().contains(mousePos)) {
                                    if (PlayerCountry.getUraniumStockpile() >= 100) {
                                        PlayerCountry.setNukes(PlayerCountry.getNukes() + 1);
                                        PlayerCountry.setUraniumStockpile(PlayerCountry.getUraniumStockpile() - 100);
                                    }
                                    else {

                                    }
                                }
                                if (metalMenuIconSprite.getGlobalBounds().contains(mousePos)) {
                                    if (PlayerCountry.getNukes() > 0) {
                                        PlayerCountry.setNukes(PlayerCountry.getNukes() - 1);
                                        EnemyCountry.cities[selected_city - 5].setIsDestroyed(1);
                                        cityBombedTimer[selected_city] = 1;
                                    }
                                    else {

                                    }
                                }
                                if (uraniumMenuIconSprite.getGlobalBounds().contains(mousePos)) {
                                    if (PlayerCountry.getUraniumStockpile() >= 50) {
                                        EnemyCountry.cities[selected_city - 5].setFarms(EnemyCountry.cities[selected_city - 5].getFarms() - 1);
                                        EnemyCountry.cities[selected_city - 5].setMines(EnemyCountry.cities[selected_city - 5].getMines() - 1);
                                        EnemyCountry.cities[selected_city - 5].setReactors(EnemyCountry.cities[selected_city - 5].getReactors() - 1);
                                        PlayerCountry.setUraniumStockpile(PlayerCountry.getUraniumStockpile() - 50);
                                    }
                                    else {

                                    }
                                }
                            }
                        }
                        else {
                            if (selected_city >= 0 && selected_city < 5) {
                                if (grainMenuIconSprite.getGlobalBounds().contains(mousePos)) {
                                    if (PlayerCountry.getUraniumStockpile() >= 100) {
                                        PlayerCountry.setNukes(PlayerCountry.getNukes() + 1);
                                        PlayerCountry.setUraniumStockpile(PlayerCountry.getUraniumStockpile() - 100);
                                    }
                                    else {

                                    }
                                }
                                if (metalMenuIconSprite.getGlobalBounds().contains(mousePos)) {
                                    if (PlayerCountry.getNukes() > 0) {
                                        PlayerCountry.setNukes(PlayerCountry.getNukes() - 1);
                                        EnemyCountry.cities[selected_city].setIsDestroyed(1);
                                        cityBombedTimer[selected_city] = 1;
                                    }
                                    else {

                                    }
                                }
                                if (uraniumMenuIconSprite.getGlobalBounds().contains(mousePos)) {
                                    if (PlayerCountry.getUraniumStockpile() >= 50) {
                                        EnemyCountry.cities[selected_city].setFarms(EnemyCountry.cities[selected_city].getFarms() - 1);
                                        EnemyCountry.cities[selected_city].setMines(EnemyCountry.cities[selected_city].getMines() - 1);
                                        EnemyCountry.cities[selected_city].setReactors(EnemyCountry.cities[selected_city].getReactors() - 1);
                                        PlayerCountry.setUraniumStockpile(PlayerCountry.getUraniumStockpile() - 50);
                                    }
                                    else {

                                    }
                                }
                            }
                            if (selected_city >= 5 && selected_city < 10) {
                                if (grainMenuIconSprite.getGlobalBounds().contains(mousePos)) {
                                    if (PlayerCountry.getMetalStockpile() > 50) {
                                        PlayerCountry.cities[selected_city - 5].setFarms(PlayerCountry.cities[selected_city - 5].getFarms() + 1);
                                        PlayerCountry.setMetalStockpile(PlayerCountry.getMetalStockpile() - 50);
                                        cityUpgradedTimer[selected_city] = 1;
                                        PlayerCountry.cities[selected_city - 5].setIsUpgraded(true);
                                    }
                                    else {

                                    }
                                }
                                if (metalMenuIconSprite.getGlobalBounds().contains(mousePos)) {
                                    if (PlayerCountry.getMetalStockpile() > 50) {
                                        PlayerCountry.cities[selected_city - 5].setMines(PlayerCountry.cities[selected_city - 5].getMines() + 1);
                                        PlayerCountry.setMetalStockpile(PlayerCountry.getMetalStockpile() - 50);
                                        cityUpgradedTimer[selected_city] = 1;
                                        PlayerCountry.cities[selected_city - 5].setIsUpgraded(true);
                                    }
                                    else {

                                    }
                                }
                                if (uraniumMenuIconSprite.getGlobalBounds().contains(mousePos)) {
                                    if (PlayerCountry.getMetalStockpile() > 50) {
                                        PlayerCountry.cities[selected_city - 5].setReactors(PlayerCountry.cities[selected_city - 5].getReactors() + 1);
                                        PlayerCountry.setMetalStockpile(PlayerCountry.getMetalStockpile() - 50);
                                        cityUpgradedTimer[selected_city] = 1;
                                        PlayerCountry.cities[selected_city - 5].setIsUpgraded(true);
                                    }
                                    else {

                                    }
                                }

                            }
                        }
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == globalSettings.getKeyEscape()) {
                    if (showGameMenu(window)) {
                        EnemyCountry.setFoodStockpile(-5);
                        return;
                    }
                }
                else if (event.key.code == globalSettings.getKeyTab()) {
                    selected_tab = (selected_tab + 1) % 2;
                }
                else if (event.key.code == globalSettings.getKeyRight()) {
                    if (selected_tab == 0) {
                        selected_city = (selected_city + 1) % 10;
                        refresh_variable = 1;
                    }
                    else {
                        if (((selected_icon + 1) > 12) || ((selected_icon + 1) < 10)) {
                            selected_icon = 10;
                        }
                        else {
                            selected_icon++;
                        }
                        refresh_variable = 1;
                    }

                }
                else if (event.key.code == globalSettings.getKeyLeft()) {
                    if (selected_tab == 0) {
                        selected_city = (selected_city - 1 + 10) % 10;
                        refresh_variable = 1;
                    }
                    else {
                        if (((selected_icon - 1) < 10) || ((selected_icon - 1) > 12)) {
                            selected_icon = 12;
                        }
                        else {
                            selected_icon--;
                        }
                        refresh_variable = 1;
                    }
                }
                else if (event.key.code == globalSettings.getKeyConfirm()) {
                    if (globalSettings.getChosenCountry() == "Finland") {
                        if (selected_city >= 0 && selected_city < 5) {
                            if (selected_icon == 10) {
                                if (PlayerCountry.getMetalStockpile() > 50) {
                                    PlayerCountry.cities[selected_city].setFarms(PlayerCountry.cities[selected_city].getFarms() + 1);
                                    PlayerCountry.setMetalStockpile(PlayerCountry.getMetalStockpile() - 50);
                                    cityUpgradedTimer[selected_city] = 1;
                                    PlayerCountry.cities[selected_city].setIsUpgraded(true);
                                }
                                else {

                                }
                            }
                            if (selected_icon == 11) {
                                if (PlayerCountry.getMetalStockpile() > 50) {
                                    PlayerCountry.cities[selected_city].setMines(PlayerCountry.cities[selected_city].getMines() + 1);
                                    PlayerCountry.setMetalStockpile(PlayerCountry.getMetalStockpile() - 50);
                                    cityUpgradedTimer[selected_city] = 1;
                                    PlayerCountry.cities[selected_city].setIsUpgraded(true);
                                }
                                else {

                                }
                            }
                            if (selected_icon == 12) {
                                if (PlayerCountry.getMetalStockpile() > 50) {
                                    PlayerCountry.cities[selected_city].setReactors(PlayerCountry.cities[selected_city].getReactors() + 1);
                                    PlayerCountry.setMetalStockpile(PlayerCountry.getMetalStockpile() - 50);
                                    cityUpgradedTimer[selected_city] = 1;
                                    PlayerCountry.cities[selected_city].setIsUpgraded(true);
                                }
                                else {

                                }
                            }

                        }

                        if (selected_city >= 5 && selected_city < 10) {
                            if (selected_icon == 10) {
                                if (PlayerCountry.getUraniumStockpile() >= 100) {
                                    PlayerCountry.setNukes(PlayerCountry.getNukes() + 1);
                                    PlayerCountry.setUraniumStockpile(PlayerCountry.getUraniumStockpile() - 100);
                                }
                                else {

                                }
                            }
                            if (selected_icon == 11) {
                                if (PlayerCountry.getNukes() > 0) {
                                    PlayerCountry.setNukes(PlayerCountry.getNukes() - 1);
                                    EnemyCountry.cities[selected_city - 5].setIsDestroyed(1);
                                    cityBombedTimer[selected_city] = 1;
                                }
                                else {

                                }
                            }
                            if (selected_icon == 12) {
                                if (PlayerCountry.getUraniumStockpile() >= 50) {
                                    EnemyCountry.cities[selected_city - 5].setFarms(EnemyCountry.cities[selected_city - 5].getFarms() - 1);
                                    EnemyCountry.cities[selected_city - 5].setMines(EnemyCountry.cities[selected_city - 5].getMines() - 1);
                                    EnemyCountry.cities[selected_city - 5].setReactors(EnemyCountry.cities[selected_city - 5].getReactors() - 1);
                                    PlayerCountry.setUraniumStockpile(PlayerCountry.getUraniumStockpile() - 50);
                                }
                                else {

                                }
                            }
                        }
                    }
                    else {
                        if (selected_city >= 0 && selected_city < 5) {
                            if (selected_icon == 10) {
                                if (PlayerCountry.getUraniumStockpile() >= 100) {
                                    PlayerCountry.setNukes(PlayerCountry.getNukes() + 1);
                                    PlayerCountry.setUraniumStockpile(PlayerCountry.getUraniumStockpile() - 100);
                                }
                                else {

                                }
                            }
                            if (selected_icon == 11) {
                                if (PlayerCountry.getNukes() > 0) {
                                    PlayerCountry.setNukes(PlayerCountry.getNukes() - 1);
                                    EnemyCountry.cities[selected_city].setIsDestroyed(1);
                                    cityBombedTimer[selected_city] = 1;
                                }
                                else {

                                }
                            }
                            if (selected_icon == 12) {
                                if (PlayerCountry.getUraniumStockpile() >= 50) {
                                    EnemyCountry.cities[selected_city].setFarms(EnemyCountry.cities[selected_city].getFarms() - 1);
                                    EnemyCountry.cities[selected_city].setMines(EnemyCountry.cities[selected_city].getMines() - 1);
                                    EnemyCountry.cities[selected_city].setReactors(EnemyCountry.cities[selected_city].getReactors() - 1);
                                    PlayerCountry.setUraniumStockpile(PlayerCountry.getUraniumStockpile() - 50);
                                }
                                else {

                                }
                            }
                        }
                        if (selected_city >= 5 && selected_city < 10) {
                            if (selected_icon == 10) {
                                if (PlayerCountry.getMetalStockpile() > 50) {
                                    PlayerCountry.cities[selected_city - 5].setFarms(PlayerCountry.cities[selected_city - 5].getFarms() + 1);
                                    PlayerCountry.setMetalStockpile(PlayerCountry.getMetalStockpile() - 50);
                                    cityUpgradedTimer[selected_city] = 1;
                                    PlayerCountry.cities[selected_city - 5].setIsUpgraded(true);
                                }
                                else {

                                }
                            }
                            if (selected_icon == 11) {
                                if (PlayerCountry.getMetalStockpile() > 50) {
                                    PlayerCountry.cities[selected_city - 5].setMines(PlayerCountry.cities[selected_city - 5].getMines() + 1);
                                    PlayerCountry.setMetalStockpile(PlayerCountry.getMetalStockpile() - 50);
                                    cityUpgradedTimer[selected_city] = 1;
                                    PlayerCountry.cities[selected_city - 5].setIsUpgraded(true);
                                }
                                else {

                                }
                            }
                            if (selected_icon == 12) {
                                if (PlayerCountry.getMetalStockpile() > 50) {
                                    PlayerCountry.cities[selected_city - 5].setReactors(PlayerCountry.cities[selected_city - 5].getReactors() + 1);
                                    PlayerCountry.setMetalStockpile(PlayerCountry.getMetalStockpile() - 50);
                                    cityUpgradedTimer[selected_city] = 1;
                                    PlayerCountry.cities[selected_city - 5].setIsUpgraded(true);
                                }
                                else {

                                }
                            }

                        }
                    }
                }
            }
        }

        if (refresh_variable) {

            for (int i = 0; i < 5; ++i) {
                cityFinlandIconSprites[i].setColor(originalColor);
                cityKoreaIconSprites[i].setColor(originalColor);
            }

            topBarText0.setString(std::to_string(PlayerCountry.getFoodStockpile()) + "/100+(" + std::to_string(PlayerCountry.getFoodIncome()) + ")");
            topBarText1.setString(std::to_string(PlayerCountry.getMetalStockpile()) + "/100+(" + std::to_string(PlayerCountry.getMetalIncome()) + ")");
            topBarText2.setString(std::to_string(PlayerCountry.getUraniumStockpile()) + "/100+(" + std::to_string(PlayerCountry.getUraniumIncome()) + ")");
            topBarText3.setString("" + std::to_string(PlayerCountry.getNukes()));
            topBarText4.setString("" + std::to_string(PlayerCountry.getNumberOfCities()));
            logBarText0.setString("City: " + std::to_string(selected_city));
            logBarText1.setString("Icon: " + std::to_string(selected_icon));
            logBarText2.setString("Tab: " + std::to_string(selected_tab));
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
            window.draw(nukeMenuIconSprite);
            window.draw(topBarText3);
            window.draw(citiesSprite);
            window.draw(topBarText4);

            window.draw(logBarText0);
            window.draw(logBarText1);
            window.draw(logBarText2);

            window.draw(logInfoText0);
            window.draw(logCostText0);
            window.draw(logCostText1);
            window.draw(logCostText2);

            window.draw(bottomText);

            if (cityAnimationClock.getElapsedTime().asSeconds() >= frameDuration) {
                currentFrameDestroyedCity = (currentFrameDestroyedCity + 1) % 3;
                for (int i = 0; i < 5; i++) {
                    cityFinlandDestroyedIconSprites[i].setTextureRect(destroyedFrames[currentFrameDestroyedCity]);
                    cityKoreaDestroyedIconSprites[i].setTextureRect(destroyedFrames[currentFrameDestroyedCity]);
                }
                currentFrameUpgradedCity = (currentFrameUpgradedCity + 1) % 4;
                for (int i = 0; i < 5; i++) {
                    cityFinlandUpgradedIconSprites[i].setTextureRect(upgradingFrames[currentFrameUpgradedCity]);
                    cityKoreaUpgradedIconSprites[i].setTextureRect(upgradingFrames[currentFrameUpgradedCity]);
                }
                currentFrameBombedCity = (currentFrameDestroyedCity + 1) % 5;
                for (int i = 0; i < 5; i++) {
                    cityFinlandBombedIconSprites[i].setTextureRect(explosionFrames[currentFrameBombedCity]);
                    cityKoreaBombedIconSprites[i].setTextureRect(explosionFrames[currentFrameBombedCity]);
                }
                currentSoldierFrame = (currentSoldierFrame + 1) % 6;
                for (int i = 0; i < 3; i++) {
                    soldierFSprites[i].setTextureRect(soldierFFrames[currentSoldierFrame]);
                    soldierKSprites[i].setTextureRect(soldierKFrames[currentSoldierFrame]);
                }
                currentFrameHourglass = (currentFrameHourglass + 1) % 6;
                hourglassSprite.setTextureRect(hourglassFrames[currentFrameHourglass]);
                cityAnimationClock.restart();
            }

            window.draw(hourglassSprite);

            for (int i = 0; i < 3; i++) {
                window.draw(soldierFSprites[i]);
                window.draw(soldierKSprites[i]);
            }

            if (selected_city >= 0 && selected_city < 5) {
                outlineShape.setPosition(cityFinlandIconSprites[selected_city].getPosition());
                outlineShape.setOutlineColor(outlineColor);
                outlineShape.setOutlineThickness(outlineThickness);
                window.draw(outlineShape);
                logInfoText0.setString("Player City");
                logCostText0.setString("");
                logCostText1.setString("");
                logCostText2.setString("");
                if (globalSettings.getChosenCountry() == "Finland") {
                    if (selected_icon == 10) {
                        logInfoText0.setString("Build Farm");
                        logCostText0.setString("0");
                        logCostText1.setString("50");
                        logCostText2.setString("0");
                    }
                    if (selected_icon == 11) {
                        logInfoText0.setString("Build Mine");
                        logCostText0.setString("0");
                        logCostText1.setString("50");
                        logCostText2.setString("0");
                    }
                    if (selected_icon == 12) {
                        logInfoText0.setString("Build Reactor");
                        logCostText0.setString("0");
                        logCostText1.setString("50");
                        logCostText2.setString("0");
                    }
                }
                else {
                    if (selected_icon == 10) {
                        logInfoText0.setString("Build Nuke");
                        logCostText0.setString("0");
                        logCostText1.setString("0");
                        logCostText2.setString("100");
                    }
                    if (selected_icon == 11) {
                        logInfoText0.setString("Nuke City");
                        logCostText0.setString("0");
                        logCostText1.setString("0");
                        logCostText2.setString("0");
                    }
                    if (selected_icon == 12) {
                        logInfoText0.setString("Bomb City(-1 F/C/R)");
                        logCostText0.setString("0");
                        logCostText1.setString("0");
                        logCostText2.setString("50");
                    }
                }
            }

            else if (selected_city >= 5 && selected_city < 10) {
                outlineShape.setPosition(cityKoreaIconSprites[selected_city - 5].getPosition());
                outlineShape.setOutlineColor(outlineColor);
                outlineShape.setOutlineThickness(outlineThickness);
                window.draw(outlineShape);
                logInfoText0.setString("Enemy City");
                logCostText0.setString("");
                logCostText1.setString("");
                logCostText2.setString("");
                if (globalSettings.getChosenCountry() == "Finland") {
                    if (selected_icon == 10) {
                        logInfoText0.setString("Build Nuke");
                        logCostText0.setString("0");
                        logCostText1.setString("0");
                        logCostText2.setString("100");
                    }
                    if (selected_icon == 11) {
                        logInfoText0.setString("Nuke City");
                        logCostText0.setString("0");
                        logCostText1.setString("0");
                        logCostText2.setString("0");
                    }
                    if (selected_icon == 12) {
                        logInfoText0.setString("Bomb City(-1 F/C/R)");
                        logCostText0.setString("0");
                        logCostText1.setString("0");
                        logCostText2.setString("50");
                    }
                }
                else {
                    if (selected_icon == 10) {
                        logInfoText0.setString("Build Farm");
                        logCostText0.setString("0");
                        logCostText1.setString("50");
                        logCostText2.setString("0");
                    }
                    if (selected_icon == 11) {
                        logInfoText0.setString("Build Mine");
                        logCostText0.setString("0");
                        logCostText1.setString("50");
                        logCostText2.setString("0");
                    }
                    if (selected_icon == 12) {
                        logInfoText0.setString("Build Reactor");
                        logCostText0.setString("0");
                        logCostText1.setString("50");
                        logCostText2.setString("0");
                    }
                }
            }

            if (selected_icon >= 0 && selected_icon < 5) {
                outlineCityShape.setPosition(cityFinlandIconSprites[selected_icon].getPosition());
                outlineCityShape.setOutlineColor(outlineIconColor);
                outlineCityShape.setOutlineThickness(outlineThickness);
                window.draw(outlineCityShape);

            }
            else if (selected_icon >= 5 && selected_icon < 10) {
                outlineCityShape.setPosition(cityKoreaIconSprites[selected_icon - 5].getPosition());
                outlineCityShape.setOutlineColor(outlineIconColor);
                outlineCityShape.setOutlineThickness(outlineThickness);
                window.draw(outlineCityShape);
            }
            else if (selected_icon >= 10 && selected_icon < 13) {
                outlineIconShape.setOutlineColor(outlineIconColor);
                outlineIconShape.setOutlineThickness(outlineThickness);
                switch (selected_icon) {
                case 10:
                    outlineIconShape.setPosition(grainMenuIconSprite.getPosition());
                    window.draw(grainLogIconSprite);
                    window.draw(metalLogIconSprite);
                    window.draw(uraniumLogIconSprite);
                    break;
                case 11:
                    outlineIconShape.setPosition(metalMenuIconSprite.getPosition());

                    window.draw(grainLogIconSprite);
                    window.draw(metalLogIconSprite);
                    window.draw(uraniumLogIconSprite);
                    break;
                case 12:
                    outlineIconShape.setPosition(uraniumMenuIconSprite.getPosition());

                    window.draw(grainLogIconSprite);
                    window.draw(metalLogIconSprite);
                    window.draw(uraniumLogIconSprite);
                    window.draw(logInfoText0);
                    window.draw(logCostText0);
                    window.draw(logCostText1);
                    window.draw(logCostText2);
                    break;
                default:
                    break;
                }

                window.draw(outlineIconShape);
            }


            if (globalSettings.getChosenCountry() == "Finland") {
                if (selected_city >= 0 && selected_city < 5) {
                    window.draw(grainMenuIconSprite);
                    window.draw(metalMenuIconSprite);
                    window.draw(uraniumMenuIconSprite);
                }
                if (selected_city >= 5 && selected_city < 10) {
                    window.draw(nukeBuildIconflagSprite);
                    window.draw(nukeIconSprite);
                    window.draw(cityBombedIconSprite);
                }
            }
            else {
                if (selected_city >= 0 && selected_city < 5) {
                    window.draw(nukeBuildIconflagSprite);
                    window.draw(nukeIconSprite);
                    window.draw(cityBombedIconSprite);
                }
                if (selected_city >= 5 && selected_city < 10) {
                    window.draw(grainMenuIconSprite);
                    window.draw(metalMenuIconSprite);
                    window.draw(uraniumMenuIconSprite);
                }
            }

            for (int u = 0; u < 5; u++) {
                if (globalSettings.getChosenCountry() == "Finland") {
                    if (PlayerCountry.cities[u].getIsUpgraded()) {
                        window.draw(cityFinlandUpgradedIconSprites[u]);
                    }
                    else if (PlayerCountry.cities[u].getIsDestroyed()) {
                        window.draw(cityFinlandDestroyedIconSprites[u]);
                    }
                    else {
                        window.draw(cityFinlandIconSprites[u]);
                    }
                    if (cityBombedTimer[u] > 0) {
                        window.draw(cityFinlandBombedIconSprites[u]);
                        if (cityAnimationClock.getElapsedTime().asSeconds() >= frameDuration) {
                            cityBombedTimer[u]--;
                        }
                    }

                    if (EnemyCountry.cities[u].getIsUpgraded()) {
                        window.draw(cityKoreaUpgradedIconSprites[u]);
                    }
                    else if (EnemyCountry.cities[u].getIsDestroyed()) {
                        window.draw(cityKoreaDestroyedIconSprites[u]);
                    }
                    else {
                        window.draw(cityKoreaIconSprites[u]);
                    }
                    if (cityBombedTimer[u + 5] > 0) {
                        window.draw(cityKoreaBombedIconSprites[u]);
                        if (cityAnimationClock.getElapsedTime().asSeconds() >= frameDuration) {
                            cityBombedTimer[u + 5]--;
                        }
                    }
                }
                else {
                    if (PlayerCountry.cities[u].getIsUpgraded()) {
                        window.draw(cityKoreaUpgradedIconSprites[u]);
                    }
                    else if (PlayerCountry.cities[u].getIsDestroyed()) {
                        window.draw(cityKoreaDestroyedIconSprites[u]);
                    }
                    else {
                        window.draw(cityKoreaIconSprites[u]);
                    }
                    if (cityBombedTimer[u] > 0) {
                        window.draw(cityKoreaBombedIconSprites[u]);
                        if (cityAnimationClock.getElapsedTime().asSeconds() >= frameDuration) {
                            cityBombedTimer[u]--;
                        }
                    }

                    if (EnemyCountry.cities[u].getIsUpgraded()) {
                        window.draw(cityFinlandUpgradedIconSprites[u]);
                    }
                    else if (EnemyCountry.cities[u].getIsDestroyed()) {
                        window.draw(cityFinlandDestroyedIconSprites[u]);
                    }
                    else {
                        window.draw(cityFinlandIconSprites[u]);
                    }
                    if (cityBombedTimer[u] > 0) {
                        window.draw(cityFinlandBombedIconSprites[u]);
                        if (cityAnimationClock.getElapsedTime().asSeconds() >= frameDuration) {
                            cityBombedTimer[u]--;
                        }
                    }
                }
            }
            if (globalSettings.getChosenCountry() == "Finland") {
                for (int u = 0; u < 5; u++) {
                    if (PlayerCountry.cities[u].getIsUpgraded()) {
                        if (cityUpgradedTimer[u] > 0) {
                            if (cityAnimationClock.getElapsedTime().asSeconds() >= frameDuration) {
                                cityUpgradedTimer[u] = cityUpgradedTimer[u] - 1;
                            }
                        }
                        else {
                            PlayerCountry.cities[u].setIsUpgraded(false);
                        }
                    }
                    if (EnemyCountry.cities[u].getIsUpgraded()) {
                        if (cityUpgradedTimer[u + 5] > 0) {
                            if (cityAnimationClock.getElapsedTime().asSeconds() >= frameDuration) {
                                cityUpgradedTimer[u + 5] = cityUpgradedTimer[u + 5] - 1;
                            }
                        }
                        else {
                            EnemyCountry.cities[u].setIsUpgraded(false);
                        }
                    }
                }
            }
            else {
                for (int u = 0; u < 5; u++) {
                    if (PlayerCountry.cities[u].getIsUpgraded()) {
                        if (cityUpgradedTimer[u + 5] > 0) {
                            if (cityAnimationClock.getElapsedTime().asSeconds() >= frameDuration) {
                                cityUpgradedTimer[u + 5] = cityUpgradedTimer[u + 5] - 1;
                            }
                        }
                        else {
                            PlayerCountry.cities[u].setIsUpgraded(false);
                        }
                    }
                    if (EnemyCountry.cities[u].getIsUpgraded()) {
                        if (cityUpgradedTimer[u] > 0) {
                            if (cityAnimationClock.getElapsedTime().asSeconds() >= frameDuration) {
                                cityUpgradedTimer[u] = cityUpgradedTimer[u] - 1;
                            }
                        }
                        else {
                            EnemyCountry.cities[u].setIsUpgraded(false);
                        }
                    }
                }
            }

            for (int i = 0; i < 5; i++) {
                window.draw(cityFinlandNames[i]);
                window.draw(cityKoreaNames[i]);
            }

            window.display();

            if (PlayerCountry.getNumberOfCities() <= 0 || PlayerCountry.getFoodStockpile() <= 0) {
                if (showEndCredits(window, 1)) {
                    return;
                }
            }
            if (EnemyCountry.getNumberOfCities() <= 0 || EnemyCountry.getFoodStockpile() <= 0) {
                if (showEndCredits(window, 2)) {
                    return;
                }
            }
        }
        refresh_variable = 0;
    }
}

//Function

bool showGameMenu(sf::RenderWindow& window) {
    extern Settings globalSettings;
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


    gameMenuText1.setFillColor(colorGray);
    gameMenuText2.setFillColor(colorGray);

    std::cout << "GameMenuFunction\n";

    int selected_option = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            // Handle mouse movement for menu navigation
            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (gameMenuText0.getGlobalBounds().contains(mousePos)) {
                    selected_option = 0;
                }
                else if (gameMenuText1.getGlobalBounds().contains(mousePos)) {
                    selected_option = 1;
                }
                else if (gameMenuText2.getGlobalBounds().contains(mousePos)) {
                    selected_option = 2;
                }
                else if (gameMenuText3.getGlobalBounds().contains(mousePos)) {
                    selected_option = 3;
                }
                else if (gameMenuText4.getGlobalBounds().contains(mousePos)) {
                    selected_option = 4;
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
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == globalSettings.getKeyDown()) {
                    selected_option = (selected_option - 1 + 5) % 5;
                }
                else if (event.key.code == globalSettings.getKeyDown()) {
                    selected_option = (selected_option + 1) % 5;
                }
                else if (event.key.code == globalSettings.getKeyConfirm()) {
                    std::cout << "Mouse Resume\n";
                    window.clear();
                    return 0;
                }
                else if (event.key.code == globalSettings.getKeyEscape()) {
                    std::cout << "Key Main Menu\n";
                    return 1;
                    break;
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
    return 0;
}

