#pragma once
#include "Object.h"
#include "Pin.h"
#include "VDDGND.h"
#include "LED.h"

#include <SFML/Graphics.hpp>
using namespace std;

class Simulator
{
	// create start and stop button
	sf::RectangleShape startButton;
	sf::RectangleShape stopButton;
	Object* selectedObject;
	Wire* selectedWire;
	Object* headObj;
	Object* tailObj;
	
public:
	sf::RenderWindow* window; //Pointer to SFML render window
	Simulator(sf::RenderWindow*);
	~Simulator();
	void addObject(Object*);
	void deleteObject();
	//void deleteWire();
	void resetAllPins();
	void resetAllLEDs();
	void switchClockTo1();
	void switchClockTo0();
	void Simulate();
	Object* getTop();
	Object* getSelectedObject();
	void setSelectedObject(Object* );
	Wire* getSelectedWire();
	void setSelectedWire(Wire*);
	Object* GetObjectOnClick(float, float);
	Pin* getPinOnClick(LogicElement*, float, float);
	void createWire(Pin*, float, float);
	void unselectAll();
	void deletePicked();

	int calculateOutput(Pin*);
	
	Object* createObjectbyType(objType type, float, float);
};
/*void Simulator::deleteWire() {
	Object* temp = headObj;
	while (temp != nullptr) {
		if (temp->selected) {
			if()
		}
	}
}*/

void Simulator::resetAllPins()
{
	Object* temp = headObj;
	while (temp != nullptr)
	{
		if (temp->getObjType() != (WIREtype || Logic0 || Logic1))
		{
			LogicElement* t = static_cast<LogicElement*>(temp);
			for (int i = 0; i < t->numPins; i++)
				t->pins[i].setState(2);


		}
		temp = temp->next;
	}
}

void Simulator::resetAllLEDs()
{
	Object* temp = headObj;
	while (temp != nullptr)
	{
		if (temp->getObjType() == LEDtype) temp->state = 0;
		temp = temp->next;
	}
}

void Simulator::switchClockTo1()
{	
	cout << "Clock switched" << endl;
	Object* temp = headObj;
	while (temp != nullptr)
	{
		if (temp->getObjType() == CLOCK) temp->state = 1;
		temp = temp->next;
	}
}void Simulator::switchClockTo0()
{
	cout << "Clock switched" << endl;
	Object* temp = headObj;
	while (temp != nullptr)
	{
		if (temp->getObjType() == CLOCK) temp->state = 0;
		temp = temp->next;
	}
}

void Simulator::Simulate()
{
	
	resetAllPins();
	Object* temp = headObj;
	temp = headObj;
	while (temp != nullptr)
	{
		if (temp->getObjType() == LEDtype)
		{
			//recursively calculate output of all connected wires
			LogicElement* t = static_cast<LogicElement*>(temp);
			t->state = calculateOutput(&(t->pins[0]));
			cout <<"asdasd" << endl << t->state << endl;

		}
		temp = temp->next;
	}

}
int Simulator::calculateOutput(Pin *pin)
{
	
	Pin* connection = pin->connectedTo[0];
	
	if (connection == nullptr)
		return 0;
	
	cout << "a1" << endl;
	if (connection->getState() == 2)
	{
		cout << "a2" << endl;
		Object* temp = connection->dad;
		LogicElement* object = static_cast<LogicElement*>(temp);
		cout << "a3" << endl;
		cout << (connection->dad == nullptr) << endl;
		cout << object << endl;
		for (int i = 0; i < object->numPins; i++)
		{
			cout << "a4" << endl;
			Pin* object_pin = &(object->pins[i]);
			if (object_pin != nullptr)
			{
				cout << object_pin;
				if (object_pin->getType() != OUTPUT)
				{
					cout << "a5" << endl;
					int re = calculateOutput(object_pin);
					object_pin->setState(re);
				}
			}
		}
		object->calculateState(object);
		
		return connection->getState();
	}
	else
	{
		cout << "not" << endl;
		pin->setState(connection->getState());
		cout << connection->getState() << endl;
		return pin->getState();
	}

	
}


Simulator::Simulator(sf::RenderWindow* window)
{
	this->window = window;
	headObj = nullptr;
	tailObj = nullptr;
	selectedObject = nullptr;
	selectedWire = nullptr;
}

Simulator::~Simulator()
{
	//delete window, headObj, tailObj;
}

void Simulator::addObject(Object* newObj)
{
	cout << "Adding element" << endl;
		
	newObj->next = nullptr;
	// create a linked list of objects
	if (headObj == nullptr)
	{
		headObj = newObj;
		tailObj = newObj;
	}
	else
	{
		tailObj-> next = newObj;
		tailObj = newObj;
	}
	if (newObj->objID == WIREtype) // if object is wire
	{
		selectedWire = static_cast<Wire*>(newObj);
		return;
	}
	selectedObject = newObj;
}

void Simulator::deleteObject()
{
	if (headObj == nullptr)
	{
		cout << "No objects to delete" << endl;
	}
	else if (headObj->selected) // delete head
	{
		cout << "Deleting head" << endl;
		headObj = headObj->next;
		delete selectedObject;
		selectedObject = nullptr;
	}
	else if (tailObj->selected) // delete tail
	{
		cout << "Deleting tail" << endl;
		Object* temp = headObj;
		while (temp->next != tailObj)
		{
			temp = temp->next;
		}
		temp->next = nullptr;
		delete tailObj;
		tailObj = temp;
		selectedObject = nullptr;
	}
	else // delete middle 
	{
		cout << "Deleting middle" << endl;
		Object* temp = headObj;
		while (temp->next != nullptr)
		{
			if (temp->next->selected)
			{
				temp->next = temp->next->next;
				delete selectedObject;
				selectedObject = nullptr;
			}
			temp = temp->next;

		}
	}
		 
}

