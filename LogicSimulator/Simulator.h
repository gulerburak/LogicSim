#pragma once
#include "Object.h"
#include "Pin.h"
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
	
};

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
	if (newObj->objID == WIREclass) // if object is wire
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
	// add middle deletion
	//else // delete middle 
	//{
	//	cout << "Deleting middle" << endl;
	//	Object* temp = headObj;
	//	while (temp->next->next != nullptr)
	//	{
	//		if (temp->next->selected)
	//		{
	//			temp->next = temp->next->next;
	//			delete temp->next;
	//			selected = nullptr;
	//		}
	//		temp = temp->next;
	//	
	//	}
	//}
		 
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
	if (x > (obj->sprite.getPosition().x + 20)) // if on right half
	{
		cout << "Right" << endl;
		return &obj->pins[2];
	}
	else if (x < (obj->sprite.getPosition().x - 20)) // if on left half
	{
		if (y > obj->sprite.getPosition().y) // if on bottom half
		{
			cout << "Bottom" << endl;
			return &obj->pins[1];
		}
		else {
			cout << "Top" << endl;
			return &obj->pins[0];
		}
	}
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