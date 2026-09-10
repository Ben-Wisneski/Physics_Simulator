#pragma once
#include <SFML/Graphics.hpp>
#include "configuration.h"
class menu
{
private:
	bool isVisible;
	bool onObject;
	sf::Vector2f position;
	sf::RectangleShape menuBox;
	sf::RectangleShape menuItemBox_addObject;
	sf::RectangleShape menuItemBox_deleteObject;
public:
	///brief Default constructor
	menu();
	//getter and setter functions for the private variables
	bool getIsVisible() const;
	bool getOnObject() const;
	sf::Vector2f getPosition() const;
	void setIsVisible(bool visible);
	void setOnObject(bool onObj);
	void setPosition(sf::Vector2f pos);


	sf::RectangleShape getMenuBox();
	sf::RectangleShape getMenuItemBox_addObject();
	sf::RectangleShape getMenuItemBox_deleteObject();
};

inline menu::menu()
{
	isVisible = false;
	onObject = false;
	position = { 0.f, 0.f };
	menuBox.setSize(config::menuBoxSize);
	menuItemBox_addObject.setSize(config::menuItemBoxSize);
	menuItemBox_deleteObject.setSize(config::menuItemBoxSize);
}

//getter and setter functions for the private variables
inline bool menu::getIsVisible() const { return isVisible; }
inline bool menu::getOnObject() const { return onObject; }
inline sf::Vector2f menu::getPosition() const { return position; }

inline void menu::setIsVisible(bool visible) { isVisible = visible; }
inline void menu::setOnObject(bool onObj) { onObject = onObj; }
inline void menu::setPosition(sf::Vector2f pos)
{
	position = pos;
	menuBox.setPosition(position);
	menuItemBox_addObject.setPosition(position);
	menuItemBox_deleteObject.setPosition(position + sf::Vector2f(0.f, config::menuItemBoxSize.y));
	menuBox.setFillColor(sf::Color::White);
	menuItemBox_addObject.setFillColor(sf::Color::Transparent);
	menuItemBox_deleteObject.setFillColor(sf::Color::Transparent);
}

inline sf::RectangleShape menu::getMenuBox() {
	return menuBox;
}

inline sf::RectangleShape menu::getMenuItemBox_addObject() {
	return menuItemBox_addObject;
}

inline sf::RectangleShape menu::getMenuItemBox_deleteObject() {
	return menuItemBox_deleteObject;
}