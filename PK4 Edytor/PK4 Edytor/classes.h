#pragma once
#ifndef classesh
#define classesh

#include <SFML/Graphics.hpp>
#include <vector>
#include <type_traits>

//Główna, w pełni witualna klasa
class ObiektGraficzny {
	
public:
	virtual void draw(sf::RenderWindow& window) = 0;	//Rysowanie obiektu na ekran
	virtual void showInfo(int click[4]) = 0;			//Wypisywanie informacji o obiekcie na konsole
};


//Klasa kształt
class Shape :public ObiektGraficzny {

protected:
	float X1, Y1, X2, Y2;	//Współrzędne
	sf::Shape* shapeSrc;	//Zmienna kształtu z biblioteki SFML
	bool fill;				//Wypełnienie
	
public:
	sf::Color chooseColor(int color);	//Wybór koloru kształtu
	void draw(sf::RenderWindow& window); //Rysowanie obiektu na ekran

	void setPoints(float points[4]);		//Ustalanie współrzędnych kształtu
	void setColor(sf::Color color);			//Ustalanie koloru kształtu
	void setFilling(int data);				//Ustalanie wypełnienia
	void setOutline(sf::Color color, int data);	//Ustalanie grubości obranowania
	void setPosition(float x, float y);		//Ustalanie pozycji kształtu

	virtual void setSize(float a, float b)=0;	//Ustalanie wielkości kształtu
	virtual void specialCalc() = 0;				//Specjalnie obliczenia dla każdej klasy
};


//Klasa linia
class Line :public Shape {

protected:
	sf::RectangleShape lineShape;	//Zmienna kształtu prostokątu z biblioteki SFML
	float length, angle;			//Parametry linii

public:	
	void setOrigin(float x, float y);	//Ustalanie początku układu wpółrzędnych
	void setSize(float a, float b);		//Ustalanie wielkości kształtu
	void setAngle();					//Ustalanie kąta nachylenia linii
	void specialCalc();					//Obliczenia dla linii
	void showInfo(int click[4]);		//Wypisywanie informacji o obiekcie na konsole

	Line(int click[4], float points[4]);
};


//Klasa prostokąt
class Rectangle :public Shape {

protected:
	sf::RectangleShape rectShape;	//Zmienna kształtu prostokąta z biblioteki SFML
	float a, b, field;				//Parametry prostokąta

public:
	void setSize(float a, float b);		//Ustalanie wielkości kształtu
	void setOrigin();					//Ustalanie początku układu współrzędnych
	void specialCalc();					//Obliczenia dla prostokąta
	void showInfo(int click[4]);		//Wypisywanie informacji o obiekcie na konsole

	Rectangle(int click[4], float points[4]);
};


//Klasa kwadrat
class Square :public Rectangle {

public:
	void setOrigin();				//Ustalanie początku układu współrzędnych
	void showInfo(int click[4]);	//Wypisywanie informacji o obiekcie na konsole

	Square(int click[4], float points[4]);
};


//Klasa elipsa
class Ellipse :public Shape {

protected:
	sf::CircleShape circleShape;		//Zmienna kształtu okręgu z biblioteki SFML
	float a, b, shortR, longR, field;	//Parametry

public:
	void setSize(float a, float b);		//Ustalanie wielkości elipsy
	void specialCalc();					//Obliczenia dla elipsy
	void showInfo(int click[4]);		//Wypisywanie informacji o obiekcie na konsole

	Ellipse(int click[4], float points[4]);
};


//Klasa Okrąg
class Circle :public Ellipse {

public:
	void rotate();					//Obrót i poprawa kształtu względem elipsy
	void showInfo(int click[4]);	//Wypisywanie informacji o obiekcie na konsole

	Circle(int click[4], float points[4]);
};

//Klasa Trójkąt
class Triangle :public Shape {

protected:
	sf::ConvexShape triangleShape;		//Zmienna Convex przechowująca kształt
	float a, b, X3, footing, field, height;	//Zmienne zawierające parametry trójkąta

public:
	void setSize(float a, float b);	//Ustawienie wielkości figury w zależności od kierunku rysowania
	void specialCalc();				//Obliczenia matematyczne związane z trójkątem
	void showInfo(int click[4]);	//Wyświetlanie informacji o trójkącie na konsolę

	Triangle(int click[4], float point[4]);	//Konstruktor trójkąta
};


//Struktura przechowująca utworzone kształty i informacje o nich
struct listManage
{
	ObiektGraficzny* p;
	listManage* pNext;
	int click[4];
	float points[4];
};

/*Funkcje zarządzające listą*/
void addElement(listManage*& pHead, int click[4], float points[4], bool fake);	//Dodawanie elementu do listy
void showInfo(ObiektGraficzny* ptr, int click[4]);								//Wyświetlanie opisu kształtu z użyciem RTTI
void drawList(listManage* pHead, sf::RenderWindow& window);						//Rysowanie listy

template <class T>
void deleteList(T*& pHead);														//Usuwanie listy

void deleteLast(listManage*& pHead);											//Usuwanie ostatniego elementu z listy (Undo)
void virtualShape(int click[4], float points[4], sf::RenderWindow& window);		//Wyświetlna podgląd na niezaakceptowany kszatałt na okno

/*Funkcje zapisu i odczytu*/
void writeToFile(listManage* pHead, std::string adress);						//Zapis do wybranego pliku informacji o kształtach
void readFile(listManage*& pHead, std::string adress);							//Odczyt z wybranego pliku infoamcji o kształtach
bool splitWords(listManage*& pHead, std::string line);							//Podział zakodowanej informacji na podproblemy
#endif