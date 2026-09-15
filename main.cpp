#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "events.h"
#include "configuration.h"
#include "menu.h"
#include "PhysicsObject.h"

struct circledata_rectdata{
    std::vector<sf::CircleShape> circleVector;
    std::vector<sf::RectangleShape> rectVector;
};

struct objects {
    circledata_rectdata shapeData;
    std::vector<menu> menuVector;
    std::vector<PhysicsObject> physicsVector;
};

//Menu that can be accessed in the main loop and event processing
menu* Menu = new menu();
//struct that holds all the vectors of shapes in menus in one spot
objects* objectList = new objects();

int main()
{
	//create the window with the specified configuration
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), config::WINDOW_TITLE, sf::Style::Default, sf::State::Windowed);
    window.setFramerateLimit(config::FRAMERATE_LIMIT);

    // Initialize Circles
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPointCount(5);

    sf::CircleShape shape22(100.f);
    shape22.setFillColor(sf::Color::Blue);
    shape22.setPosition({ 200.f, 0.f });

    // Initialize Rectangles
    sf::RectangleShape rect1(sf::Vector2f(100.f, 50.f));
    rect1.setFillColor(sf::Color::Red);
    rect1.setPosition({ 400.f, 0.f });

    // 1. Add Circles and create matching PhysicsObjects
    objectList->shapeData.circleVector.push_back(shape);
    objectList->physicsVector.emplace_back(shape.getPosition());

    objectList->shapeData.circleVector.push_back(shape22);
    objectList->physicsVector.emplace_back(shape22.getPosition());

    // 2. Add Rectangles and create matching PhysicsObjects
    //objectList->shapeData.rectVector.push_back(rect1);
    //objectList->physicsVector.emplace_back(rect1.getPosition());
    
	objectList->menuVector.push_back(*Menu);


	sf::Clock clock; // Clock to measure time between frames

    while (window.isOpen())
    {
		float deltaTime = clock.restart().asSeconds(); // Time elapsed since last frame
        // 3. Update Circles Physics
        int numCircles = objectList->shapeData.circleVector.size();
        for (int i = 0; i < numCircles; i++) {
            objectList->physicsVector[i].update(deltaTime,objectList->shapeData.circleVector[i],window.getSize().x,window.getSize().y
            );
        }

        // 4. Update Rectangles Physics (Offset by number of circles)
        int numRects = objectList->shapeData.rectVector.size();
        for (int i = 0; i < numRects; i++) {
            objectList->physicsVector[numCircles + i].update(deltaTime,objectList->shapeData.rectVector[i],window.getSize().x,window.getSize().y);
        }

		// Handle events
        while (const std::optional event = window.pollEvent()) { processEvents(window, *event, objectList->shapeData.circleVector, objectList->shapeData.rectVector, objectList->menuVector, objectList->physicsVector, *Menu); }



		// Clear the window, draw the shape vector, and display the contents
        window.clear();
		//drawing all the vectors of shapes in the window
        for (const auto& s : objectList->shapeData.circleVector) window.draw(s);
        for (const auto& r : objectList->shapeData.rectVector) window.draw(r);
        
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