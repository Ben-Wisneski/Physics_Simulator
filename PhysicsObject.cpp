#include "PhysicsObject.h"

void PhysicsObject::update(float deltaTime, sf::Transformable& shape)
{
	if(!isDragged)
	{
		// Kinematic Euler integration
		velocity += acceleration * deltaTime;
		position += velocity * deltaTime;
	}

	// Apply updated position directly to SFML shape
	shape.setPosition(position);
}