#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

#include "menu.h"


//Ustalanie koloru tła
void Button::setBackColor(sf::Color color) {
	button.setFillColor(color);
}


//Ustalanie pozycji
void Button::setPosition(sf::Vector2f point, int frame) {
	button.setPosition(point.x + frame, point.y + frame);
	menuImage.setPosition(point.x + frame, point.y + frame);
}


//Ustalanie aktywności
void Button::setActive(bool what) {
	active = what;
}


//Ustalanie podświetnienia
void Button::setHovered(bool what) {
	hovered = what;
}


//Zmiana tekstury (ograniczona ze względu na wykorzystanie w jednym przypadku)
void Button::changeTexture(int which) {
	menuImage.setTextureRect(sf::IntRect(50 * which, 50 * 3, 50, 50));
}


//Narysuj przycisk na ekran
void Button::drawTo(sf::RenderWindow& window) {

	if (active == true || hovered == true)
		button.setFillColor(sf::Color(200, 200, 200));
	else
		button.setFillColor(sf::Color(220, 220, 220));

	window.draw(button);
	window.draw(menuImage);
}


//Zwraca prawdę gdy kursor znajduje się na przycisku
bool Button::isMouseOver(sf::RenderWindow& window) {
	int mouseX = sf::Mouse::getPosition(window).x;
	int mouseY = sf::Mouse::getPosition(window).y;

	int btnPosX = button.getPosition().x;
	int btnPosY = button.getPosition().y;

	int btnxPosWidth = button.getPosition().x + btnWidth;
	int btnyPosHeight = button.getPosition().y + btnHeight;

	if (mouseX < btnxPosWidth && mouseX > btnPosX&& mouseY < btnyPosHeight && mouseY > btnPosY) {
		return true;
	}
	return false;
}


//Konstruktor przycisku
Button::Button(sf::Vector2f buttonSize, sf::Vector2f buttonPosition, float frame, sf::Color BgColor, sf::Texture* menuTexture, int BtnNo, int TextureRow) {

	button.setSize(buttonSize);
	button.setFillColor(BgColor);
	button.setOutlineThickness(frame);
	button.setOutlineColor(sf::Color(180, 180, 180));

	menuImage.setSize(buttonSize);
	menuImage.setTexture(menuTexture);

	menuImage.setTextureRect(sf::IntRect(buttonSize.x * BtnNo, buttonSize.y * TextureRow, buttonSize.x, buttonSize.y));

	setPosition(buttonPosition, frame);

	btnWidth = buttonSize.x;
	btnHeight = buttonSize.y;
	active = false;
}




/*INTERFACE*/

//Rysowanie całego Gui
void Gui::drawGui(sf::RenderWindow& window) {

	window.draw(menuBg);
	window.draw(lineText);
	window.draw(fillText);

	for (int i = 0; i < GuiVector.size(); i++) {
		for (int j = 0; j < GuiVector[i].size(); j++) {
			GuiVector[i][j].drawTo(window);
		}
	}
}


//Konstruktor rzędu przycisków
void Gui::makeMenu(std::vector<Button>* menuButtonRow, sf::Vector2f buttonSize, sf::Vector2f buttonPosition, float frame, sf::Color BgColor, sf::Texture* menuTexture, int BtnAm, int row) {
	for (float i = 0; i < BtnAm; i++)
		(*menuButtonRow).push_back(Button(buttonSize, { (buttonPosition.x + buttonSize.x * i), buttonPosition.y }, frame, BgColor, menuTexture, i, row));
}


//Podświetlenie przycisku po najechaniu
void Gui::menuReact(sf::RenderWindow& window, int row) {
	for (int i = 0; i < GuiVector[row].size(); i++) {
		if (GuiVector[row][i].isMouseOver(window)) {
			GuiVector[row][i].setHovered(true);
		}
		else {
			GuiVector[row][i].setHovered(false);
		}
	}
}


