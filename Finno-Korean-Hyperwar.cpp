#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "Files/MenuView.h"
#include "Classes/Settings.cpp"

Settings globalSettings;

int main() {

    std::cout << "Game Init\n";

    sf::RenderWindow window(sf::VideoMode(800, 600), "FK-Hyperwar");

    showMenu(window);

    return 0;
}