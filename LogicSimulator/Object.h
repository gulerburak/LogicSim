#pragma once
enum objType { AND, OR, XOR };

class Object 
{
protected:
	
public:
	objType objID;
	Object* next; //Pointer to next object in the list
	bool locked; //Whether the object can move on screen or is fixed
	//You can use this flag for toolbar items which cannot move
	sf::RenderWindow* window; //Pointer to SFML render window
	sf::Texture textures[2]; //SFML texture list for the object (if any). 
	//Some object such as LED element may have multiple textures(for on stateand off state), hence this is a list
	
	sf::Sprite sprite; //SFML sprite for the object (if any)
	bool state; //State of the logic element (may be used to designate button state; // D - flipflop state or whether LED is on or off)
	bool selected; //Whether the object is selected for deletion 
	virtual void drawObject(sf::RenderWindow*)=0;
};