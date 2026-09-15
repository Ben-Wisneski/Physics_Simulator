#include <iostream>
#include "events.h"

//global variable to track if the shape is being dragged only used in the handleObjectEvents function
struct draggedData
{
    bool isDragged = false;
    sf::Vector2f dragOffset{ 0.f, 0.f };
    sf::Vector2f lastMousePos{ 0.f, 0.f }; // Track previous position for velocity calculation and throwing object
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

void handleObjectEvents(sf::RenderWindow& window, const sf::Event& event, std::vector<sf::CircleShape>& circleVector, std::vector<menu>& menuVector, std::vector<sf::RectangleShape>& rectVector, std::vector<PhysicsObject>& PhysicsObjects, menu& menu){
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
                    PhysicsObjects[index].setDragged(true); // Set the isDragged flag in the PhysicsObject
                    data.lastMousePos = static_cast<sf::Vector2f>(mousePos);
                    data.indexOfDraggedCirc = index;
                    //mark the offset between the mouse position and the shape's position so that the shape doesn't jump to the mouse position when dragging
                    data.dragOffset = static_cast<sf::Vector2f>(mousePos) - circleVector[index].getPosition();
					break; //stop checking when found the first shape that contains the mouse position
                }
            }
            for (int index = 0; index < rectVector.size(); ++index)
            {
                if (rectVector[index].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                {
                    data.isDragged = true;
                    data.indexOfDraggedRect = index;
                    data.lastMousePos = static_cast<sf::Vector2f>(mousePos);
                    data.dragOffset = static_cast<sf::Vector2f>(mousePos) - rectVector[index].getPosition();

                    // Calculate offset index in physicsVector (Circle Count + Rectangle Index)
                    int physIndex = circleVector.size() + index;
                    PhysicsObjects[physIndex].setDragged(true);
                    PhysicsObjects[physIndex].setVelocity({ 0.f, 0.f });
                    break; //stop checking when found the first shape that contains the mouse position
                }
            }
        }
		//where the right event is handled to show the right click menu
        else if (event.getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Right)
        {
            const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>();
			const auto mousePos = mouseButtonPressed->position;
            menu.setPosition(static_cast<sf::Vector2f>(mousePos));
            menu.setIsVisible(true);

            bool onCircleObject = false;
			bool onRectObject = false;

			for (int index = 0; index < circleVector.size(); ++index){
				//check if the mouse position is on top of circle shape for each index of the circle vector
                onCircleObject = circleVector[index].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
                if (onCircleObject) {
                    menu.setOnObject(true);
					continue; // Exit the loop if the mouse is on a circle object
                }
            }
            for (int index = 0; index < rectVector.size(); ++index) {
				//check if the mouse position is on top of rectangle shape for each index of the rectangle vector
                onRectObject = rectVector[index].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
                if (onCircleObject) { continue; }
                if (onRectObject) {
                    menu.setOnObject(true);
					continue; // Exit the loop if the mouse is on a rectangle object
                }
            }
        }
    }

    if(event.is<sf::Event::MouseButtonReleased>())
    {
		//reset the isDragged flag and the index of the shape being dragged
        data.isDragged = false;
        for(auto& obj : PhysicsObjects)
        {
            obj.setDragged(false); // Set the isDragged flag in the PhysicsObject
        }
		data.indexOfDraggedCirc = -1;
		data.indexOfDraggedRect = -1;
    }

    if (data.isDragged && event.is<sf::Event::MouseMoved>())
    {
        const auto* mouseButtonMoved = event.getIf<sf::Event::MouseMoved>();
        sf::Vector2i mousePos = mouseButtonMoved->position;
        sf::Vector2f newPos = static_cast<sf::Vector2f>(mousePos) - data.dragOffset;

        if (data.indexOfDraggedCirc != -1)
        {
            // Update shape position
            circleVector[data.indexOfDraggedCirc].setPosition(newPos);

            // Sync physics object position and clear velocity/acceleration while held
            PhysicsObjects[data.indexOfDraggedCirc].setPosition(newPos);
            PhysicsObjects[data.indexOfDraggedCirc].setVelocity({ 0.f, 0.f });

			//show the velocity of the shape being dragged in the console
            sf::Vector2f mouseDelta = static_cast<sf::Vector2f>(mousePos) - data.lastMousePos;
            
            // Multiply by target FPS (e.g., 60) to convert movement per frame into velocity units (pixels/second)
            PhysicsObjects[data.indexOfDraggedCirc].setVelocity(mouseDelta * 60.f);

            data.lastMousePos = static_cast<sf::Vector2f>(mousePos);
        }

        if (data.indexOfDraggedRect != -1)
        {
            // Update shape position
            rectVector[data.indexOfDraggedRect].setPosition(newPos);

            // Sync physics object position and clear velocity/acceleration while held
            PhysicsObjects[data.indexOfDraggedRect].setPosition(newPos);
            PhysicsObjects[data.indexOfDraggedRect].setVelocity({ 0.f, 0.f });

            //show the velocity of the shape being dragged in the console
            sf::Vector2f mouseDelta = static_cast<sf::Vector2f>(mousePos) - data.lastMousePos;

            // Multiply by target FPS (e.g., 60) to convert movement per frame into velocity units (pixels/second)
            PhysicsObjects[data.indexOfDraggedRect].setVelocity(mouseDelta * 60.f);

            data.lastMousePos = static_cast<sf::Vector2f>(mousePos);
        }
    }
}

void processEvents(sf::RenderWindow& window, const sf::Event& event, std::vector<sf::CircleShape>& circleVector, std::vector<sf::RectangleShape>& rectVector, std::vector<menu>& menuVector, std::vector<PhysicsObject>& PhysicsObjects, menu& menu)
{
	handleWindowEvents(window, event);
    handleRightClickMenu(window, event, menu);
	handleObjectEvents(window, event, circleVector, menuVector, rectVector, PhysicsObjects, menu);
}