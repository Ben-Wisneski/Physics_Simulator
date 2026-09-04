#include <iostream>
#include "events.h"
#include "object.h"



//global variable to track if the shape is being dragged only used in the handleObjectEvents function
struct draggedData
{
    bool isDragged = false;
    sf::Vector2f dragOffset{ 0.f, 0.f };
    int indexOfDraggedCirc = -1;
    int indexOfDraggedRect = -1;
};

draggedData data;


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
    else if (const auto* resized = event.getIf<sf::Event::Resized>())
    {
		//handle resizing the window in here
        resized->size.x;
        resized->size.y;
    }
}

void handleRightClickMenu(sf::RenderWindow& window, const sf::Event& event, menu& menu)
{
	if (menu.getIsVisible())
	{
		// Handle right click menu events here
		if (event.is<sf::Event::MouseButtonPressed>())
		{
            
            if (event.getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left)
            {
                // Hide the right click menu when left mouse button is pressed
                menu.setIsVisible(false);
            }
        }
	}
}

void handleObjectEvents(sf::RenderWindow& window, const sf::Event& event, std::vector<sf::CircleShape>& circleVector, std::vector<menu>& menuVector, std::vector<sf::RectangleShape>& rectVector, menu& menu){
	// Handle events related to objects here
	//should be able to click and drag the shape around the window
    if (event.is<sf::Event::MouseButtonPressed>())
    {
        //Here is where you can handle mouse click events
		//left click to drag the shape around the window first
        if (event.getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left) {
            const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>();
            sf::Vector2i mousePos = mouseButtonPressed->position;
            for (int index = 0; index < circleVector.size(); ++index)
            {
                if (circleVector[index].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                {
                    //set the isDragged flag to true and store the index of the shape being dragged
                    data.isDragged = true;
                    data.indexOfDraggedCirc = index;
                    //mark the offset between the mouse position and the shape's position so that the shape doesn't jump to the mouse position when dragging
                    data.dragOffset = static_cast<sf::Vector2f>(mousePos) - circleVector[index].getPosition();

                }
            }
            for (int index = 0; index < rectVector.size(); ++index)
            {
                if (rectVector[index].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                {
                    //set the isDragged flag to true and store the index of the shape being dragged
                    data.isDragged = true;
                    data.indexOfDraggedRect = index;
                    //mark the offset between the mouse position and the shape's position so that the shape doesn't jump to the mouse position when dragging
                    data.dragOffset = static_cast<sf::Vector2f>(mousePos) - rectVector[index].getPosition();

                }
            }
        }
        //where the right click menu is handeled
        else if (event.getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Right)
        {
            const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>();
			const auto mousePos = mouseButtonPressed->position;
            menu.setPosition(static_cast<sf::Vector2f>(mousePos));
            menu.setIsVisible(true);
			for (int index = 0; index < circleVector.size(); ++index){
                if (circleVector[index].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    menu.setOnObject(true);
                }
            }
        }
    }

    if(event.is<sf::Event::MouseButtonReleased>())
    {
		//reset the isDragged flag and the index of the shape being dragged
        data.isDragged = false;
		data.indexOfDraggedCirc = -1;
		data.indexOfDraggedRect = -1;
    }

    if (data.isDragged && event.is<sf::Event::MouseMoved>())
    {
        const auto* mouseButtonMoved = event.getIf<sf::Event::MouseMoved>();
        sf::Vector2i mousePos = mouseButtonMoved->position;
		//here is where to use the dragOffset and the indexOfDraggedShape to move the shape around the window
        if(data.indexOfDraggedCirc != -1)
            circleVector[data.indexOfDraggedCirc].setPosition(static_cast<sf::Vector2f>(mousePos) - data.dragOffset);
        else
            rectVector[data.indexOfDraggedRect].setPosition(static_cast<sf::Vector2f>(mousePos) - data.dragOffset);
    }
}

void processEvents(sf::RenderWindow& window, const sf::Event& event, std::vector<sf::CircleShape>& circleVector, std::vector<sf::RectangleShape>& rectVector, std::vector<menu>& menuVector, menu& menu)
{
	handleWindowEvents(window, event);
    handleRightClickMenu(window, event, menu);
	handleObjectEvents(window, event, circleVector, menuVector, rectVector, menu);
}