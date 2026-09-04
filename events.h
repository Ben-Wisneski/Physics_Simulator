#pragma once
#include <SFML/Graphics.hpp>
#include "menu.h"


void handleWindowEvents(sf::RenderWindow&, const sf::Event&);

void handleRightClickMenu(sf::RenderWindow&, const sf::Event&, menu&);

void handleObjectEvents(sf::RenderWindow&, const sf::Event&, std::vector<sf::CircleShape>&, std::vector<menu>&, std::vector<sf::RectangleShape>&, menu&);

void processEvents(sf::RenderWindow&, const sf::Event&, std::vector<sf::CircleShape>&, std::vector<sf::RectangleShape>&, std::vector<menu>&, menu&);