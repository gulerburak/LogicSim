#pragma once

class LogicElement :public Object {
	Pin pins[4]; //List of pins of the logic element
	int numPins; //Number of pins of the logic element 
};