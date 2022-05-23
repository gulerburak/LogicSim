/* Create logic gate simulator using SFML library
    
*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Object.h"
#include "Wire.h"
#include "Pin.h"
#include "LogicElement.h"
#include "AndGate.h"
#include "OrGate.h"
#include "NotGate.h"
#include "XorGate.h"
#include "Dff.h"
#include "Clock.h"
#include "Simulator.h"
#include "Palette.h"
#include "VDDGND.h"
#include "LED.h"
using namespace std;

static const float view_height = 1024.0f;

void Resize_view(sf::RenderWindow& window, sf::View& view) // resize window
{
    
   float aspect_ratio = float(window.getSize().x) / float(window.getSize().y);
   view.setSize(view_height *aspect_ratio, view_height);
   cout << aspect_ratio << endl;
   //Palette palette(&window,aspect_ratio);
}

int main()
{   
	// create font for text
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

   sf::View view(sf::Vector2f(512.0f, 512.0f), sf::Vector2f(view_height, view_height));

    // create the window
    sf::RenderWindow window(sf::VideoMode(1024, 1024), "Logic Simulator");
	window.setFramerateLimit(144);
    float aspectratio = float(window.getSize().x) / float(window.getSize().y);
    Palette palette(&window);
    
	sf::Clock clock; // create clock  for timer
    float prev = 0;
	// create simulator class and pass window
    Simulator simulator(&window);
    bool isSimulating = 0;
    // run the program as long as the window is open
    while (window.isOpen())
    {
        
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);		

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) 
            {
                // if close button is clicked
                window.close();
            }
            if (event.type == sf::Event::Resized) 
            {
				// if window is resized
                Resize_view(window, view);
            }
            float aspectratio = float(window.getSize().x) / float(window.getSize().y);
            
            // create a dummy pointer to use
            Object* dummyObject = nullptr;
            Wire* dummyWire = nullptr;
			Pin* dummyPin = nullptr;
			
            if (event.type == sf::Event::MouseButtonPressed)
            {
				// unselect all objects
                simulator.unselectAll();
				
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    // if left mouse button is pressed
                {
                    if (mousePos.y > 1 * aspectratio && mousePos.y < 36 * aspectratio) 
                        // if mouse on startstop area
                    {
                        dummyObject = palette.GetObjectOnClick(mousePos.x, mousePos.y);
						if (dummyObject != nullptr) 
						{
							if (dummyObject->getObjType() == BUTTON)
                                // start-stop button is clicked
							{
                                cout << "Button clicked" << endl;
                                // change the state of simulator
								if (isSimulating)
								{
									isSimulating = false;
                                    dummyObject->state = 1;
                                    simulator.resetAllLEDs();
								}
								else
								{
									isSimulating = true;
                                    dummyObject->state = 0;
								}
							}
						}						
                    }
                    else if (mousePos.x > 1 * aspectratio && mousePos.x < 150 * aspectratio) 
                        // if mouse is on item palette
                    {
                        // if any object is clicked create new object by type
                        dummyObject = palette.GetObjectOnClick(mousePos.x, mousePos.y);
						if(dummyObject != nullptr)
						{
                            dummyObject = simulator.createObjectbyType(dummyObject->getObjType(),
                                                                       mousePos.x,
                                                                       mousePos.y);  
                            simulator.addObject(dummyObject);
							
						}
                    }
                    else if (simulator.GetObjectOnClick(mousePos.x, mousePos.y) != nullptr)
                        // look if clicked on existing object
                    {
                        cout << "mouse " << mousePos.x << " " << mousePos.y << endl;
						// assign if it is a created object
					    dummyObject = simulator.GetObjectOnClick(mousePos.x, mousePos.y);
                        simulator.setSelectedObject(dummyObject);
						
						// check if clicked on the pin of the object
						Pin* dummyPin = simulator.getPinOnClick(static_cast<LogicElement*>(dummyObject),
                                                                mousePos.x, mousePos.y);
                        if (dummyPin != nullptr)
                        {
							// create new wire which starts from here
							Wire* wire = new Wire(mousePos.x, mousePos.y, &window, dummyPin);
                            if (dummyPin->addWire(wire))
                                simulator.addObject(wire);
						}
                        else // select clicked object
                            simulator.GetObjectOnClick(mousePos.x, mousePos.y)->selected = true;
                    }
                    else // if clicked empty place, unselect all objects
                    {
                        simulator.unselectAll();
                    }
                }
                
            }
			
			
            if (event.type == sf::Event::MouseMoved)
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
					if (!(simulator.getSelectedWire() == nullptr)) // move wire
					{
						// move but do not save ending pin
                        dummyWire = simulator.getSelectedWire();
						dummyWire->setEndOfWire(nullptr, mousePos.x, mousePos.y);
						
					}
                    else if (!(simulator.getSelectedObject() == nullptr)) // move recently created object
                    {
                        // last moved location is saved
                        dummyObject = simulator.getSelectedObject();
                        dummyObject->sprite.setPosition(mousePos.x, mousePos.y);
                    }
                }
            }
			
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (mousePos.x > 150 * aspectratio && mousePos.y > 36 * aspectratio) // if mouse is not in command palette
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (!(simulator.getSelectedWire() == nullptr))
                            // if wire is drawing
                        {
							dummyWire = simulator.getSelectedWire();
                            if (simulator.GetObjectOnClick(mousePos.x, mousePos.y) != nullptr)
                            {
								// get the object's pin lying on this position
                                dummyObject = simulator.GetObjectOnClick(mousePos.x, mousePos.y);
                                dummyPin = simulator.getPinOnClick(static_cast<LogicElement*>(dummyObject),
                                                                   mousePos.x,
                                                                   mousePos.y);
                                
								
                                if (dummyPin->addWire(dummyWire))
                                    // if max wire limit is not exceeded
                                {
                                    // assing ending pin of the wire
                                    dummyWire->setEndOfWire(dummyPin,
                                                            mousePos.x,
                                                            mousePos.y);
                                    dummyWire->connectPins();
									
                                    dummyWire = nullptr;
                                }
                                else 
                                {
									// delete wire
                                    simulator.getSelectedWire()->getPinPtr(0)->numConnections--;
                                    simulator.getSelectedWire()->selected = 1;
                                    simulator.deleteObject();
                                }
                            }
							else // no object in released area
							{
                                simulator.getSelectedWire()->getPinPtr(0)->numConnections--;
                                simulator.getSelectedWire()->selected = 1;
                                simulator.deleteObject();
                                
                            }
						
                        }
                        else if (!(simulator.getSelectedObject() == nullptr))
                        {
							// select object
                            dummyObject = simulator.getSelectedObject();

                        }
                        simulator.setSelectedObject(nullptr);
                        simulator.setSelectedWire(nullptr);
                    }
                }
                else // if mouse released on tool palette area, delete created objects
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (!(simulator.getSelectedWire() == nullptr))
                        {
							simulator.getSelectedWire()->selected = 1;
							simulator.deleteObject();
                        }
                        else if (!(simulator.getSelectedObject() == nullptr))
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
                    if (simulator.GetObjectOnClick(mousePos.x, mousePos.y) != nullptr) 
                    {
                        if (!(simulator.getSelectedWire() == nullptr)) {
                                
                            dummyWire = simulator.getSelectedWire();
                            cout << "Deleting wire" << endl;
                            simulator.deleteObject();
                        }
                        dummyObject = simulator.GetObjectOnClick(mousePos.x, mousePos.y);
                        simulator.deleteObject();
                    }
                }
            }
        }
        
		
        if (isSimulating) // start button is triggered
        {
			cout << "Simulating" << endl;
			simulator.Simulate(); // run simulation
            sf::Time elapsed = clock.getElapsedTime();
            float seconds = elapsed.asSeconds();
            float aa = prev + seconds;
            prev = aa;
            int ss_int = (int)aa;
            cout << ss_int << endl;
            if (ss_int % 2 == 0) {
                simulator.switchClockTo1();
            }
            else {
                simulator.switchClockTo0();
            }
        }
		
        // draw palette and objects
        window.clear(sf::Color::Color(211, 211, 211, 255));
        window.draw(background);
        drawLinkedObjects(&window, palette.getTop());
        drawLinkedObjects(&window, simulator.getTop());

        window.setView(view);
		

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