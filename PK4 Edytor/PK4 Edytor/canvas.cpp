#include <SFML/Graphics.hpp>
#include <iostream>

#include "menu.h"
#include "classes.h"
#include "canvas.h"


// Drawing the workspace
void Canvas::drawTo(sf::RenderWindow& window) {
	window.draw(field);
}

// Returns true when the mouse is in the work area
bool Canvas::isMouseOver(sf::RenderWindow& window) {
	int mouseX = sf::Mouse::getPosition(window).x;
	int mouseY = sf::Mouse::getPosition(window).y;

	int fieldPosX = field.getPosition().x;
	int fieldPosY = field.getPosition().y;

	int fieldxPosWidth = field.getPosition().x + fieldWidth;
	int fieldyPosHeight = field.getPosition().y + fieldHeight;

	if (mouseX < fieldxPosWidth && mouseX > fieldPosX && mouseY < fieldyPosHeight && mouseY > fieldPosY) {
		return true;
	}
	return false;
}

// Canvas constructor
Canvas::Canvas() {
	field.setSize({ 1280,720 - 54 });
	field.setPosition({ 0,54 });
	field.setFillColor(sf::Color::White);

	fieldWidth = 1280;
	fieldHeight = 720 - 54;
}