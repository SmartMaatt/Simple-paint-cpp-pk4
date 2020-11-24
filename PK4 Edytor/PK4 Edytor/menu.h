#pragma once
#ifndef menuh
#define menuh

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

//Klasa pojedynczego przycisku interface'u
class Button {

private:
	sf::RectangleShape button;		//Zmienne kształtu prostokątu biblioteki SFML
	sf::RectangleShape menuImage;	//Kolejno styl i wielkość przycisku oraz tekstura

	int btnWidth;		//Szerokość
	int btnHeight;		//Wysokość
	bool active;		//Czy aktywny
	bool hovered;		//Czy zaznaczony kursorem

public:
	void setBackColor(sf::Color color);					//Ustalanie koloru tła
	void setPosition(sf::Vector2f point, int frame);	//Ustalanie pozycji
	void setActive(bool what);							//Ustalanie aktywności
	void setHovered(bool what);							//Ustalanie podświetnienia
	void changeTexture(int which);						//Zmiana tekstury (ograniczona ze względu na wykorzystanie w jednym przypadku)
	void drawTo(sf::RenderWindow& window);				//Narysuj przycisk na ekran
	bool isMouseOver(sf::RenderWindow& window);			//Zwraca prawdę gdy kursor znajduje się na przycisku

	Button(sf::Vector2f buttonSize, sf::Vector2f buttonPosition, float frame, sf::Color BgColor, sf::Texture* menuTexture, int BtnNo, int TextureRow);
};


//Klasa konstrolująca interface
class Gui {

private:
	std::vector<std::vector<Button>> GuiVector;		//Wektor wektorów przechowujący wszystkie dostępne przyciski
	sf::RectangleShape menuBg;						//Tło menu
	sf::Text lineText;								//Tekst grubości linii
	sf::Text fillText;								//Tekst wypełnienia kształtu

public:
	void drawGui(sf::RenderWindow& window);		//Rysowanie całego Gui

	//Konstruktor rzędu przyciskow powiązanych ze sobą (narzędzie/kolor)
	void makeMenu(std::vector<Button>* menuButtonRow, sf::Vector2f buttonSize, 	
	sf::Vector2f buttonPosition, float frame, sf::Color BgColor, sf::Texture* menuTexture, int BtnAm, int row);

	void menuReact(sf::RenderWindow& window, int row);		//Podświetlenie przycisku po najechaniu
	bool menuClick(sf::RenderWindow& window, int row);		//Reakcja na klikniecie dla pojedynczych przyciskow
	int menuListClick(sf::RenderWindow& window, int row);	//Reakcja na klinięcie dla list przycisków
	void changeText(int which, int value);					//Zmiana tesktów w gui

	/*PRZECIĄŻONY OPERATOR*/
	operator int();

	Gui(sf::RenderWindow& window, sf::Texture* menuTexture, sf::Font* font);

};




#endif