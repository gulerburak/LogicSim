#pragma once
#include "Object.h"
#include "Pin.h"
#include "LogicElement.h"
class Wire: public Object {
public:
	sf::Vertex line[2];
	Pin* pins[2];
};