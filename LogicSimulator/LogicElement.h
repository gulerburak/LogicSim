#pragma once
#include "Object.h"
#include "Pin.h"

class LogicElement :public Object {

public:
	Pin pins[4];
	int numPins; //Number of pins of the logic element
};