Object* Simulator::getTop()
{
	return headObj;
}
Object* Simulator::getSelectedObject() 
{
	return selectedObject;
}

Wire* Simulator::getSelectedWire() 
{
	return selectedWire;
}

void Simulator::setSelectedWire(Wire* newSelected)
{
	selectedWire = newSelected;
}

void Simulator::setSelectedObject(Object* newSelected) 
{
	selectedObject = newSelected;
}
Object* Simulator::GetObjectOnClick(float x, float y)
{
	Object* temp = headObj;
	while (temp != nullptr)
	{
		
		if (temp->sprite.getGlobalBounds().contains(x, y))
			return temp;
		
		temp = temp->next;
	}
	return nullptr;
	
}

Pin* Simulator::getPinOnClick(LogicElement* obj, float x, float y)
{ 
	// return pin by object type
	switch (obj->getObjType())
	{
		case AND:
		case OR:
		case XOR:
			if (x > (obj->sprite.getPosition().x + 20)) // if on right half
			{
				cout << "Out" << endl;
				return &obj->pins[2];
			}
			else if (x < (obj->sprite.getPosition().x - 20)) // if on left half
			{
				if (y > obj->sprite.getPosition().y) // if on bottom half
				{
					cout << "In1" << endl;
					return &obj->pins[1];
				}
				else {
					cout << "In2" << endl;
					return &obj->pins[0];
				}
			}
			break;
		case Logic1:
			if (y > (obj->sprite.getPosition().y)) // if on bottom half
			{
				cout << "VddOut" << endl;
				return &obj->pins[0];
			}
			
			break;
		case Logic0:
			if (y < (obj->sprite.getPosition().y)) // if on top half
			{
				cout << "GNDin" << endl;
				return &obj->pins[0];
			}
			break;
		case LEDtype:
			if (y > obj->sprite.getPosition().y)
			{
				if ( x > obj->sprite.getPosition().x)
				{
					cout << "LEDOut" << endl;
					return &obj->pins[1];
				}
				else
				{
					cout << "LEDIn" << endl;
					return &obj->pins[0];
				}
			}
			break;
		case NOT:
			if (x > (obj->sprite.getPosition().x + 20)) // if on right half
			{
				cout << "Out" << endl;
				return &obj->pins[1];
			}
			else if (x < (obj->sprite.getPosition().x - 20)) // if on left half
			{
				cout << "In" << endl;
				return &obj->pins[0];
			}
			break;
		case CLOCK:
			if (x > (obj->sprite.getPosition().x + 20)) // if on right half
			{
				cout << "Out" << endl;
				return &obj->pins[0];
			}
			break;
		case DFF:
			if (x > (obj->sprite.getPosition().x + 20)) // if on right half
			{
				if (y > obj->sprite.getPosition().y) {
					cout << "Q1_" << endl;
					return &obj->pins[3];
				}
				else {
					cout << "Q1" << endl;
					return &obj->pins[2];
				}
				
			}
			else if (x < (obj->sprite.getPosition().x - 20)) // if on left half
			{
				if (y > obj->sprite.getPosition().y) // if on bottom half
				{
					cout << "Clock" << endl;
					return &obj->pins[1];
				}
				else {
					cout << "D" << endl;
					return &obj->pins[0];
				}
			}

		
			
		
	}
	//if (x > (obj->sprite.getPosition().x + 20)) // if on right half
	//{
	//	cout << "Right" << endl;
	//	return &obj->pins[2];
	//}
	//else if (x < (obj->sprite.getPosition().x - 20)) // if on left half
	//{
	//	if (y > obj->sprite.getPosition().y) // if on bottom half
	//	{
	//		cout << "Bottom" << endl;
	//		return &obj->pins[1];
	//	}
	//	else {
	//		cout << "Top" << endl;
	//		return &obj->pins[0];
	//	}
	//}
	return nullptr;
}

void Simulator::createWire(Pin*, float, float) 
{
	
	
}

void Simulator::unselectAll()
{

	Object* temp = headObj;
	while (temp != nullptr)
	{
		temp->selected = false;
		temp = temp->next;
	}
	selectedObject = nullptr;
	selectedWire = nullptr;
}
void Simulator::deletePicked()
{
	/*if (selected == nullptr) return;
	
	selected->
	Object* temp = headObj;
	while (temp->next != nullptr)
	{		
		if (temp->next->selected = true)
		{
			
			if (temp->next->next == nullptr)
			{
				cout << "Deleting1" << endl;
				temp->next = nullptr;
				break;
			}
			else
			{
				cout << "Deleting" << endl;
				temp->next = temp->next->next;
				break;
			}
		}
			
		temp = temp->next;
	}*/
}

Object* Simulator::createObjectbyType(objType type, float x, float y)
{
	
	switch (type)
	{
	case AND:
		return new AndGate(window, x, y);
		break;
	case OR:
		return new OrGate(window, x, y);
		break;
	case NOT:
		return new NotGate(window, x, y);
		break;
	case XOR:
		return new XorGate(window, x, y);
		break;
	case DFF:
		return new DffGate(window, x, y);
		break;
	case CLOCK:
		return new Clock(window, x, y);
		break;
	case Logic1:
		return new Logic_1(window, x, y);
		break;
	case Logic0:
		return new Logic_0(window, x, y);
		break;
	case LEDtype:
		return new LED(window, x, y);
		break;
	/*default:
		return nullptr;
		break;*/
	}
}
