#pragma once
enum objType { AND, OR, XOR, NOT, WIREtype, LEDtype, Logic0, Logic1, DFF, CLOCK, BUTTON };

class Object
{
protected:
	objType objID;
public:
	friend class Simulator;
	Object* next; // Pointer to next object in the list
	sf::RenderWindow* window; // Pointer to SFML render window
	/*
	* SFML texture list for the object(if any).
	* Some object such as LED element may have multiple textures(for on state and off state),
	* hence this is a list
	*/
	sf::Texture textures[2];

	sf::Sprite sprite; // SFML sprite for the object (if any)
	/*
	* State of the logic element (may be used to designate button state
	* D - flipflop state or whether LED is on or off)
	*/
	bool state; 
	bool selected; //Whether the object is selected for deletion 
	virtual void drawObject(sf::RenderWindow*) = 0; // abstract function to draw the object
	objType getObjType(); // Returns the object type
};

objType Object::getObjType()
{
return objID;
}
