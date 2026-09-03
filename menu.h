#pragma once
#include <SFML/Graphics.hpp>
class menu
{
private:
	bool isVisible;
	bool onObject;
	sf::Vector2f position;
	sf::RectangleShape menuBox;
	//sf::RectangleShape menuItemBox_addObject;
	//sf::RectangleShape menuItemBox_deleteObject;
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

	sf::RectangleShape getMenuBox() const;
};

