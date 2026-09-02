#include <iostream>
#include "events.h"
#include "object.h"

//global variable to track if the shape is being dragged
bool isDragged = false;
sf::Vector2f dragOffset;
int indexOfDraggedShape = -1;

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

void handleObjectEvents(sf::RenderWindow& window, const sf::Event& event, std::vector<sf::CircleShape>& circleVector){
	// Handle events related to objects here
	//should be able to click and drag the shape around the window
    

		
    if (event.is<sf::Event::MouseButtonPressed>())
    {
        //Here is where you can handle mouse click events on the shape
            
        const auto *mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>();
        sf::Vector2i mousePos = mouseButtonPressed->position;
        for(int index = 0; index < circleVector.size(); ++index)
        {
            if (circleVector[index].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
            {
				//set the isDragged flag to true and store the index of the shape being dragged
                isDragged = true;
				indexOfDraggedShape = index;
                //mark the offset between the mouse position and the shape's position so that the shape doesn't jump to the mouse position when dragging
                dragOffset = static_cast<sf::Vector2f>(mousePos) - circleVector[index].getPosition();

            }
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
		//here is where to use the dragOffset and the indexOfDraggedShape to move the shape around the window
        circleVector[indexOfDraggedShape].setPosition(static_cast<sf::Vector2f>(mousePos) - dragOffset);
    }
}

void processEvents(sf::RenderWindow& window, const sf::Event& event, std::vector<sf::CircleShape>& circleVector)
{
	handleWindowEvents(window, event);
	handleObjectEvents(window, event, circleVector);
}