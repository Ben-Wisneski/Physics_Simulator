#include <SFML/Graphics.hpp>
#include "events.h"
#include "configuration.h"
#include "object.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), config::WINDOW_TITLE, sf::Style::Default);
    window.setFramerateLimit(config::FRAMERATE_LIMIT);
    // Force OS focus onto the SFML window
    window.requestFocus();


    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
	shape.setPointCount(5);


    while (window.isOpen())
    {
		// Handle events
        while (const std::optional event = window.pollEvent()) { processEvents(window, *event, shape); }
            
		// Clear the window, draw the shape, and display the contents
        window.clear();
        window.draw(shape);
        window.display();
    }
}