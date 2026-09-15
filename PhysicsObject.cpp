#include "PhysicsObject.h"
#include <SFML/Graphics.hpp>
void PhysicsObject::update(float deltaTime, sf::Shape& shape, unsigned int windowWidth, unsigned int windowHeight)
{
    if (!isDragged)
    {
        // Kinematic Euler integration
        velocity += acceleration * deltaTime;
        position += velocity * deltaTime;
    }
	else return; // Skip physics update if being dragged

	sf::FloatRect bounds = shape.getGlobalBounds();

    // Floor collision using bounds height
    if (position.y + bounds.size.y >= windowHeight) {
        position.y = windowHeight - bounds.size.y;
        velocity.y = -velocity.y * 0.5f;
    }

	//ceiling collision using bounds height
    if (position.y <= 0.f) {
        position.y = 0.f;
        velocity.y = -velocity.y * 0.5f;
    }

    // Left wall collision
    if (position.x <= 0.f) {
        position.x = 0.f;
        velocity.x = -velocity.x * 0.5f;
    }

    // Right wall collision using bounds width
    if (position.x + bounds.size.x >= windowWidth) {
        position.x = windowWidth - bounds.size.x;
        velocity.x = -velocity.x * 0.5f;
    }

	// Apply updated position directly to SFML shape
	shape.setPosition(position);
}