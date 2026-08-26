#pragma once
#include <SFML/Graphics.hpp>

void handleWindowEvents(sf::RenderWindow& window, const sf::Event& event);

void handleObjectEvents(sf::RenderWindow& window, const sf::Event& event, sf::CircleShape& shape);

void processEvents(sf::RenderWindow& window, const sf::Event& event, sf::CircleShape& shape);