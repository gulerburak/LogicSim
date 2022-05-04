#pragma once

class Wire: public Object {
	sf::Vertex line[2];
	Pin* pins[2];
};