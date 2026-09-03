#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "events.h"
#include "configuration.h"
#include "object.h"
#include "menu.h"

//Menu that can be accessed in the main loop and event processing
menu* Menu = new menu();

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), config::WINDOW_TITLE, sf::Style::Default);
    window.setFramerateLimit(config::FRAMERATE_LIMIT);
    // Force OS focus onto the SFML window
    window.requestFocus();


    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
	shape.setPointCount(5);

    std::vector<sf::CircleShape> circleVector = {shape};
    while (window.isOpen())
    {
		// Handle events
        while (const std::optional event = window.pollEvent()) { processEvents(window, *event, circleVector, *Menu); }
            
		// Clear the window, draw the shape vector, and display the contents
        window.clear();
        for (const auto& s : circleVector) window.draw(s);

        if (Menu->getIsVisible()) window.draw(Menu->getMenuBox());

        window.display();
    }
}