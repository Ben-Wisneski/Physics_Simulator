#pragma once
#include <string>
#include <SFML/Graphics.hpp>
//this is where to change the configuration of the application quickly and easily without having to dig through the code
namespace config {
	//window configuration
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;
	const std::string WINDOW_TITLE = "My SFML Application";
	const int FRAMERATE_LIMIT = 60;

	static const sf::Vector2f menuBoxSize = { 200.f, 66.f };
	static const sf::Vector2f menuItemBoxSize = { 200.f, 33.f };
}