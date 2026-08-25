#include <SFML/Graphics.hpp>
#include "events.hpp"
#include "configuration.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), config::WINDOW_TITLE, sf::Style::None);
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