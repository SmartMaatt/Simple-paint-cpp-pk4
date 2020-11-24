#include <SFML/Graphics.hpp>
#include <iostream>

#include "menu.h"
#include "classes.h"
#include "canvas.h"


//Rysowanie obszaru roboczego
void canvas::drawTo(sf::RenderWindow& window) {
	window.draw(field);
}

//Zwraca prawdę gdy mysz znajduje się w obszarze roboczym
bool canvas::isMouseOver(sf::RenderWindow& window) {
	int mouseX = sf::Mouse::getPosition(window).x;
	int mouseY = sf::Mouse::getPosition(window).y;

	int fieldPosX = field.getPosition().x;
	int fieldPosY = field.getPosition().y;

	int fieldxPosWidth = field.getPosition().x + fieldWidth;
	int fieldyPosHeight = field.getPosition().y + fieldHeight;

	if (mouseX < fieldxPosWidth && mouseX > fieldPosX&& mouseY < fieldyPosHeight && mouseY > fieldPosY) {
		return true;
	}
	return false;
}

//Konstruktor obszatu roboczego
canvas::canvas() {
	field.setSize({ 1280,720 - 54 });
	field.setPosition({ 0,54 });
	field.setFillColor(sf::Color::White);

	fieldWidth = 1280;
	fieldHeight = 720 - 54;
}