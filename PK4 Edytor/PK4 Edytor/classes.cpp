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


/* Shape */
// Choose shape color
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
		// Orange
		return sf::Color(255, 129, 18);
		break;
	case 7:
		return sf::Color::Magenta;
		break;
	case 8:
		// Celadon
		return sf::Color(69, 214, 195);
		break;
	case 9:
		// Grey
		return sf::Color(219, 219, 219);
		break;
	}
}

// Determining shape coordinates
void Shape::setPoints(float points[4]) {
	X1 = points[0];
	Y1 = points[1];
	X2 = points[2];
	Y2 = points[3];
}

// Determining shape color
void Shape::setColor(sf::Color color) {
	(*shapeSrc).setFillColor(color);
}

// Determining the thickness of outline
void Shape::setOutline(sf::Color color, int data) {
	(*shapeSrc).setOutlineColor(color);
	(*shapeSrc).setOutlineThickness(data * 2 + 3);
}

// Determining filling
void Shape::setFilling(int data) {
	if (data == 1)
		fill = true;
	else {
		fill = false;
		(*shapeSrc).setFillColor(sf::Color::Transparent);
	}
}

// Determining shape position
void Shape::setPosition(float x, float y) {
	(*shapeSrc).setPosition({ x, y });
}

// Determining shape on screen
void Shape::draw(sf::RenderWindow& window) {
	window.draw(*shapeSrc);
}



/* Line */
// Determining origin coordinates
void Line::setOrigin(float x, float y) {
	lineShape.setOrigin({ x,y });
}

// Determining line size
void Line::setSize(float a, float b) {
	lineShape.setSize({ a,b });
}

// Determining line angle
void Line::setAngle() {
	lineShape.rotate(angle);
}

// Line calculations
void Line::specialCalc() {
	length = sqrt(abs(pow(Y2 - Y1, 2)) + abs(pow(X2 - X1, 2)));
	angle = atan2(Y2 - Y1, X2 - X1) * (180 / 3.14);
}

// Writing out information about an object to consoles
void Line::showInfo(int click[4]) {
	std::cout << "Length: " << length << std::endl;
	if (angle < 0)
		std::cout << "Angle: " << abs(angle) + 180 << std::endl;
	else
		std::cout << "Angle: " << angle << std::endl;

	std::cout << "Color number: " << click[1] + 1 << std::endl;
	std::cout << "Line thickness: " << click[2] + 1 << std::endl << std::endl;
}

// Line constructor
Line::Line(int click[4], float points[4]) {

	shapeSrc = &lineShape;

	setPoints(points);
	specialCalc();
	setColor(chooseColor(click[1]));

	setOrigin(0, (float)(click[2] + 2));
	setSize(length, (float)(click[2] * 2 + 3));

	setPosition(X1, Y1);
	setAngle();
}




/* Rectangle */
// Determining rectangle size
void Rectangle::setSize(float a, float b) {
	rectShape.setSize({ a,b });
}

// Determining origin coordinates
void Rectangle::setOrigin() {
	if (X1 > X2 && Y1 > Y2) {
		rectShape.setOrigin({ a,b });
	}
	else if (X1 > X2 && Y1 < Y2) {
		rectShape.setOrigin({ a,0 });
	}
	else if (X1 < X2 && Y1 > Y2) {
		rectShape.setOrigin({ 0,b });
	}
}

// Rectangle calculations
void Rectangle::specialCalc() {
	a = abs(X2 - X1);
	b = abs(Y2 - Y1);
	area = a * b;
}

// Writing out information about an object to consoles
void Rectangle::showInfo(int click[4]) {
	std::cout << "Area: " << area << std::endl;
	std::cout << "Lengths a: " << a << " b: " << b << std::endl;
	std::cout << "Color number: " << click[1] + 1 << std::endl;
	std::cout << "Line thickness: " << click[2] + 1 << std::endl;
	std::cout << "Filling: " << fill << std::endl << std::endl;
}

// Rectangle constructor
Rectangle::Rectangle(int click[4], float points[4]) {

	shapeSrc = &rectShape;

	setPoints(points);
	specialCalc();
	setOrigin();

	setColor(chooseColor(click[1]));
	setOutline(rectShape.getFillColor(), click[2]);

	setFilling(click[3]);

	setPosition(X1, Y1);
	setSize(a, b);
}



/* Square */
// Determining origin coordinates
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

// Writing out information about an object to consoles
void Square::showInfo(int click[4]) {
	std::cout << "Pole: " << area << std::endl;
	if (a > b)
		std::cout << "Side length: " << b << std::endl;
	else
		std::cout << "Side length: " << a << std::endl;

	std::cout << "Color number: " << click[1] + 1 << std::endl;
	std::cout << "Line thickness: " << click[2] + 1 << std::endl;
	std::cout << "Filling: " << fill << std::endl << std::endl;
}

