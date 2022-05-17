#pragma once
#include "Object.h"
#include "Pin.h"

class LogicElement :public Object {

public:
	Pin pins[4];
	int numPins; //Number of pins of the logic element
	void setPinsDad(Object*);
};

void LogicElement::setPinsDad(Object *dad)
{
	for (int i = 0; i < numPins; i++)
	{
		pins[i].dad = dad;
	}

}