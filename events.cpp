#include <iostream>
#include "events.h"
#include "object.h"

void handleWindowEvents(sf::RenderWindow& window, const sf::Event& event)
{
    //handles closing the window and pressing escape to close the window
    if (event.is<sf::Event::Closed>())
    {
        window.close();
    }
    else if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
    {
        //handle pressing key events in here
        if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
            window.close();
    }
}

void handleObjectEvents(sf::RenderWindow& window, const sf::Event& event, sf::CircleShape& shape){
	// Handle events related to objects here
	//should be able to click and drag the shape around the window
    bool isDragged = false;

		
    if (event.is<sf::Event::MouseButtonPressed>())
    {
        //Here is where you can handle mouse click events on the shape
            
        const auto *mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>();
        sf::Vector2i mousePos = mouseButtonPressed->position;
		std::cout << "Mouse clicked at: " << mousePos.x << ", " << mousePos.y << std::endl;
        std::cout << "Object position: " << shape.getPosition().x << ", " << shape.getPosition().y << std::endl;
        if(static_cast<sf::Vector2f>(mousePos) == shape.getPosition())
        {
			isDragged = true;
            std::cout << "Clicked the object!" << std::endl;
        }

    }

    if(event.is<sf::Event::MouseButtonReleased>())
    {
        isDragged = false;
    }

    if (isDragged && event.is<sf::Event::MouseMoved>())
    {
        const auto* mouseButtonMoved = event.getIf<sf::Event::MouseMoved>();
        sf::Vector2i mousePos = mouseButtonMoved->position;
        std::cout << "Mouse moved to: " << mousePos.x << ", " << mousePos.y << std::endl;
    }
}

void processEvents(sf::RenderWindow& window, const sf::Event& event, sf::CircleShape& shape)
{
	handleWindowEvents(window, event);
	handleObjectEvents(window, event, shape);
}