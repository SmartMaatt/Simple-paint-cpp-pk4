#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <type_traits>

#include "menu.h"
#include "classes.h"
#include "canvas.h"


/*KSZTAŁT*/

//Wybór koloru kształtu
sf::Color Shape::chooseColor(int color) {
	switch (color)
	{
	case 0:
		return sf::Color::White;
		break;
	case 1:
		return sf::Color::Black;
		break;
	case 2:
		return sf::Color::Red;
		break;
	case 3:
		return sf::Color::Blue;
		break;
	case 4:
		return sf::Color::Green;
		break;
	case 5:
		return sf::Color::Yellow;
		break;
	case 6:
		//pomarańcz
		return sf::Color(255, 129, 18);
		break;
	case 7:
		return sf::Color::Magenta;
		break;
	case 8:
		//seledyn
		return sf::Color(69, 214, 195);
		break;
	case 9:
		//szary
		return sf::Color(219, 219, 219);
		break;
	}
}


//Ustalanie współrzędnych kształtu
void Shape::setPoints(float points[4]) {
	X1 = points[0];
	Y1 = points[1];
	X2 = points[2];
	Y2 = points[3];
}


//Ustalanie koloru kształtu
void Shape::setColor(sf::Color color) {
	(*shapeSrc).setFillColor(color);
}


//Ustalanie wypełnienia
void Shape::setOutline(sf::Color color, int data) {
	(*shapeSrc).setOutlineColor(color);
	(*shapeSrc).setOutlineThickness(data * 2 + 3);
}


//Ustalanie grubości obranowania
void Shape::setFilling(int data) {
	if (data == 1)
		fill = true;
	else {
		fill = false;
		(*shapeSrc).setFillColor(sf::Color::Transparent);
	}
}


//Ustalanie pozycji kształtu
void Shape::setPosition(float x, float y) {
	(*shapeSrc).setPosition({ x, y });
}


//Rysowanie obiektu na ekran
void Shape::draw(sf::RenderWindow& window) {
	window.draw(*shapeSrc);
}




/*LINIA*/

//Ustalanie początku układu wpółrzędnych
void Line::setOrigin(float x, float y) {
	lineShape.setOrigin({ x,y });
}


//Ustalanie wielkości kształtu
void Line::setSize(float a, float b) {
	lineShape.setSize({ a,b });
}


//Ustalanie kąta nachylenia linii
void Line::setAngle() {
	lineShape.rotate(angle);
}


//Obliczenia dla linii
void Line::specialCalc() {	
	length = sqrt(abs(pow(Y2 - Y1, 2)) + abs(pow(X2 - X1, 2)));
	angle = atan2(Y2 - Y1, X2 - X1) * (180 / 3.14);
}


//Wypisywanie informacji o obiekcie na konsole
void Line::showInfo(int click[4]) {
	std::cout << "Dlugosc: " << length << std::endl;
	if (angle < 0)
		std::cout << "Kat: " << abs(angle) + 180 << std::endl;
	else
		std::cout << "Kat: " << angle << std::endl;
	std::cout << "Kolor nr: " << click[1] + 1 << std::endl;
	std::cout << "Grubosc linii: " << click[2] + 1 << std::endl << std::endl;
}


//Konstruktor linii
Line::Line(int click[4], float points[4]){

	shapeSrc = &lineShape;

	setPoints(points);
	specialCalc();
	setColor(chooseColor(click[1]));
	
	setOrigin(0, (float)(click[2] + 2));
	setSize(length, (float)(click[2] * 2 + 3));

	setPosition(X1, Y1);
	setAngle();	
}




/*PROSTOKĄT*/

//Ustalanie wielkości kształtu
void Rectangle::setSize(float a, float b) {
	rectShape.setSize({ a,b });
}


//Ustalanie początku układu współrzędnych
void Rectangle::setOrigin() {
	if (X1 > X2&& Y1 > Y2) {
		rectShape.setOrigin({ a,b });
	}
	else if (X1 > X2&& Y1 < Y2) {
		rectShape.setOrigin({ a,0 });
	}
	else if (X1 < X2 && Y1 > Y2) {
		rectShape.setOrigin({ 0,b });
	}
}


//Obliczenia dla prostokąta
void Rectangle::specialCalc() {
	a = abs(X2 - X1);
	b = abs(Y2 - Y1);
	field = a*b;
}


//Wypisywanie informacji o obiekcie na konsole
void Rectangle::showInfo(int click[4]) {
	std::cout << "Pole: " << field << std::endl;
	std::cout << "Dlugosci a: " << a << " b: " << b << std::endl;
	std::cout << "Kolor nr: " << click[1] + 1 << std::endl;
	std::cout << "Grubosc linii: " << click[2] + 1 << std::endl;

	if (fill)
		std::cout << "Wypelnienie: Tak" << std::endl << std::endl;
	else
		std::cout << "Wypelnienie: Nie" << std::endl << std::endl;
}


