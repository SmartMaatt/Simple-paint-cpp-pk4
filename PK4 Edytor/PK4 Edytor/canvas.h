#pragma once
#ifndef canvash
#define canvash
#include <SFML/Graphics.hpp>

//Klasa obszaru roboczego
class canvas {

private:
	sf::RectangleShape field;	//Zmienna kształtu prostokąta biblioteki SFML
	int fieldWidth;				//Szerokość
	int fieldHeight;			//Wysokość

public:
	void drawTo(sf::RenderWindow& window);			//Rysowanie obszaru roboczego
	bool isMouseOver(sf::RenderWindow& window);		//Zwraca prawdę gdy mysz znajduje się w obszarze roboczym
	canvas();										//Domyślny konstruktor
};

#endif