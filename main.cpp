#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "events.h"
#include "configuration.h"
#include "menu.h"
#include "PhysicsObject.h"

struct objects {
    std::vector<sf::CircleShape> circleVector;
    std::vector<sf::RectangleShape> rectVector;
    std::vector<menu> menuVector;
    std::vector<PhysicsObject> physicsVector;
};

//Menu that can be accessed in the main loop and event processing
menu* Menu = new menu();
//struct that holds all the vectors of shapes in menus in one spot
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
   

	//add the shape to a vector of shapes so that we can draw multiple shapes in the window
	//have to have multiple vectors for different shapes because they are different types and cannot be stored in the same vector
	objectList->circleVector.push_back(shape);
	//link the physics object to the shape so that we can update the position of the shape based on the physics object
    objectList->physicsVector.emplace_back(shape.getPosition());
	objectList->menuVector.push_back(*Menu);


	sf::Clock clock; // Clock to measure time between frames

    while (window.isOpen())
    {
		float deltaTime = clock.restart().asSeconds(); // Time elapsed since last frame

        // Apply physics updates to circle shapes
        for (int i = 0; i < objectList->circleVector.size(); i++) {
            objectList->physicsVector[i].update(deltaTime, objectList->circleVector[i]);
        }

		// Handle events
        while (const std::optional event = window.pollEvent()) { processEvents(window, *event, objectList->circleVector, objectList->rectVector, objectList->menuVector, objectList->physicsVector, *Menu); }



		// Clear the window, draw the shape vector, and display the contents
        window.clear();
		//drawing all the vectors of shapes in the window
        for (const auto& s : objectList->circleVector) window.draw(s);
        for (const auto& r : objectList->rectVector) window.draw(r);
        
        if (Menu->getIsVisible()) {
            window.draw(Menu->getMenuBox());
            window.draw(Menu->getMenuItemBox_addObject());
            window.draw(Menu->getMenuItemBox_deleteObject());
        }
        window.display();
    }

	//delete the dynamically allocated menu and objectList to avoid memory leaks
    delete Menu;
    delete objectList;
}