//Konstruktor prostokąta
Rectangle::Rectangle(int click[4], float points[4]) {

	shapeSrc = &rectShape;

	setPoints(points);
	specialCalc();
	setOrigin();

	setColor(chooseColor(click[1]));
	setOutline(rectShape.getFillColor(), click[2]);
	
	setFilling(click[3]);
	
	setPosition(X1,Y1);
	setSize(a,b);
}



/*KWADRAT*/

//Ustalanie początku układu współrzędnych
void Square::setOrigin() {
	if (X1 > X2 && Y1 > Y2) {
		rectShape.setOrigin({ 0,0 });
		rectShape.rotate(180);
	}
	else if (X1 > X2 && Y1 < Y2) {
		rectShape.setOrigin({ 0,0 });
		rectShape.rotate(90);
	}
	else if (X1 < X2 && Y1 > Y2) {
		rectShape.setOrigin({ 0,0 });
		rectShape.rotate(270);
	}
}


//Wypisywanie informacji o obiekcie na konsole
void Square::showInfo(int click[4]) {
	std::cout << "Pole: " << field << std::endl;
	if(a>b)
		std::cout << "Dlugosc boku: " << b << std::endl;
	else
		std::cout << "Dlugosc boku: " << a << std::endl;
	std::cout << "Kolor nr: " << click[1] + 1 << std::endl;
	std::cout << "Grubosc linii: " << click[2] + 1 << std::endl;

	if (fill)
		std::cout << "Wypelnienie: Tak" << std::endl << std::endl;
	else
		std::cout << "Wypelnienie: Nie" << std::endl << std::endl;
}


//Konstruktor kwadratu
Square::Square(int click[4], float points[4]) : Rectangle(click, points) {

	if (a > b) {
		setSize(b, b);
		field = b * b;
	}
	else {
		setSize(a, a);
		field = a * a;
	}

	setOrigin();
}




/*ELIPSA*/

//Ustalanie wielkości elipsy
void Ellipse::setSize(float a, float b) {
	circleShape.setRadius(shortR);
	if (X1 < X2 && Y1 < Y2) {
		circleShape.setScale(a / b, b / a);
	}
	else if (X1 > X2&& Y1 > Y2) {
		circleShape.setScale(-(a / b), -(b / a));
	}
	else if (X1 > X2&& Y1 < Y2) {
		circleShape.setScale(-(a / b), b / a);
	}
	else if (X1 < X2 && Y1 > Y2) {
		circleShape.setScale(a / b, -(b / a));
	}
}


//Obliczenia dla elipsy
void Ellipse::specialCalc() {
	a = abs(X2 - X1);
	b = abs(Y2 - Y1);

	if (a > b) {
		shortR = b / 2;
		longR = a / 2;
	}
	else {
		shortR = a / 2;
		longR = b / 2;
	}
	field = 3.14 * a * b;
}


//Wypisywanie informacji o obiekcie na konsole
void Ellipse::showInfo(int click[4]) {
	std::cout << "Pole: " << field << std::endl;
	std::cout << "Dlugosci r1: " << shortR << " r: " << longR << std::endl;
	std::cout << "Kolor nr: " << click[1] + 1 << std::endl;
	std::cout << "Grubosc linii: " << click[2] + 1 << std::endl;

	if (fill)
		std::cout << "Wypelnienie: Tak" << std::endl << std::endl;
	else
		std::cout << "Wypelnienie: Nie" << std::endl << std::endl;
}


//Konstruktor elipsy
Ellipse::Ellipse(int click[4], float points[4]) {

	shapeSrc = &circleShape;

	setPoints(points);
	specialCalc();

	setColor(chooseColor(click[1]));
	setOutline(circleShape.getFillColor(), click[2]);

	setFilling(click[3]);

	setPosition(X1, Y1);
	setSize(a, b);
}




/*OKRĄG*/

//Obrót i poprawa kształtu względem elipsy
void Circle::rotate() {
	if (X1 > X2&& Y1 > Y2) {
		circleShape.rotate(180);
	}
	else if (X1 > X2&& Y1 < Y2) {
		circleShape.rotate(90);
	}
	else if (X1 < X2 && Y1 > Y2) {
		circleShape.rotate(270);
	}
}


//Wypisywanie informacji o obiekcie na konsole
void Circle::showInfo(int click[4]) {
	std::cout << "Pole: " << field << std::endl;
	std::cout << "Dlugosci r: " << longR << std::endl;
	std::cout << "Kolor nr: " << click[1] + 1 << std::endl;
	std::cout << "Grubosc linii: " << click[2] + 1 << std::endl;

	if (fill)
		std::cout << "Wypelnienie: Tak" << std::endl << std::endl;
	else
		std::cout << "Wypelnienie: Nie" << std::endl << std::endl;
}