//Reakcja na klikniecie dla pojedynczych przyciskow
bool Gui::menuClick(sf::RenderWindow& window, int row) {
		if (GuiVector[row][0].isMouseOver(window)) 
			return true;
		else return false;
}


//Reakcja na klinięcie dla list przycisków
int Gui::menuListClick(sf::RenderWindow& window, int row) {

	for (int i = 0; i < GuiVector[row].size(); i++)
		if (GuiVector[row][i].isMouseOver(window)) {

			for (int j = 0; j < GuiVector[row].size(); j++)
				GuiVector[row][j].setActive(false);

			GuiVector[row][i].setActive(true);
			return i;
		}
	return -1;
}


//Zmiana tesktów w gui
void Gui::changeText(int which, int value) {

	if (which == 0) {
		lineText.setString("Grubosc linii: " + std::to_string(value + 1));
	}
	else if (which == 1) {
		if (value == 0) {
			fillText.setString("Wypelnienie ksztaltu: Nie");
			GuiVector[3][0].changeTexture(0);
		}
		else if (value == 1) {
			fillText.setString("Wypelnienie ksztaltu: Tak");
			GuiVector[3][0].changeTexture(1);
		}
	}
}


/*PRZECIĄŻONY OPERATOR*/
Gui::operator int() {
	return GuiVector.size();
}


//Konstruktor całego Gui składający wszystkie przyciski w całość
Gui::Gui(sf::RenderWindow& window, sf::Texture* menuTexture, sf::Font* font) {

	std::vector<Button> temp;

	//Tło górnego paska
	menuBg.setFillColor(sf::Color(180, 180, 180));
	menuBg.setSize({ 1280,54 });

	//Teksty informujące o grubości linni i wypełnieniu
	lineText.setString("Grubosc linii: 1");
	lineText.setFont(*font);
	lineText.setCharacterSize(16);
	lineText.setPosition({ 930,4 });
	lineText.setFillColor(sf::Color::Black);

	fillText.setString("Wypelnienie ksztaltu: Nie");
	fillText.setFont(*font);
	fillText.setCharacterSize(16);
	fillText.setPosition({ 930,26 });
	fillText.setFillColor(sf::Color::Black);

	//Przyciski narzędzi
	makeMenu(&temp, { 50,50 }, { 0,0 }, 2, sf::Color(220, 220, 220), menuTexture, 6, 0);
	GuiVector.push_back(temp);
	temp.clear();

	//Przyciski kolorów
	makeMenu(&temp, { 50,50 }, { 310,0 }, 2, sf::Color(220, 220, 220), menuTexture, 10, 1);
	GuiVector.push_back(temp);
	temp.clear();

	//Przycisk zmiany grubości
	makeMenu(&temp, { 50,50 }, { 820,0 }, 2, sf::Color(220, 220, 220), menuTexture, 1, 2);
	GuiVector.push_back(temp);
	temp.clear();

	//Przycisk wypełnienia
	makeMenu(&temp, { 50,50 }, { 870,0 }, 2, sf::Color(220, 220, 220), menuTexture, 1, 3);
	GuiVector.push_back(temp);
	temp.clear();

	//Przycisk Undo
	makeMenu(&temp, { 50,50 }, { 1126,0 }, 2, sf::Color(220, 220, 220), menuTexture, 1, 4);
	GuiVector.push_back(temp);
	temp.clear();

	//Przycisk zapisu
	makeMenu(&temp, { 50,50 }, { 1178,0 }, 2, sf::Color(220, 220, 220), menuTexture, 1, 5);
	GuiVector.push_back(temp);
	temp.clear();

	//Przycisk odczytu
	makeMenu(&temp, { 50,50 }, { 1230,0 }, 2, sf::Color(220, 220, 220), menuTexture, 1, 6);
	GuiVector.push_back(temp);
	temp.clear();

	//Podstawowe wartości
	GuiVector[0][0].setActive(1);
	GuiVector[1][2].setActive(1);
}


