#include "menu.h"
//constructor for the menu class
menu::menu() 
{
	isVisible = false;
	onObject = false;
	sf::Vector2f position = { 0.f, 0.f };
	sf::RectangleShape menuBox = sf::RectangleShape({ 200.f, 100.f });
	menuBox.setFillColor(sf::Color::White);
	menuBox.setSize({200.f, 100.f});

	//sf::RectangleShape menuItemBox_addObject = sf::RectangleShape({ 200.f, 50.f });
	//sf::RectangleShape menuItemBox_deleteObject = sf::RectangleShape({ 200.f, 50.f });
}

//getter and setter functions for the private variables
bool menu::getIsVisible() const { return isVisible; }
bool menu::getOnObject() const { return onObject; }
sf::Vector2f menu::getPosition() const { return position; }
void menu::setIsVisible(bool visible) { isVisible = visible; }
void menu::setOnObject(bool onObj) { onObject = onObj; }
void menu::setPosition(sf::Vector2f pos) 
{ 
	position = pos; 
	menuBox.setPosition(position);
}

sf::RectangleShape menu::getMenuBox() { 
	menuBox.setSize({200.f, 100.f});
	return menuBox; }
