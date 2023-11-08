#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

// Class representing an individual button in the GUI
class Button {
private:
	sf::RectangleShape button;       // SFML library rectangle shape variables
	sf::RectangleShape menuImage;    // Button style, size, and texture

	int btnWidth;                    // Button width
	int btnHeight;                   // Button height
	bool active;                     // Is button active
	bool hovered;                    // Is button hovered by cursor

public:
	void setBackColor(sf::Color color);                    // Set background color
	void setPosition(sf::Vector2f point, int frame);       // Set position
	void setActive(bool what);                             // Set activity status
	void setHovered(bool what);                            // Set hover status
	void changeTexture(int which);                         // Change texture (limited usage case)
	void drawTo(sf::RenderWindow& window);                 // Draw button to screen
	bool isMouseOver(sf::RenderWindow& window);            // Return true if cursor is over the button

	Button(sf::Vector2f buttonSize, sf::Vector2f buttonPosition, float frame,
		sf::Color bgColor, sf::Texture* menuTexture, int btnNo, int textureRow);
};

// Class controlling the GUI
class Gui {
private:
	std::vector<std::vector<Button>> guiVector;           // Vector of vectors storing all available buttons
	sf::RectangleShape menuBg;                            // Menu background
	sf::Text lineText;                                    // Text for line thickness
	sf::Text fillText;                                    // Text for shape fill

public:
	void drawGui(sf::RenderWindow& window);               // Draw the entire GUI

	// Constructor for a row of related buttons (tool/color)
	void makeMenu(std::vector<Button>* menuButtonRow, sf::Vector2f buttonSize,
		sf::Vector2f buttonPosition, float frame, sf::Color bgColor,
		sf::Texture* menuTexture, int btnAmount, int row);

	void menuReact(sf::RenderWindow& window, int row);    // Highlight button when hovered
	bool menuClick(sf::RenderWindow& window, int row);    // Single button click response
	int menuListClick(sf::RenderWindow& window, int row); // Response to click for a list of buttons
	void changeText(int which, int value);                // Change text in GUI

	// Overloaded operator to cast Gui to an integer
	operator int() const;

	Gui(sf::RenderWindow& window, sf::Texture* menuTexture, sf::Font* font);
};