// Square constructor
Square::Square(int click[4], float points[4]) : Rectangle(click, points) {

	if (a > b) {
		setSize(b, b);
		area = b * b;
	}
	else {
		setSize(a, a);
		area = a * a;
	}

	setOrigin();
}




/* Ellipse */
// Determining ellipse size
void Ellipse::setSize(float a, float b) {
	circleShape.setRadius(shortR);
	if (X1 < X2 && Y1 < Y2) {
		circleShape.setScale(a / b, b / a);
	}
	else if (X1 > X2 && Y1 > Y2) {
		circleShape.setScale(-(a / b), -(b / a));
	}
	else if (X1 > X2 && Y1 < Y2) {
		circleShape.setScale(-(a / b), b / a);
	}
	else if (X1 < X2 && Y1 > Y2) {
		circleShape.setScale(a / b, -(b / a));
	}
}

// Ellipse calculations
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
	area = 3.14 * a * b;
}

// Writing out information about an object to consoles
void Ellipse::showInfo(int click[4]) {
	std::cout << "Area: " << area << std::endl;
	std::cout << "Lengths r1: " << shortR << " r: " << longR << std::endl;
	std::cout << "Color number: " << click[1] + 1 << std::endl;
	std::cout << "Line thickness: " << click[2] + 1 << std::endl;
	std::cout << "Filling: " << fill << std::endl << std::endl;
}

// Ellipse constructor
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



/* Circle */
// Rotate and improve the shape relative to the ellipse
void Circle::rotate() {
	if (X1 > X2 && Y1 > Y2) {
		circleShape.rotate(180);
	}
	else if (X1 > X2 && Y1 < Y2) {
		circleShape.rotate(90);
	}
	else if (X1 < X2 && Y1 > Y2) {
		circleShape.rotate(270);
	}
}

// Writing out information about an object to consoles
void Circle::showInfo(int click[4]) {
	std::cout << "Area: " << area << std::endl;
	std::cout << "Lengths r: " << longR << std::endl;
	std::cout << "Color number: " << click[1] + 1 << std::endl;
	std::cout << "Line thickness: " << click[2] + 1 << std::endl;
	std::cout << "Filling: " << fill << std::endl << std::endl;
}

// Circle constructor
Circle::Circle(int click[4], float points[4]) : Ellipse(click, points) {
	circleShape.setScale(1, 1);
	longR = shortR;
	area = shortR * shortR * 3, 14;
	rotate();
}



/* Triangle */
// Determining triangle size
void Triangle::setSize(float a, float b) {

	triangleShape.setPointCount(3);
	triangleShape.setPoint(0, sf::Vector2f(X1, Y1));
	triangleShape.setPoint(1, sf::Vector2f(X2, Y2));

	if ((X1 > X2 && Y1 < Y2) || (X1 > X2 && Y1 > Y2)) {
		X3 = X2 + (abs(X1 - X2) * 2);
		triangleShape.setPoint(2, sf::Vector2f(X3, Y2));
	}
	else if ((X1 < X2 && Y1 > Y2) || (X1 < X2 && Y1 < Y2)) {
		X3 = X2 - (abs(X1 - X2) * 2);
		triangleShape.setPoint(2, sf::Vector2f(X3, Y2));
	}
}

// Triangle calculations
void Triangle::specialCalc() {
	height = abs(Y2 - Y1);
	base = abs(X2 - X3);
	area = (height * base) / 2;
}

// Writing out information about an object to consoles
void Triangle::showInfo(int click[4]) {
	std::cout << "Area: " << area << std::endl;
	std::cout << "Height: " << height << std::endl;
	std::cout << "Base length: " << base << std::endl;
	std::cout << "Color number: " << click[1] + 1 << std::endl;
	std::cout << "Line thickness: " << click[2] + 1 << std::endl;
	std::cout << "Filling: " << fill << std::endl << std::endl;
}

// Triangle constructor
Triangle::Triangle(int click[4], float points[4]) {

	shapeSrc = &triangleShape;
	setPoints(points);
	setSize(a, b);
	specialCalc();

	setColor(chooseColor(click[1]));
	setOutline(triangleShape.getFillColor(), click[2]);

	setFilling(click[3]);

}



/* List management functions */
// Displaying shape description using RTTI
void showInfo(GraphicalObject* ptr, int click[4]) {

	std::cout << "/* Drawn ";

	if (typeid(*ptr) == typeid(Line))
		std::cout << "Line";
	else if (typeid(*ptr) == typeid(Rectangle))
		std::cout << "Rectangle";
	else if (typeid(*ptr) == typeid(Square))
		std::cout << "Square";
	else if (typeid(*ptr) == typeid(Ellipse))
		std::cout << "Ellipse";
	else if (typeid(*ptr) == typeid(Circle))
		std::cout << "Circle";
	else if (typeid(*ptr) == typeid(Triangle))
		std::cout << "Triangle";
	else
		std::cout << "Unknown object";

	std::cout << "! */" << std::endl;
	ptr->showInfo(click);
}

