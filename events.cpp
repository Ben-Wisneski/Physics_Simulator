#include "events.hpp"

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
        if (event.is<sf::Event::MouseButtonPressed>())
        {
            window.close();
        }
}

void processEvents(sf::RenderWindow& window, const sf::Event& event, sf::CircleShape& shape)
{
	handleWindowEvents(window, event);
	handleObjectEvents(window, event, shape);
}