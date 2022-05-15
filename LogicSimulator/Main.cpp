/* Create logic gate simulator using SFML library
    
*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Object.h"
#include "Wire.h"
#include "Pin.h"
#include "LogicElement.h"
#include "AndGate.h"
#include "Simulator.h"
#include "Palette.h"
using namespace std;

int main()
{    
    /*sf::Sprite sprite;
    sf::Sprite sprite2;
    sprite.setTexture(texture);
    sprite.setPosition(200, 200);
    sprite2.setTexture(texture);
    sprite.setOrigin(49.0f, 30.0f);
    sprite2.setOrigin(49.0f, 30.0f);*/
	
    sf::Font font;
    font.loadFromFile("../assets/font.ttf");
    sf::Text FPS;
	FPS.setFont(font);
	FPS.setCharacterSize(20);
	FPS.setFillColor(sf::Color::White);
	FPS.setPosition(10, 10);

	// create background for command palette
    sf::RectangleShape background;
    background.setSize(sf::Vector2f(150, 1000));
    background.setFillColor(sf::Color::Magenta);
    background.setPosition(0, 0);
	
    // create the window
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Logic Simulator");
	window.setFramerateLimit(144);
    sf::Clock clock;
    Palette palette(&window);
    
	
	
	// create simulator class and pass window
    Simulator simulator(&window);
	
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);		

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
			
            // create a dummy pointer to use
            Object* dummy = nullptr;
            Wire* dummyWire = nullptr;
			
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if (mousePos.x < 150) // if mouse is in item palette
                    {
                        // create new AndGate object
						AndGate* andGate = new AndGate(&window , mousePos.x, mousePos.y);
						
                        dummy = andGate;
						
						// add object to simulator
						simulator.addObject(andGate);
                    }
                    // look if clicked on existing object
                    else if (simulator.GetObjectOnClick(mousePos.x, mousePos.y) != nullptr)
                    {
					    dummy = simulator.GetObjectOnClick(mousePos.x, mousePos.y);
						cout << "mouse " << mousePos.x << " " << mousePos.y << endl;
						
						// if clicked on pin of object, add wire to simulator
						Pin* dummyPin = simulator.getPinOnClick(static_cast<LogicElement*>(dummy), mousePos.x, mousePos.y);
                        
                        if (dummyPin != nullptr)
                        {
							Wire* wire = new Wire(mousePos.x, mousePos.y, &window, dummyPin);
							dummyWire = wire;
							simulator.addObject(wire);
							
						}
                        else
                            simulator.GetObjectOnClick(mousePos.x, mousePos.y)->selected = true;
                    }
                    else
                    {
                        simulator.unselectAll();
                    }
                }
                
            }
			
			
            if (event.type == sf::Event::MouseMoved)
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
					if (!(simulator.getSelectedWire() == nullptr))
					{
						dummyWire->setEndofWire(nullptr, mousePos.x, mousePos.y);
					}
                    else if (!(simulator.getSelectedObject() == nullptr))
                    {
                        dummy = simulator.getSelectedObject();
                        dummy->sprite.setPosition(mousePos.x, mousePos.y);
                    }
                }
            }
			
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (mousePos.x > 150) // if mouse is not in command palette
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (!(simulator.getSelectedObject() == nullptr))
                        {
                            dummy = simulator.getSelectedObject();
                            simulator.deleteObject();
                            simulator.setSelected(nullptr);

                        }
                    }
                }
                else
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (!(simulator.getSelectedObject() == nullptr))
                        {
                            simulator.getSelectedObject()->selected = 1;
                            simulator.deleteObject();

                        }
                    }
					
                }
            }
            // KeyPressed is not working
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Delete)
                {
                    cout << "Deleting2" << endl;
                    simulator.deleteObject();
                }
            }
            
        }
		
        // draw palette and objects
        window.clear(sf::Color::Black);
        window.draw(background);
        drawPalette(&window, palette.getTop());
        drawPalette(&window, simulator.getTop());
		

		// calculate fps
        sf::Time time = clock.getElapsedTime();
        FPS.setString(to_string(1.0f/time.asSeconds()));
		clock.restart().asSeconds();
        window.draw(FPS);
        // end the current frame
        window.display();
    }
    return 0;
}