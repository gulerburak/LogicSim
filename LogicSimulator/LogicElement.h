#pragma once
#include "Object.h"
#include "Pin.h"

class LogicElement :public Object {

public:
	Pin pins[4];
	int numPins; //Number of pins of the logic element
	
	virtual int calculateState(LogicElement*)=0;
	
};


int LogicElement::calculateState(LogicElement* x)
{
	return 0;
}
