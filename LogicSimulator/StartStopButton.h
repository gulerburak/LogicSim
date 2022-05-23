#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"

class StartStopButton : public Object
{
	public:
	StartStopButton(sf::RenderWindow*, float, float);
	void drawObject(sf::RenderWindow*);
};

StartStopButton::StartStopButton(sf::RenderWindow* window, float x, float y)
{
	objID = BUTTON;
	this->window = window;
	textures[0].loadFromFile("../assets/STOP.png");
	textures[1].loadFromFile("../assets/START.png");
	
	sprite.setTexture(textures[1]);
	sprite.setPosition(x, y);
	state = 1;
}

void StartStopButton::drawObject(sf::RenderWindow* window)
{

	sprite.setTexture(textures[state]);
	window->draw(sprite);
}

