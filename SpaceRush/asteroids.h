#pragma once

#include <SFML/Graphics.hpp>
#include "resourceholder.h"
#include "resourceidentifiers.h"


class Asteroid
{
public:
	static void loadTextures();
	void render(sf::RenderTarget& l_window);
	void update(sf::Time dt);
	Asteroid();
	sf::IntRect getTextureRect();
	const sf::Texture* getTexture();
	const sf::Transform getInverseTransform();
	sf::FloatRect getBounds();
	void decreaseHealth(int);
	bool isDestroyed();
	const sf::Vector2f getPosition();
	//sf::Vector2f& getVelocityRef();
	sf::Vector2f dampingVelocity;
private:
	static TextureHolder asteriodsTex;
	static int screenWidth;

	int mHealth;
	sf::Sprite asteroid;

	float angularVelocity = 0.f;
	float scale = 0.5f;
	sf::Vector2f velocity;
	sf::Vector2f position;
	sf::Vector2f direction;

};
