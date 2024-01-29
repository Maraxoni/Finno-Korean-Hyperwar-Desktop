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

    sf::Color colorGray(128, 128, 128);

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
    float scaleX = static_cast<float>(800) / originalSize.x;
    float scaleY = static_cast<float>(600) / originalSize.y;
    // Set the scale of the sprite
    creditsBackgroundSprite.setScale(scaleX, scaleY);

    sf::RectangleShape bottomTooltipRectangle(sf::Vector2f(798, 25)); // Set the size of the rectangle
    bottomTooltipRectangle.setPosition(2, 575);
    bottomTooltipRectangle.setFillColor(colorGray);
    bottomTooltipRectangle.setOutlineThickness(2);
    bottomTooltipRectangle.setOutlineColor(sf::Color::Black);

    //Main
    sf::Text settingsTitleText("Settings", font_arial, 50);
    settingsTitleText.setOutlineThickness(2);
    settingsTitleText.setPosition((800 - settingsTitleText.getGlobalBounds().width) / 2, 0);
    settingsTitleText.setFillColor(sf::Color::Red);

    sf::Text settingsReturnText("Return", font_arial, 20);
    settingsReturnText.setOutlineThickness(2);
    settingsReturnText.setPosition((800 - settingsReturnText.getGlobalBounds().width) / 2, 500);
    settingsReturnText.setFillColor(sf::Color::White);
    //Choices
    sf::Text settingsChoiceText0("Game", font_arial, 40);
    settingsChoiceText0.setOutlineThickness(2);
    settingsChoiceText0.setPosition((800 - 400 - settingsChoiceText0.getGlobalBounds().width) / 2, 100);
    settingsChoiceText0.setFillColor(sf::Color::White);

    sf::Text settingsChoiceText1("Key Binds", font_arial, 40);
    settingsChoiceText1.setOutlineThickness(2);
    settingsChoiceText1.setPosition((800 - settingsChoiceText1.getGlobalBounds().width) / 2, 100);
    settingsChoiceText1.setFillColor(sf::Color::White);

    sf::Text settingsChoiceText2("Instruction", font_arial, 40);
    settingsChoiceText2.setOutlineThickness(2);
    settingsChoiceText2.setPosition((800 + 400 - settingsChoiceText2.getGlobalBounds().width) / 2, 100);
    settingsChoiceText2.setFillColor(sf::Color::White);

    //Game Options
    sf::Text settingsGameText0("Selected Country: ", font_arial, 20);
    settingsGameText0.setOutlineThickness(2);
    settingsGameText0.setPosition((800 - settingsGameText0.getGlobalBounds().width) / 2, 170);
    sf::Text settingsGameText1("Difficulty: ", font_arial, 20);
    settingsGameText1.setOutlineThickness(2);
    settingsGameText1.setPosition((800 - settingsGameText1.getGlobalBounds().width) / 2, 220);
    sf::Text settingsGameText2("Speed: ", font_arial, 20);
    settingsGameText2.setOutlineThickness(2);
    settingsGameText2.setPosition((800 - settingsGameText2.getGlobalBounds().width) / 2, 270);
    //Key Binds
    sf::Text settingsKeyText0("Up: ", font_arial, 20);
    settingsKeyText0.setOutlineThickness(2);
    settingsKeyText0.setPosition((800 - settingsKeyText0.getGlobalBounds().width) / 2, 150);
    sf::Text settingsKeyText1("Down: ", font_arial, 20);
    settingsKeyText1.setOutlineThickness(2);
    settingsKeyText1.setPosition((800 - settingsKeyText1.getGlobalBounds().width) / 2, 180);
    sf::Text settingsKeyText2("Right: ", font_arial, 20);
    settingsKeyText2.setOutlineThickness(2);
    settingsKeyText2.setPosition((800 - settingsKeyText2.getGlobalBounds().width) / 2, 210);
    sf::Text settingsKeyText3("Left: ", font_arial, 20);
    settingsKeyText3.setOutlineThickness(2);
    settingsKeyText3.setPosition((800 - settingsKeyText3.getGlobalBounds().width) / 2, 240);
    sf::Text settingsKeyText4("Confirm: ", font_arial, 20);
    settingsKeyText4.setOutlineThickness(2);
    settingsKeyText4.setPosition((800 - settingsKeyText4.getGlobalBounds().width) / 2, 270);
    sf::Text settingsKeyText5("Tab: ", font_arial, 20);
    settingsKeyText5.setOutlineThickness(2);
    settingsKeyText5.setPosition((800 - settingsKeyText5.getGlobalBounds().width) / 2, 300);
    sf::Text settingsKeyText6("Escape: ", font_arial, 20);
    settingsKeyText6.setOutlineThickness(2);
    settingsKeyText6.setPosition((800 - settingsKeyText6.getGlobalBounds().width) / 2, 330);
    //Instruction
    sf::Text settingsInstruction("Celem gry jest zniszczenie miast przeciwnika,\n Buduj budynki i sie rozwijaj,\nGra konczy sie gdy ktorakolwiek ze stron, straci wszystkie miasta,\n badz zywnosc spadnie do zera.", font_arial, 20);

    settingsInstruction.setOutlineThickness(2);
    settingsInstruction.setPosition((800 - settingsInstruction.getGlobalBounds().width) / 2, 150);

    sf::Text keyOption("Nacisnij dowolny przycisk", font_arial, 20);
    keyOption.setFillColor(sf::Color::Red);
    keyOption.setOutlineThickness(2);

    sf::Text highlightedChoiceOption("", font_arial, 40);
    highlightedChoiceOption.setFillColor(sf::Color::Red);
    sf::Text highlightedOption("", font_arial, 20);
    highlightedOption.setFillColor(sf::Color::Red);

    std::cout << "SettingsFunction\n";

    sf::Keyboard::Key selected_key;
    int selected_menu = 0;
    int selected_option = -1;

    sf::Text bottomText("", font_arial, 15);
    bottomText.setPosition((800 - bottomText.getGlobalBounds().width) / 2, 575);
    bottomText.setOutlineThickness(1);

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

        settingsGameText0.setString("Selected Country: " + globalSettings.getChosenCountry());
        settingsGameText0.setPosition((800 - settingsGameText0.getGlobalBounds().width) / 2, 170);
        settingsGameText1.setString("Difficulty: " + std::to_string(globalSettings.getDifficulty()));
        settingsGameText1.setPosition((800 - settingsGameText1.getGlobalBounds().width) / 2, 220);
        settingsGameText2.setString("Speed: " + std::to_string(globalSettings.getSpeed()));
        settingsGameText2.setPosition((800 - settingsGameText2.getGlobalBounds().width) / 2, 270);

        settingsKeyText0.setString("Up Key: " + std::to_string(globalSettings.getKeyUp()));
        settingsKeyText0.setPosition((800 - settingsKeyText0.getGlobalBounds().width) / 2, 150);
        settingsKeyText1.setString("Down Key: " + std::to_string(globalSettings.getKeyDown()));
        settingsKeyText1.setPosition((800 - settingsKeyText1.getGlobalBounds().width) / 2, 180);
        settingsKeyText2.setString("Right Key: " + std::to_string(globalSettings.getKeyRight()));
        settingsKeyText2.setPosition((800 - settingsKeyText2.getGlobalBounds().width) / 2, 210);
        settingsKeyText3.setString("Left Key: " + std::to_string(globalSettings.getKeyLeft()));
        settingsKeyText3.setPosition((800 - settingsKeyText3.getGlobalBounds().width) / 2, 240);
        settingsKeyText4.setString("Confirm Key: " + std::to_string(globalSettings.getKeyConfirm()));
        settingsKeyText4.setPosition((800 - settingsKeyText4.getGlobalBounds().width) / 2, 270);
        settingsKeyText5.setString("Tab Key: " + std::to_string(globalSettings.getKeyTab()));
        settingsKeyText5.setPosition((800 - settingsKeyText5.getGlobalBounds().width) / 2, 300);
        settingsKeyText6.setString("Escape Key: " + std::to_string(globalSettings.getKeyEscape()));
        settingsKeyText6.setPosition((800 - settingsKeyText6.getGlobalBounds().width) / 2, 330);

        switch (selected_menu) {
        case 0:
            if (selected_option == 3) {
                selected_option = 7;
            }
            else if (selected_option == 4 || selected_option == 5 || selected_option == 6 || selected_option > 7) {
                selected_option = 0;
            }
            break;
        case 1:

            break;
        case 2:
            if (selected_option != 7) {
                selected_option = 7;
            }
            break;
        default:
            break;
        }
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                switch (selected_menu) {
                case 0:
                    if (settingsGameText0.getGlobalBounds().contains(mousePos)) {
                        selected_option = 0;
                    }
                    else if (settingsGameText1.getGlobalBounds().contains(mousePos)) {
                        selected_option = 1;
                    }
                    else if (settingsGameText2.getGlobalBounds().contains(mousePos)) {
                        selected_option = 2;
                    }
                    else if (settingsReturnText.getGlobalBounds().contains(mousePos)) {
                        selected_option = 7;
                    }
                    break;
                case 1:
                    if (settingsKeyText0.getGlobalBounds().contains(mousePos)) {
                        selected_option = 0;
                    }
                    else if (settingsKeyText1.getGlobalBounds().contains(mousePos)) {
                        selected_option = 1;
                    }
                    else if (settingsKeyText2.getGlobalBounds().contains(mousePos)) {
                        selected_option = 2;
                    }
                    else if (settingsKeyText3.getGlobalBounds().contains(mousePos)) {
                        selected_option = 3;
                    }
                    else if (settingsKeyText4.getGlobalBounds().contains(mousePos)) {
                        selected_option = 4;
                    }
                    else if (settingsKeyText5.getGlobalBounds().contains(mousePos)) {
                        selected_option = 5;
                    }
                    else if (settingsKeyText6.getGlobalBounds().contains(mousePos)) {
                        selected_option = 6;
                    }
                    else if (settingsReturnText.getGlobalBounds().contains(mousePos)) {
                        selected_option = 7;
                    }
                    break;
                case 2:
                    if (settingsReturnText.getGlobalBounds().contains(mousePos)) {
                        selected_option = 7;
                    }
                    break;
                default:
                    break;
                }
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == globalSettings.getKeyEscape()) {
                    return;
                }
                else if (event.key.code == globalSettings.getKeyConfirm()) {
                    switch (selected_menu) {
                    case 0:
                        if (selected_option == 0) {
                            if (globalSettings.getChosenCountry() == "Finland") {
                                globalSettings.setChosenCountry("Korea");
                            }
                            else {
                                globalSettings.setChosenCountry("Finland");
                            }
                            std::cout << "0.0\n";
                        }
                        else if (selected_option == 1) {
                            if ((globalSettings.getDifficulty() + 1) > 3) {
                                globalSettings.setDifficulty(1);
                            }
                            else {
                                globalSettings.setDifficulty(globalSettings.getDifficulty() + 1);
                            }
                            std::cout << "0.1\n";
                        }
                        else if (selected_option == 2) {
                            if ((globalSettings.getSpeed() + 1) > 5) {
                                globalSettings.setSpeed(1);
                            }
                            else {
                                globalSettings.setSpeed(globalSettings.getSpeed() + 1);
                            }
                            std::cout << "0.2\n";
                        }
                        else if (selected_option == 7) {
                            std::cout << "0.7\n";
                            return;
                        }
                        break;
                    case 1:
                        if (selected_option == 0) {
                            std::cout << "1.0\n";
                            keyOption.setPosition(settingsKeyText0.getPosition());
                            keyOption.move(150.0f, 0.0f);
                            window.draw(keyOption);
                            window.display();
                            while (window.waitEvent(event)) {
                                if (event.type == sf::Event::KeyPressed) {
                                    selected_key = event.key.code;
                                    globalSettings.setKeyUp(selected_key);
                                    std::cout << "Wybrany klawisz: " << selected_key << "\n";
                                    break;
                                }
                            }
                        }
                        else if (selected_option == 1) {
                            std::cout << "1.1\n";
                            keyOption.setPosition(settingsKeyText1.getPosition());
                            keyOption.move(150.0f, 0.0f);
                            window.draw(keyOption);
                            window.display();
                            while (window.waitEvent(event)) {
                                if (event.type == sf::Event::KeyPressed) {
                                    selected_key = event.key.code;
                                    globalSettings.setKeyDown(selected_key);
                                    std::cout << "Wybrany klawisz: " << selected_key << "\n";
                                    break;
                                }
                            }
                        }
                        else if (selected_option == 2) {
                            std::cout << "1.2\n";
                            keyOption.setPosition(settingsKeyText2.getPosition());
                            keyOption.move(150.0f, 0.0f);
                            window.draw(keyOption);
                            window.display();
                            while (window.waitEvent(event)) {
                                if (event.type == sf::Event::KeyPressed) {
                                    selected_key = event.key.code;
                                    globalSettings.setKeyRight(selected_key);
                                    std::cout << "Wybrany klawisz: " << selected_key << "\n";
                                    break;
                                }
                            }
                        }
                        else if (selected_option == 3) {
                            std::cout << "1.3\n";
                            keyOption.setPosition(settingsKeyText3.getPosition());
                            keyOption.move(150.0f, 0.0f);
                            window.draw(keyOption);
                            window.display();
                            while (window.waitEvent(event)) {
                                if (event.type == sf::Event::KeyPressed) {
                                    selected_key = event.key.code;
                                    globalSettings.setKeyLeft(selected_key);
                                    std::cout << "Wybrany klawisz: " << selected_key << "\n";
                                    break;
                                }
                            }
                        }
                        else if (selected_option == 4) {
                            std::cout << "1.4\n";
                            keyOption.setPosition(settingsKeyText4.getPosition());
                            keyOption.move(150.0f, 0.0f);
                            window.draw(keyOption);
                            window.display();
                            while (window.waitEvent(event)) {
                                if (event.type == sf::Event::KeyPressed) {
                                    selected_key = event.key.code;
                                    globalSettings.setKeyConfirm(selected_key);
                                    std::cout << "Wybrany klawisz: " << selected_key << "\n";
                                    break;
                                }
                            }
                        }
                        else if (selected_option == 5) {
                            std::cout << "1.5\n";
                            keyOption.setPosition(settingsKeyText5.getPosition());
                            keyOption.move(150.0f, 0.0f);
                            window.draw(keyOption);
                            window.display();
                            while (window.waitEvent(event)) {
                                if (event.type == sf::Event::KeyPressed) {
                                    selected_key = event.key.code;
                                    globalSettings.setKeyTab(selected_key);
                                    std::cout << "Wybrany klawisz: " << selected_key << "\n";
                                    break;
                                }
                            }
                        }
                        else if (selected_option == 6) {
                            std::cout << "1.6\n";
                            keyOption.setPosition(settingsKeyText6.getPosition());
                            keyOption.move(150.0f, 0.0f);
                            window.draw(keyOption);
                            window.display();
                            while (window.waitEvent(event)) {
                                if (event.type == sf::Event::KeyPressed) {
                                    selected_key = event.key.code;
                                    globalSettings.setKeyEscape(selected_key);
                                    std::cout << "Wybrany klawisz: " << selected_key << "\n";
                                    break;
                                }
                            }
                        }
                        else if (selected_option == 7) {
                            std::cout << "1.7\n";
                            return;
                        }
                        break;
                    case 2:
                        if (selected_option == 7) {
                            std::cout << "2.7\n";
                            return;
                        }
                        break;
                    default:
                        break;
                    }
                }
                else if (event.key.code == globalSettings.getKeyDown()) {
                    selected_option = (selected_option + 1) % 8;
                }
                else if (event.key.code == globalSettings.getKeyUp()) {
                    selected_option = (selected_option - 1 + 8) % 8;
                }
                else if (event.key.code == globalSettings.getKeyTab()) {
                    selected_menu = (selected_menu + 1) % 3;
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (settingsChoiceText0.getGlobalBounds().contains(mousePos)) {
                        selected_menu = 0;
                    }
                    else if (settingsChoiceText1.getGlobalBounds().contains(mousePos)) {
                        selected_menu = 1;
                    }
                    else if (settingsChoiceText2.getGlobalBounds().contains(mousePos)) {
                        selected_menu = 2;
                    }
                    else switch (selected_menu) {
                    case 0:
                        if (settingsGameText0.getGlobalBounds().contains(mousePos)) {
                            if (globalSettings.getChosenCountry() == "Finland") {
                                globalSettings.setChosenCountry("Korea");
                            }
                            else {
                                globalSettings.setChosenCountry("Finland");
                            }
                            std::cout << "0.0\n";
                        }
                        else if (settingsGameText1.getGlobalBounds().contains(mousePos)) {
                            if ((globalSettings.getDifficulty() + 1) > 3) {
                                globalSettings.setDifficulty(1);
                            }
                            else {
                                globalSettings.setDifficulty(globalSettings.getDifficulty() + 1);
                            }
                            std::cout << "0.1\n";
                        }
                        else if (settingsGameText2.getGlobalBounds().contains(mousePos)) {
                            if ((globalSettings.getSpeed() + 1) > 5) {
                                globalSettings.setSpeed(1);
                            }
                            else {
                                globalSettings.setSpeed(globalSettings.getSpeed() + 1);
                            }
                            std::cout << "0.2\n";
                        }
                        else if (settingsReturnText.getGlobalBounds().contains(mousePos)) {
                            std::cout << "0.7\n";
                            return;
                        }
                        break;
                    case 1:
                        if (settingsKeyText0.getGlobalBounds().contains(mousePos)) {
                            std::cout << "1.0\n";
                            keyOption.setPosition(settingsKeyText0.getPosition());
                            keyOption.move(150.0f, 0.0f);
                            window.draw(keyOption);
                            window.display();
                            while (window.waitEvent(event)) {
                                if (event.type == sf::Event::KeyPressed) {
                                    selected_key = event.key.code;
                                    globalSettings.setKeyUp(selected_key);
                                    std::cout << "Wybrany klawisz: " << selected_key << "\n";
                                    break;
                                }
                            }
                        }
                        else if (settingsKeyText1.getGlobalBounds().contains(mousePos)) {
                            std::cout << "1.1\n";
                            keyOption.setPosition(settingsKeyText1.getPosition());
                            keyOption.move(150.0f, 0.0f);
                            window.draw(keyOption);
                            window.display();
                            while (window.waitEvent(event)) {
                                if (event.type == sf::Event::KeyPressed) {
                                    selected_key = event.key.code;
                                    globalSettings.setKeyDown(selected_key);
                                    std::cout << "Wybrany klawisz: " << selected_key << "\n";
                                    break;
                                }
                            }
                        }
                        else if (settingsKeyText2.getGlobalBounds().contains(mousePos)) {
                            std::cout << "1.2\n";
                            keyOption.setPosition(settingsKeyText2.getPosition());
                            keyOption.move(150.0f, 0.0f);
                            window.draw(keyOption);
                            window.display();
                            while (window.waitEvent(event)) {
                                if (event.type == sf::Event::KeyPressed) {
                                    selected_key = event.key.code;
                                    globalSettings.setKeyRight(selected_key);
                                    std::cout << "Wybrany klawisz: " << selected_key << "\n";
                                    break;
                                }
                            }
                        }
                        else if (settingsKeyText3.getGlobalBounds().contains(mousePos)) {
                            std::cout << "1.3\n";
                            keyOption.setPosition(settingsKeyText3.getPosition());
                            keyOption.move(150.0f, 0.0f);
                            window.draw(keyOption);
                            window.display();
                            while (window.waitEvent(event)) {
                                if (event.type == sf::Event::KeyPressed) {
                                    selected_key = event.key.code;
                                    globalSettings.setKeyLeft(selected_key);
                                    std::cout << "Wybrany klawisz: " << selected_key << "\n";
                                    break;
                                }
                            }
                        }
                        else if (settingsKeyText4.getGlobalBounds().contains(mousePos)) {
                            std::cout << "1.4\n";
                            keyOption.setPosition(settingsKeyText4.getPosition());
                            keyOption.move(150.0f, 0.0f);
                            window.draw(keyOption);
                            window.display();
                            while (window.waitEvent(event)) {
                                if (event.type == sf::Event::KeyPressed) {
                                    selected_key = event.key.code;
                                    globalSettings.setKeyConfirm(selected_key);
                                    std::cout << "Wybrany klawisz: " << selected_key << "\n";
                                    break;
                                }
                            }
                        }
                        else if (settingsKeyText5.getGlobalBounds().contains(mousePos)) {
                            std::cout << "1.5\n";
                            keyOption.setPosition(settingsKeyText5.getPosition());
                            keyOption.move(150.0f, 0.0f);
                            window.draw(keyOption);
                            window.display();
                            while (window.waitEvent(event)) {
                                if (event.type == sf::Event::KeyPressed) {
                                    selected_key = event.key.code;
                                    globalSettings.setKeyTab(selected_key);
                                    std::cout << "Wybrany klawisz: " << selected_key << "\n";
                                    break;
                                }
                            }
                        }
                        else if (settingsKeyText6.getGlobalBounds().contains(mousePos)) {
                            std::cout << "1.6\n";
                            keyOption.setPosition(settingsKeyText6.getPosition());
                            keyOption.move(150.0f, 0.0f);
                            window.draw(keyOption);
                            window.display();
                            while (window.waitEvent(event)) {
                                if (event.type == sf::Event::KeyPressed) {
                                    selected_key = event.key.code;
                                    globalSettings.setKeyEscape(selected_key);
                                    std::cout << "Wybrany klawisz: " << selected_key << "\n";
                                    break;
                                }
                            }
                        }
                        else if (settingsReturnText.getGlobalBounds().contains(mousePos)) {
                            std::cout << "1.7\n";
                            return;
                        }
                        break;
                    case 2:
                        if (settingsReturnText.getGlobalBounds().contains(mousePos)) {
                            std::cout << "2.7\n";
                            return;
                        }
                        break;
                    default:
                        break;
                    }
                }
            }
        }

        window.clear();

        window.draw(creditsBackgroundSprite);
        window.draw(bottomTooltipRectangle);

        window.draw(settingsTitleText);

        window.draw(settingsChoiceText0);
        window.draw(settingsChoiceText1);
        window.draw(settingsChoiceText2);

        switch (selected_menu) {
        case 0:
            window.draw(settingsGameText0);
            window.draw(settingsGameText1);
            window.draw(settingsGameText2);
            highlightedChoiceOption.setString(settingsChoiceText0.getString());
            highlightedChoiceOption.setPosition(settingsChoiceText0.getPosition());
            switch (selected_option) {
            case 0:
                highlightedOption.setString(settingsGameText0.getString());
                highlightedOption.setPosition(settingsGameText0.getPosition());
                break;
            case 1:
                highlightedOption.setString(settingsGameText1.getString());
                highlightedOption.setPosition(settingsGameText1.getPosition());
                break;
            case 2:
                highlightedOption.setString(settingsGameText2.getString());
                highlightedOption.setPosition(settingsGameText2.getPosition());
                break;
            case 7:
                highlightedOption.setString(settingsReturnText.getString());
                highlightedOption.setPosition(settingsReturnText.getPosition());
                break;
            default:
                break;
            }
            break;
        case 1:
            window.draw(settingsKeyText0);
            window.draw(settingsKeyText1);
            window.draw(settingsKeyText2);
            window.draw(settingsKeyText3);
            window.draw(settingsKeyText4);
            window.draw(settingsKeyText5);
            window.draw(settingsKeyText6);
            highlightedChoiceOption.setString(settingsChoiceText1.getString());
            highlightedChoiceOption.setPosition(settingsChoiceText1.getPosition());
            switch (selected_option) {
            case 0:
                highlightedOption.setString(settingsKeyText0.getString());
                highlightedOption.setPosition(settingsKeyText0.getPosition());
                break;
            case 1:
                highlightedOption.setString(settingsKeyText1.getString());
                highlightedOption.setPosition(settingsKeyText1.getPosition());
                break;
            case 2:
                highlightedOption.setString(settingsKeyText2.getString());
                highlightedOption.setPosition(settingsKeyText2.getPosition());
                break;
            case 3:
                highlightedOption.setString(settingsKeyText3.getString());
                highlightedOption.setPosition(settingsKeyText3.getPosition());
                break;
            case 4:
                highlightedOption.setString(settingsKeyText4.getString());
                highlightedOption.setPosition(settingsKeyText4.getPosition());
                break;
            case 5:
                highlightedOption.setString(settingsKeyText5.getString());
                highlightedOption.setPosition(settingsKeyText5.getPosition());
                break;
            case 6:
                highlightedOption.setString(settingsKeyText6.getString());
                highlightedOption.setPosition(settingsKeyText6.getPosition());
                break;
            case 7:
                highlightedOption.setString(settingsReturnText.getString());
                highlightedOption.setPosition(settingsReturnText.getPosition());
                break;
            default:
                break;
            }
            break;
        case 2:
            highlightedChoiceOption.setString(settingsChoiceText2.getString());
            highlightedChoiceOption.setPosition(settingsChoiceText2.getPosition());
            switch (selected_option) {
            case 7:
                highlightedOption.setString(settingsReturnText.getString());
                highlightedOption.setPosition(settingsReturnText.getPosition());
                break;
            default:
                break;
            }
            window.draw(settingsInstruction);
            break;
        default:
            break;
        }

        window.draw(settingsReturnText);

        window.draw(highlightedOption);

        window.draw(bottomText);

        window.draw(highlightedChoiceOption);
        window.display();
    }
}

