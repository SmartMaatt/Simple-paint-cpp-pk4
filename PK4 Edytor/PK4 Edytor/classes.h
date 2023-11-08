#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <type_traits>


class GraphicalObject {

public:
	virtual void draw(sf::RenderWindow& window) = 0;	// Drawing object on screen
	virtual void showInfo(int click[4]) = 0;			// Writing out information about an object to console
};



class Shape : public GraphicalObject {

protected:
	float X1, Y1, X2, Y2;	// Coordinates
	sf::Shape* shapeSrc;	// Shape variable from the SFML library
	bool fill;				// Filling flag

public:
	sf::Color chooseColor(int color);			// Choose shape color
	void draw(sf::RenderWindow& window);		// Determining shape on screen

	void setPoints(float points[4]);			// Determining shape coordinates
	void setColor(sf::Color color);				// Determining shape color
	void setOutline(sf::Color color, int data);	// Determining the thickness of outline
	void setFilling(int data);					// Determining filling
	void setPosition(float x, float y);			// Determining shape position

	virtual void setSize(float a, float b) = 0;
	virtual void specialCalc() = 0;
};



class Line : public Shape {

protected:
	sf::RectangleShape lineShape;		// Line shape variable from SFML library
	float length, angle;				// Line parameters

public:
	void setOrigin(float x, float y);	// Determining origin coordinates
	void setSize(float a, float b);		// Determining line size
	void setAngle();					// Determining line angle
	void specialCalc();					// Line calculations
	void showInfo(int click[4]);		// Writing out information about an object to consoles

	Line(int click[4], float points[4]);
};



class Rectangle :public Shape {

protected:
	sf::RectangleShape rectShape;		// Rectangle shape variable from SFML library
	float a, b, area;					// Rectangle parameters

public:
	void setSize(float a, float b);		// Determining rectangle size
	void setOrigin();					// Determining origin coordinates
	void specialCalc();					// Rectangle calculations
	void showInfo(int click[4]);		// Writing out information about an object to consoles

	Rectangle(int click[4], float points[4]);
};



class Square : public Rectangle {

public:
	void setOrigin();				// Determining origin coordinates
	void showInfo(int click[4]);	// Writing out information about an object to consoles

	Square(int click[4], float points[4]);
};



class Ellipse : public Shape {

protected:
	sf::CircleShape circleShape;		// Ellipse shape variable from SFML library
	float a, b, shortR, longR, area;	// Ellipse parameters

public:
	void setSize(float a, float b);		// Determining ellipse size
	void specialCalc();					// Ellipse calculations
	void showInfo(int click[4]);		// Writing out information about an object to consoles

	Ellipse(int click[4], float points[4]);
};



class Circle : public Ellipse {

public:
	void rotate();					// Rotate and improve the shape relative to the ellipse
	void showInfo(int click[4]);	// Writing out information about an object to consoles

	Circle(int click[4], float points[4]);
};



class Triangle : public Shape {

protected:
	sf::ConvexShape triangleShape;			// Convex variable storing the shape
	float a, b, X3, base, area, height;	// Triangle parameters

public:
	void setSize(float a, float b);			// Determining triangle size
	void specialCalc();						// Triangle calculations
	void showInfo(int click[4]);			// Writing out information about an object to consoles

	Triangle(int click[4], float point[4]);
};



/* List management functions */
// Structure storing created shapes and information about them
struct ListManager
{
	GraphicalObject* p;
	ListManager* pNext;
	int click[4];
	float points[4];
};

void showInfo(GraphicalObject* ptr, int click[4]);								// Displaying shape description using RTTI
void addElement(ListManager*& pHead, int click[4], float points[4], bool fake);	// Adding an item to a list
void drawList(ListManager* pHead, sf::RenderWindow& window);					// Drawing a list

template <class T>
void deleteList(T*& pHead);														// Deleting list

void deleteLast(ListManager*& pHead);											// Deleting the last item in the list
void virtualShape(int click[4], float points[4], sf::RenderWindow& window);		// Display a preview of the unaccepted shape on the window



/* Write and read functions */
void writeToFile(ListManager* pHead, std::string adress);						// Writing shape information to the selected file
void readFile(ListManager*& pHead, std::string adress);							// Reading information about shapes from the selected file
bool splitWords(ListManager*& pHead, std::string line);							// Division of coded information into subproblems