#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "events.h"
#include "configuration.h"
#include "object.h"
#include "menu.h"

struct objects {
	std::vector<sf::CircleShape> circleVector;
	std::vector<sf::RectangleShape> rectVector;
	std::vector<menu> menuVector;
};

//Menu that can be accessed in the main loop and event processing
menu* Menu = new menu();
objects* objectList = new objects();

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), config::WINDOW_TITLE, sf::Style::Default);
    window.setFramerateLimit(config::FRAMERATE_LIMIT);
    // Force OS focus onto the SFML window
    window.requestFocus();
    
    /*
        Here is where you initialize shapes before adding to the vector
    */
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
	shape.setPointCount(5);

	sf::CircleShape shape2(50.f);
	shape2.setFillColor(sf::Color::Blue);


	//add the shape to a vector of shapes so that we can draw multiple shapes in the window
	//have to have multiple vectors for different shapes because they are different types and cannot be stored in the same vector
	objectList->circleVector.push_back(shape);
    std::vector<sf::RectangleShape> rectVector = {};
	std::vector<menu> menuVector = { *Menu };
    while (window.isOpen())
    {
		// Handle events
        while (const std::optional event = window.pollEvent()) { processEvents(window, *event, objectList->circleVector, objectList->rectVector, objectList->menuVector, *Menu); }
            
		// Clear the window, draw the shape vector, and display the contents
        window.clear();
		//drawing all the vectors of shapes in the window
        for (const auto& s : objectList->circleVector) window.draw(s);
        for (const auto& r : objectList->rectVector) window.draw(r);
        
        if (Menu->getIsVisible()) {
            window.draw(Menu->getMenuBox());
        }
        window.display();
    }
    delete objectList;
}