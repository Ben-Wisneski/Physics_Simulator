#pragma once
#include <SFML/Graphics.hpp>
#include "menu.h"


void handleWindowEvents(sf::RenderWindow& window, const sf::Event& event);

void handleRightClickMenu(sf::RenderWindow& window, const sf::Event& event, menu& menu);

void handleObjectEvents(sf::RenderWindow& window, const sf::Event& event, std::vector<sf::CircleShape>& circleVector, menu& menu);

void processEvents(sf::RenderWindow& window, const sf::Event& event, std::vector<sf::CircleShape>& circleVector, menu& menu);