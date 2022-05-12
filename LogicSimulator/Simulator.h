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
	Object* headObj;
	Object* tailObj;
	// add text to buttons
	
public:
	sf::RenderWindow* window; //Pointer to SFML render window
	Simulator(sf::RenderWindow*);
	~Simulator();
	void addObject(Object*);
	void deleteObject();
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
	headObj = nullptr;
	tailObj = nullptr;
	selected = nullptr;
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
	selected = newObj;
	
}

void Simulator::deleteObject()
{
	if (headObj->selected) // delete head
	{
		cout << "Deleting head" << endl;
		headObj = headObj->next;
		delete selected;
		selected = nullptr;
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
		selected = nullptr;
	}
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
	Object* temp = headObj;
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

	Object* temp = headObj;
	while (temp != nullptr)
	{
		temp->selected = false;
		temp = temp->next;
	}
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