// Adding an item to list
void addElement(ListManager*& pHead, int click[4], float points[4], bool info) {

	GraphicalObject* p = nullptr;

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

	ListManager* tmp = new ListManager{ p, nullptr };
	for (int i = 0; i < 4; i++) {
		tmp->click[i] = click[i];
		tmp->points[i] = points[i];
	}

	if (pHead) {
		ListManager* tmpHead = pHead;
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

// Drawing list
void drawList(ListManager* pHead, sf::RenderWindow& window) {
	if (pHead) {
		pHead->p->draw(window);
		drawList(pHead->pNext, window);
	}
}

// Deleting list
template <class T>
void deleteList(T*& pHead) {
	if (std::is_same<T, ListManager>::value)
	{
		if (pHead) {
			deleteList(pHead->pNext);
			delete pHead;
		}
	}
}

// Deleting the last item in the list
void deleteLast(ListManager*& pHead) {
	if (pHead && pHead->pNext) {
		ListManager* tmpPrev = pHead;
		ListManager* tmpHead = pHead->pNext;

		while (tmpHead->pNext) {
			tmpPrev = tmpHead;
			tmpHead = tmpHead->pNext;
		}
		tmpPrev->pNext = nullptr;
		delete tmpHead;
	}
	else if (pHead)
	{
		delete pHead;
		pHead = nullptr;
	}
}

// Display a preview of the unaccepted shape on the window
void virtualShape(int click[4], float points[4], sf::RenderWindow& window) {

	ListManager* pHead = nullptr;
	float temp[4] = { points[0], points[1], sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y };

	addElement(pHead, click, temp, false);
	drawList(pHead, window);
	deleteList(pHead);
}



/* Write and read functions */
// Writing shape information to the selected file
void writeToFile(ListManager* pHead, std::string adress)
{
	std::ofstream fileIn(adress, std::ios::out);

	while (pHead) {
		ListManager* w = pHead;

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
	std::cout << "File " << adress << " was created successfully!" << std::endl;
};

// Reading information about shapes from the selected file
void readFile(ListManager*& pHead, std::string adress) {

	deleteList(pHead);
	pHead = nullptr;

	std::string line;

	try {
		std::ifstream fileOut(adress, std::ios::in);
		if (fileOut) {
			while (getline(fileOut, line)) {
				if (!(splitWords(pHead, line))) {
					throw "Error in file syntax found " + adress + "Please check the correct coding\n!";
				}
			}
			throw "File " + adress + " was read successfully!\n";
		}
		else throw "File " + adress + " does not exist!\n";
		fileOut.close();
	}
	catch (std::string text) {
		std::cout << text;
	}
	catch (...) {
		std::cout << "Default read file exception!" << std::endl;
	}
};


// Division of coded information into subproblems
bool splitWords(ListManager*& pHead, std::string line) {

	std::istringstream test(line);
	std::istringstream str(line);

	int click[4] = { 0,0,0,0 };
	float points[4] = { 0,0,0,0 };
	int length = 0;

	while (test) {
		std::string tmp;
		test >> tmp;
		length++;
	};

	if (length != 15) {
		std::cout << "Too little or too much information was found in the file being opened!" << std::endl;
		return false;
	}

	std::string tmp;
	str >> tmp;
	if (tmp != "{\"shape\":") { return false; }

	str >> tmp;
	if (tmp.length() == 2 && tmp[1] == ',' && (int)tmp[0] - 48 < 6) { click[0] = (int)(tmp[0]) - 48; }
	else { return false; }

	str >> tmp;
	if (tmp != "\"color\":") { return false; }

	str >> tmp;
	if (tmp.length() == 2 && tmp[1] == ',' && (int)tmp[0] - 48 < 10) { click[1] = (int)(tmp[0]) - 48; }
	else { return false; }

	str >> tmp;
	if (tmp != "\"thickness\":") { return false; }

	str >> tmp;
	if (tmp.length() == 2 && tmp[1] == ',' && (int)tmp[0] - 48 < 5) { click[2] = (int)(tmp[0]) - 48; }
	else { return false; }

	str >> tmp;
	if (tmp != "\"fill\":") { return false; }

	str >> tmp;
	if (tmp.length() == 2 && tmp[1] == ',' && (int)tmp[0] - 48 < 2) { click[3] = (int)(tmp[0]) - 48; }
	else { return false; }

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