//Konstruktor koła
Circle::Circle(int click[4], float points[4]): Ellipse(click,points) {
	circleShape.setScale(1, 1);
	longR = shortR;
	field = shortR * shortR * 3, 14;
	rotate();
}

/*TRÓJKĄT*/

//Ustawienie wielkości i rozstawienie punktów
void Triangle::setSize(float a, float b) {

	triangleShape.setPointCount(3);
	triangleShape.setPoint(0, sf::Vector2f(X1, Y1));
	triangleShape.setPoint(1, sf::Vector2f(X2, Y2));

	if ((X1 > X2 && Y1 < Y2)||(X1 > X2 && Y1 > Y2)) {
		X3 = X2 + (abs(X1 - X2) * 2);
		triangleShape.setPoint(2, sf::Vector2f(X3, Y2));
	}
	else if ((X1 < X2&& Y1 > Y2)||(X1 < X2&& Y1 < Y2)) {
		X3 = X2 - (abs(X1 - X2) * 2);
		triangleShape.setPoint(2, sf::Vector2f(X3, Y2));
	}
}

//Specjalne obliczenia trójkąta
void Triangle::specialCalc() {
	height = abs(Y2 - Y1);
	footing = abs(X2 - X3);
	field = (height * footing) / 2;
}

//Wypisywanie informacji o obiekcie na konsole
void Triangle::showInfo(int click[4]) {
	std::cout << "Pole: " << field << std::endl;
	std::cout << "Wysokosc: " << height << std::endl;
	std::cout << "Dlugosc podstawy: " << footing << std::endl;
	std::cout << "Kolor nr: " << click[1] + 1 << std::endl;
	std::cout << "Grubosc linii: " << click[2] + 1 << std::endl;

	if (fill)
		std::cout << "Wypelnienie: Tak" << std::endl << std::endl;
	else
		std::cout << "Wypelnienie: Nie" << std::endl << std::endl;
}

//Konstruktor trójkąta
Triangle::Triangle(int click[4], float points[4]) {

	shapeSrc = &triangleShape;
	setPoints(points);
	setSize(a, b);
	specialCalc();

	setColor(chooseColor(click[1]));
	setOutline(triangleShape.getFillColor(), click[2]);

	setFilling(click[3]);

}

/*Funkcje zarządzające listą*/

//Wyświetlanie opisu kształtu z użyciem RTTI
void showInfo(ObiektGraficzny* ptr, int click[4]) {

	std::cout << "/*Narysowano ";

	if (typeid(*ptr) == typeid(Line))
		std::cout << "Linie";
	else if (typeid(*ptr) == typeid(Rectangle))
		std::cout << "Prostokat";
	else if (typeid(*ptr) == typeid(Square))
		std::cout << "Kwadrat";
	else if (typeid(*ptr) == typeid(Ellipse))
		std::cout << "Elipse";
	else if (typeid(*ptr) == typeid(Circle)){
		if (click[3] == 0)
			std::cout << "Okrag";
		else
			std::cout << "Kolo";
	}
	else { std::cout << "Trojkat"; }
	std::cout << "!*/" << std::endl;
	ptr->showInfo(click);
}

//Dodawanie elementu do listy
void addElement(listManage*& pHead, int click[4], float points[4], bool info) {

	ObiektGraficzny* p = nullptr;

	switch (click[0]) {
	case 0:
		p = new Line(click, points);
		break;
	case 1:
		p = new Rectangle(click, points);
		break;
	case 2:
		p = new Square(click, points);
		break;
	case 3:
		p = new Ellipse(click, points);
		break;
	case 4:
		p = new Circle(click, points);
		break;
	case 5:
		p = new Triangle(click, points);
		break;
	}

	listManage* tmp = new listManage{ p, nullptr };
	for (int i = 0; i < 4; i++) {
		tmp->click[i] = click[i];
		tmp->points[i] = points[i];
	}

	if (pHead) {
		listManage* tmpHead = pHead;
		while (tmpHead->pNext) {
			tmpHead = tmpHead->pNext;
		}
		tmpHead->pNext = tmp;
	}
	else {
		pHead = tmp;
	}

	if (info)
		showInfo(p, click);
}


//Rysowanie listy
void drawList(listManage* pHead, sf::RenderWindow& window) {
	if (pHead) {
		pHead->p->draw(window);
		drawList(pHead->pNext, window);
	}
}


