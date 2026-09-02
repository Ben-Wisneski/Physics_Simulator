#include <vector>
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

	sf::CircleShape shape2(50.f);
	shape2.setFillColor(sf::Color::Blue);
	shape2.setPosition({ 200.f, 200.f });

    std::vector<sf::CircleShape> circleVector = {shape, shape2};
    while (window.isOpen())
    {
		// Handle events
        while (const std::optional event = window.pollEvent()) { processEvents(window, *event, circleVector); }
            
		// Clear the window, draw the shape vector, and display the contents
        window.clear();
        for (const auto& s : circleVector) 
        {
            window.draw(s);
        }
        window.display();
    }
}