void showCredits(sf::RenderWindow& window) {
    extern Settings globalSettings;

    sf::Color colorGray(128, 128, 128);

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
    float scaleX = static_cast<float>(800) / originalSize.x;
    float scaleY = static_cast<float>(600) / originalSize.y;
    // Set the scale of the sprite
    creditsBackgroundSprite.setScale(scaleX, scaleY);

    sf::RectangleShape bottomTooltipRectangle(sf::Vector2f(798, 25)); // Set the size of the rectangle
    bottomTooltipRectangle.setPosition(2, 575);
    bottomTooltipRectangle.setFillColor(colorGray);
    bottomTooltipRectangle.setOutlineThickness(2);
    bottomTooltipRectangle.setOutlineColor(sf::Color::Black);

    sf::Text creditsTitleText("Credits", font_arial, 50);
    creditsTitleText.setOutlineThickness(2);
    creditsTitleText.setPosition((800 - creditsTitleText.getGlobalBounds().width) / 2, 0);
    creditsTitleText.setFillColor(sf::Color::Red);

    sf::Text creditsText0("Dev Team:", font_arial, 40);
    creditsText0.setOutlineThickness(2);
    creditsText0.setPosition((800 - creditsText0.getGlobalBounds().width) / 2, 100);

    sf::Text creditsText1("Creator: Mateusz Zaczeniuk", font_arial, 40);
    creditsText1.setOutlineThickness(2);
    creditsText1.setPosition((800 - creditsText1.getGlobalBounds().width) / 2, 150);

    sf::Text creditsText2("Emotional Support: Teo", font_arial, 40);
    creditsText2.setOutlineThickness(2);
    creditsText2.setPosition((800 - creditsText2.getGlobalBounds().width) / 2, 200);

    sf::Text creditsTextReturn("Return", font_arial, 40);
    creditsTextReturn.setOutlineThickness(2);
    creditsTextReturn.setPosition((800 - creditsTextReturn.getGlobalBounds().width) / 2, 500);

    sf::Text highlightedOption("", font_arial, 40);
    highlightedOption.setFillColor(sf::Color::Red);

    sf::Text bottomText("", font_arial, 15);
    bottomText.setPosition((800 - bottomText.getGlobalBounds().width) / 2, 575);
    bottomText.setOutlineThickness(1);

    std::cout << "CreditsFunction\n";
    int selected_option = -1;
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
                    if (selected_option = 0) {
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
        
        window.draw(bottomTooltipRectangle);

        window.draw(creditsText0);
        window.draw(creditsText1);
        window.draw(creditsText2);

        window.draw(creditsTitleText);
        window.draw(creditsTextReturn);

        window.draw(highlightedOption);

        window.draw(bottomText);
        window.display();
    }
}

void showSave(sf::RenderWindow& window) {
    std::cout << "SaveFunction";
}

void showLoad(sf::RenderWindow& window) {
    std::cout << "LoadFunction";
}