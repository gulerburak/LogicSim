#include <iostream>
#include <SFML/Graphics.hpp>
#include "Object.h"
#include "Wire.h"
#include "Pin.h"
#include "LogicElement.h"
#include "AndGate.h"
#include "Simulator.h"
using namespace std;

int main()
{
    sf::Texture texture;
    if (!texture.loadFromFile("../assets/AND.png"))
    {
        cout << "Failed to load texture!" << endl;
        return -1;
    }

    sf::Sprite sprite;
    sf::Sprite sprite2;
    sprite.setTexture(texture);
    sprite.setPosition(200, 200);
    sprite2.setTexture(texture);
    sprite.setOrigin(49.0f, 30.0f);
    sprite2.setOrigin(49.0f, 30.0f);

    // create the window
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Logic Simulator");
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                // "close requested" event: we close the window
                case sf::Event::Closed:
                    window.close();
                    break;
            }
            
        }
		
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sprite.setPosition((float)mousePos.x, static_cast<float>(mousePos.y));
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sprite2.setPosition((float)mousePos.x, static_cast<float>(mousePos.y));
        }

        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(sprite);
        window.draw(sprite2);
		
        // end the current frame
        window.display();
    }
#burak
    return 0;
}