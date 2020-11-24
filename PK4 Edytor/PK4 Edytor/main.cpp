#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "menu.h" //klasy i funkcje związane z gui
#include "canvas.h"	//klasa i funkcje obszaru roboczego
#include "classes.h" //główne klasy i funkcje kształtów, zarządzanie listą, zapis i odczyt z pliku

int main()
{
	//Główne okno aplikacji
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Edytor graficzny- projekt Pk4", sf::Style::Close | sf::Style::Titlebar);

	//Instalacja czcionki "Arial"
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
		std::cout << "Font not found!\n";

	//Instalacja pliku z teksturami ikon
	sf::Texture menuTexture;
	if (!menuTexture.loadFromFile("menuTexture.png"))
		std::cout << "Texture file could not be loaded currectly!" << std::endl;

	//Zmienne przechowujące dane na temat aktywnych narzędzi, wybranych punktów i procesie rysowania
	int click[4] = {0,2,0,0};
	float points[4] = { 0,0,0,0 };
	bool mouseHolded = false;

	listManage* pHead = nullptr; //Głowa głównej listy jednokierunkowej przechowującej kształty
	Gui mainGui(window, &menuTexture, &font); //Konstruktor interface'u(Gui) programu
	canvas field; //Konstruktor przestrzeni roboczej programu


	//Główna pętla programu
	while (window.isOpen())
	{
		sf::Event event; //Zmienna wydarzenia biblioteki SFML
		while (window.pollEvent(event))	//Pętla wywołania reakcji na wydarzenie 
		{
			//Switch określający reakcję na dane wydarzenie "event"
			switch (event.type) {


				//Zamknięcie programu po wciśnięciu krzyżyka
				case sf::Event::Closed:
					window.close();


				//Zmiana koloru podświetlenia przycisków interfacu po najechaniu kursorem
				case sf::Event::MouseMoved:
					for (int i = 0; i < (int)mainGui; i++)
						mainGui.menuReact(window, i);
				break;


				//Reakcja na wciśnięcie klawisza myszy
				case sf::Event::MouseButtonPressed:

					//Potwierdzenie wciśnięcia lewego przycisku myszy
					if (event.mouseButton.button == sf::Mouse::Left) {

						//Przyciski wyboru koloru/kształtu
						for (int i = 0; i < 2; i++) {
							if (mainGui.menuListClick(window, i) > -1) {
								click[i] = mainGui.menuListClick(window, i);
							}
						}

						//Przycisk zmiany grubości linii
						if (mainGui.menuClick(window, 2) == true) {
							click[2]++;
							if (click[2] > 4) click[2] = 0;
							mainGui.changeText(0, click[2]);
						}

						//Przycisk zmiany wypełnienia kształtu
						if (mainGui.menuClick(window, 3) == true) {
							click[3]++;
							if (click[3] > 1) click[3] = 0;
							mainGui.changeText(1, click[3]);
						}

						//Przycisk "Undo"
						if (mainGui.menuClick(window, 4) == true) {
							deleteLast(pHead);
						}

						//Zapis do Pliku "ProjectPK4"
						if (mainGui.menuClick(window, 5) == true){
							writeToFile(pHead, "ProjectPK4.json");
						}

						//Odczyt z Pliku "ProjectPK4"
						if (mainGui.menuClick(window, 6) == true) {
							readFile(pHead, "ProjectPK4.json");
						}

						//Reakcja na kliknięcie w obszarze do rysowania
						if (field.isMouseOver(window)) {
							points[0]= sf::Mouse::getPosition(window).x; //Zapis współrzędnych 
							points[1]= sf::Mouse::getPosition(window).y;
							std::cout << "Mysz kliknieta: ";
							std::cout << "X: " << points[0] << " Y: " << points[1] << std::endl;
							mouseHolded = true;
						}
					}
				break;


				//Reakcja na puszczenie klawisza myszy
				case sf::Event::MouseButtonReleased:

					//Potwierdzenie wciśnięcia lewego przycisku myszy
					if (event.mouseButton.button == sf::Mouse::Left && field.isMouseOver(window)) {
						points[2] = sf::Mouse::getPosition(window).x; //Zapis współrzędnych
						points[3] = sf::Mouse::getPosition(window).y;

						std::cout << "Mysz puszczona: ";
						std::cout << "X: " << points[2] << " Y: " << points[3] << std::endl << std::endl;

						addElement(pHead, click, points, true); //Dodanie nowego elementu do listy
						mouseHolded = false;
					}
				break;
			}
		}


		window.clear(sf::Color::White);	//Czyszczenie okna
		field.drawTo(window);			//Wyświetlenie pola roboczego
		drawList(pHead, window);		//Wyświetlenie wszystkich narysowanych kształtów

		if (mouseHolded) {virtualShape(click, points, window);};	//Gdy myszka jest wciśnięta. Rysowanie wizualizacji kształtu który będziemy rysować
		
		mainGui.drawGui(window);		//Wyświetlenie interface'u
		window.display();				//Wyświetlenie okna programu
	}

	deleteList(pHead);	//Usunięcie dynamicznie zaalokowanej listy
	return 0;
}