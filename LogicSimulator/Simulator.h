#pragma once
#include "Object.h"
#include <SFML/Graphics.hpp>

class Simulator
{
	// create start and stop button
	sf::RectangleShape startButton;
	sf::RectangleShape stopButton;
	
	// add text to buttons
	
public:
	sf::RenderWindow* window; //Pointer to SFML render window
	Object* objects; //Pointer to a list of objects on screen
	Simulator(sf::RenderWindow* window);
	~Simulator();
};

Simulator::Simulator(sf::RenderWindow* window)
{
	this->window = window;
	
}

Simulator::~Simulator()
{
	delete window, objects;
}