//Usuwanie listy
template <class T>
void deleteList(T*& pHead) {
	//Zabezpieczenie na wypadek użycia struktury/klasy o innej budowie
	if (std::is_same<T, listManage>::value)
	{
		if (pHead) {
			deleteList(pHead->pNext);
			delete pHead;
		}
	}
}


//Usuwanie ostatniego elementu listy
void deleteLast(listManage*& pHead) {
	if (pHead) {
		listManage* temp = pHead->pNext;
		delete pHead;
		pHead = temp;
	}
}


//Wyświetlna podgląd na niezaakceptowany kszatałt na okno
void virtualShape(int click[4], float points[4], sf::RenderWindow& window) {

	listManage* pHead=nullptr;
	float temp[4] = { points[0], points[1], sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y };

	addElement(pHead, click, temp, false);
	drawList(pHead, window);
	deleteList(pHead);
}




/*Funkcje zapisu i odczytu*/

//Zapis do wybranego pliku informacji o kształtach
void writeToFile(listManage* pHead, std::string adress) 
{
	std::ofstream fileIn(adress, std::ios::out); 

	while (pHead) {	
		listManage* w = pHead; 

		std::string str = "{\"shape\": ";
		str = str + std::to_string(w->click[0]);

		str = str + ", \"color\": ";
		str = str + std::to_string(w->click[1]);

		str = str + ", \"thickness\": ";
		str = str + std::to_string(w->click[2]);

		str = str + ", \"fill\": ";
		str = str + std::to_string(w->click[3]);

		str = str + ", \"coords\":[ ";
		for (int j = 0; j < 4; j++) {
			str = str + std::to_string(w->points[j]) + ", ";
		}
		str = str + "]},";
		
		fileIn << str << std::endl;	
		pHead = pHead->pNext;	
	};

	fileIn.close();
	std::cout << "Plik " << adress << " zostal utworzony pomyslnie!" << std::endl;
};


//Odczyt z wybranego pliku infoamcji o kształtach
void readFile(listManage*& pHead, std::string adress) {

	deleteList(pHead);
	pHead = nullptr;

	std::string line;

	try {
		std::ifstream fileOut(adress, std::ios::in);
		if (fileOut) {
			while (getline(fileOut, line)) {
				if (!(splitWords(pHead, line))) {
					throw "Odnaleziono blad w skladni pliku " + adress + "\nProsze sprawdzic poprawnosc kodowania!" ;
				}
			}
			throw "Plik " + adress + " zostal odczytany pomyslnie!\n";
		}
		else throw "Plik " + adress + " nie istnieje!\n";
		fileOut.close();
	}
	catch (std::string text) {
		std::cout << text;
	}
	catch (...) {
		std::cout << "Wyjatek domyslny odczytu z pliku!" << std::endl;
	}
};


//Podział zakodowanej informacji na podproblemy
bool splitWords(listManage*& pHead, std::string line) {

	std::istringstream test(line);
	std::istringstream str(line);

	int click[4] = { 0,0,0,0 };
	float points[4] = { 0,0,0,0 };
	int length = 0;

	while(test) {
		std::string tmp;
		test >> tmp;
		length++;
	};

	if (length != 15) {
		std::cout << "W otwieranym pliku znaleziono za malo/duzo informacji!" << std::endl;
		return false;
	}

	std::string tmp;
	str >> tmp;
	if (tmp != "{\"shape\":") { return false; }
	
	str >> tmp;
	if (tmp.length() == 2 && tmp[1] == ',' && (int)tmp[0] - 48 <6) { click[0] = (int)(tmp[0])-48; }
	else{ return false;}

	str >> tmp;
	if (tmp != "\"color\":") { return false; }

	str >> tmp;
	if (tmp.length() == 2 && tmp[1] == ',' && (int)tmp[0] - 48 < 10) { click[1] = (int)(tmp[0])-48; }
	else{ return false; }

	str >> tmp;
	if (tmp != "\"thickness\":") { return false; }

	str >> tmp;
	if (tmp.length() == 2 && tmp[1] == ',' && (int)tmp[0] - 48 < 5) { click[2] = (int)(tmp[0])-48; }
	else{ return false; }

	str >> tmp;
	if (tmp != "\"fill\":") { return false; }

	str >> tmp;
	if (tmp.length() == 2 && tmp[1] == ',' && (int)tmp[0] - 48 < 2) { click[3] = (int)(tmp[0])-48; }
	else{ return false; }

	str >> tmp;
	if (tmp != "\"coords\":[") { return false; }

	for (int i = 0; i < 4; i++) {
		str >> tmp;
		if (tmp[tmp.length() - 1] == ',') {
			tmp.pop_back();
			points[i] = stof(tmp);
		}
		else { return false; }
	}

	str >> tmp;
	if (tmp != "]},") { return false; }
	

	addElement(pHead, click, points, true);
	return true;
}