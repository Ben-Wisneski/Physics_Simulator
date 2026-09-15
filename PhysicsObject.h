#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class PhysicsObject
{
private:
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	float mass;
	bool isDragged = false; // Flag to indicate if the object is being dragged
public:
	PhysicsObject(sf::Vector2f startPos = { 0.f, 0.f }, float m = 1.0f)
		: position(startPos), velocity(0.f, 0.f), acceleration(0.f, 980.0f), mass(m) {
	}

	sf::Vector2f getPosition() const { return position; }
	sf::Vector2f getVelocity() const { return velocity; }
	sf::Vector2f getAcceleration() const { return acceleration; }
	float getMass() const { return mass; }

	void setPosition(const sf::Vector2f& pos) { position = pos; }
	void setVelocity(const sf::Vector2f& vel) { velocity = vel; }
	void setAcceleration(const sf::Vector2f& acc) { acceleration = acc; }
	void setMass(float m) { mass = m; }
	void setDragged(bool dragged) { isDragged = dragged; }

	// Updates internal kinematic state and applies position back to visual shape
	void update(float deltaTime, sf::Transformable& shape);
};
