#pragma once
#include <SFML/Graphics.hpp>

class Canvas {

private:
	sf::RectangleShape field;	// SFML library rectangle shape variable
	int fieldWidth;
	int fieldHeight;

public:
	void drawTo(sf::RenderWindow& window);			// Drawing the workspace
	bool isMouseOver(sf::RenderWindow& window);		// Returns true when the mouse is in the work area
	Canvas();
};