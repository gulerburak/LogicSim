#pragma once
#include "Object.h"
#include <SFML/Graphics.hpp>
using namespace std;

class Simulator
{
	// create start and stop button
	sf::RectangleShape startButton;
	sf::RectangleShape stopButton;
	Object* selected;
	Object* topObj;
	// add text to buttons
	
public:
	sf::RenderWindow* window; //Pointer to SFML render window
	Simulator(sf::RenderWindow*);
	~Simulator();
	void addObject(Object*);
	void Simulate();
	Object* getTop();
	Object* getSelected();
	void setSelected(Object* );
	Object* GetObjectOnClick(float, float);
	void unselectAll();
	void deletePicked();
	
};

Simulator::Simulator(sf::RenderWindow* window)
{
	this->window = window;
	topObj = nullptr;
	selected = nullptr;
}

Simulator::~Simulator()
{
	delete window, topObj;
}

void Simulator::addObject(Object* newObj)
{
	cout << "Adding element" << endl;
	// create a linked list of objects
	if (topObj == nullptr)
	{
		topObj = newObj;
	}
	else
	{
		Object* temp = topObj;
		while (temp->next != nullptr)
		{
			temp = temp->next;
		}
		temp->next = newObj;
	}
	selected = newObj;
	
}

Object* Simulator::getTop()
{
	return topObj;
}
Object* Simulator::getSelected() 
{
	return selected;
}
void Simulator::setSelected(Object* newSelected) 
{
	selected = newSelected;
}
Object* Simulator::GetObjectOnClick(float x, float y)
{
	Object* temp = topObj;
	while (temp != nullptr)
	{
		
		if (temp->sprite.getGlobalBounds().contains(x, y))
			return temp;
		
		temp = temp->next;
	}
	return nullptr;
	
}
void Simulator::unselectAll()
{

	Object* temp = topObj;
	while (temp != nullptr)
	{
		temp->selected = false;
		temp = temp->next;
	}
}
void Simulator::deletePicked()
{
	Object* temp = topObj;
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
	}
}