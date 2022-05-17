#pragma once

class LED : public LogicElement
{
public:
	LED(sf::RenderWindow* window, float x, float y);
	int calculateState(LogicElement*);
	~LED();
	void drawObject(sf::RenderWindow*);
};

LED::LED(sf::RenderWindow* window, float x, float y)
{
	
	objID = LEDtype;
	this->window = window;
	numPins = 2;
	pins[0].setType(INPUT);
	pins[1].setType(OUTPUT);

	pins[0].dad = this;
	pins[1].dad = this;
	
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

int LED::calculateState(LogicElement* x)
{
	x->pins[1].setState(x->pins[0].getState());
	return x->pins[1].getState();
}