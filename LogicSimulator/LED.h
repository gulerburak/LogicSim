#pragma once

class LED : public LogicElement
{
public:
	LED(sf::RenderWindow* window, float x, float y);
	~LED();
	void drawObject(sf::RenderWindow*);
};

LED::LED(sf::RenderWindow* window, float x, float y)
{
	setPinsDad(this);
	objID = LEDtype;
	this->window = window;
	numPins = 2;
	state = 0;
	textures[0].loadFromFile("../assets/LEDOFF.png");
	textures[1].loadFromFile("../assets/LEDON.png");
	sprite.setTexture(textures[0]);
	sprite.setOrigin(20.0f, 39.0f);
	sprite.setPosition(x, y);
}

void LED::drawObject(sf::RenderWindow* window) 
{
	sprite.setTexture(textures[state]);
	window->draw(sprite);
}