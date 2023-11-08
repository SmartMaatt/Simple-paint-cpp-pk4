#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

#include "menu.h"

// Set background color
void Button::setBackColor(sf::Color color) {
    button.setFillColor(color);
}

// Set position
void Button::setPosition(sf::Vector2f point, int frame) {
    button.setPosition(point.x + frame, point.y + frame);
    menuImage.setPosition(point.x + frame, point.y + frame);
}

// Set activity
void Button::setActive(bool what) {
    active = what;
}

// Set highlighting
void Button::setHovered(bool what) {
    hovered = what;
}

// Change texture (limited due to use in one case)
void Button::changeTexture(int which) {
    menuImage.setTextureRect(sf::IntRect(50 * which, 150, 50, 50));
}

// Draw button on screen
void Button::drawTo(sf::RenderWindow& window) {
    if (active || hovered)
        button.setFillColor(sf::Color(200, 200, 200));
    else
        button.setFillColor(sf::Color(220, 220, 220));

    window.draw(button);
    window.draw(menuImage);
}

// Return true if cursor is over the button
bool Button::isMouseOver(sf::RenderWindow& window) {
    int mouseX = sf::Mouse::getPosition(window).x;
    int mouseY = sf::Mouse::getPosition(window).y;

    int btnPosX = button.getPosition().x;
    int btnPosY = button.getPosition().y;

    int btnxPosWidth = btnPosX + btnWidth;
    int btnyPosHeight = btnPosY + btnHeight;

    return mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY;
}

// Button constructor
Button::Button(sf::Vector2f buttonSize, sf::Vector2f buttonPosition, float frame, sf::Color bgColor, sf::Texture* menuTexture, int btnNo, int textureRow) {
    button.setSize(buttonSize);
    button.setFillColor(bgColor);
    button.setOutlineThickness(frame);
    button.setOutlineColor(sf::Color(180, 180, 180));

    menuImage.setSize(buttonSize);
    menuImage.setTexture(menuTexture);
    menuImage.setTextureRect(sf::IntRect(buttonSize.x * btnNo, buttonSize.y * textureRow, buttonSize.x, buttonSize.y));

    setPosition(buttonPosition, frame);

    btnWidth = buttonSize.x;
    btnHeight = buttonSize.y;
    active = false;
}

/* INTERFACE */

// Draw the entire GUI
void Gui::drawGui(sf::RenderWindow& window) {
    window.draw(menuBg);
    window.draw(lineText);
    window.draw(fillText);

    for (auto& buttonRow : guiVector) {
        for (auto& button : buttonRow) {
            button.drawTo(window);
        }
    }
}

// Constructor for a row of buttons
void Gui::makeMenu(std::vector<Button>* menuButtonRow, sf::Vector2f buttonSize, sf::Vector2f buttonPosition, float frame, sf::Color bgColor, sf::Texture* menuTexture, int btnAmount, int row) {
    for (int i = 0; i < btnAmount; ++i) {
        menuButtonRow->emplace_back(buttonSize, sf::Vector2f{buttonPosition.x + buttonSize.x * i, buttonPosition.y}, frame, bgColor, menuTexture, i, row);
    }
}

// Highlight button on hover
void Gui::menuReact(sf::RenderWindow& window, int row) {
    for (auto& button : guiVector[row]) {
        button.setHovered(button.isMouseOver(window));
    }
}

// Single button click response
bool Gui::menuClick(sf::RenderWindow& window, int row) {
    return guiVector[row][0].isMouseOver(window);
}

// Response to click for a list of buttons
int Gui::menuListClick(sf::RenderWindow& window, int row) {
    for (int i = 0; i < guiVector[row].size(); ++i) {
        if (guiVector[row][i].isMouseOver(window)) {
            for (auto& button : guiVector[row]) {
                button.setActive(false);
            }
            guiVector[row][i].setActive(true);
            return i;
        }
    }
    return -1;
}

// Change texts in GUI
void Gui::changeText(int which, int value) {
    if (which == 0) {
        lineText.setString("Grubosc linii: " + std::to_string(value + 1));
    }
    else if (which == 1) {
        if (value == 0) {
            fillText.setString("Shape fill: Nie");
            guiVector[3][0].changeTexture(0);
        }
        else if (value == 1) {
            fillText.setString("Shape fill: Tak");
            guiVector[3][0].changeTexture(1);
        }
    }
}

// Operator overload
Gui::operator int() const {
    return static_cast<int>(guiVector.size());
}

// GUI constructor assembling all buttons
Gui::Gui(sf::RenderWindow& window, sf::Texture* menuTexture, sf::Font* font) {
    std::vector<Button> temp;

    // Top bar background
    menuBg.setFillColor(sf::Color(180, 180, 180));
    menuBg.setSize({ 1280,54 });

    // Text for line thickness and shape fill
    lineText.setString("Line thickness: 1");
    lineText.setFont(*font);
    lineText.setCharacterSize(16);
    lineText.setPosition({ 930,4 });
    lineText.setFillColor(sf::Color::Black);

    fillText.setString("Shape fill: No");
    fillText.setFont(*font);
    fillText.setCharacterSize(16);
    fillText.setPosition({ 930,26 });
    fillText.setFillColor(sf::Color::Black);

    // Tool buttons
    makeMenu(&temp, { 50,50 }, { 0,0 }, 2, sf::Color(220, 220, 220), menuTexture, 6, 0);
    guiVector.push_back(temp);
    temp.clear();

    // Color buttons
    makeMenu(&temp, { 50,50 }, { 310,0 }, 2, sf::Color(220, 220, 220), menuTexture, 10, 1);
    guiVector.push_back(temp);
    temp.clear();

    // Line thickness change button
    makeMenu(&temp, { 50,50 }, { 820,0 }, 2, sf::Color(220, 220, 220), menuTexture, 1, 2);
    guiVector.push_back(temp);
    temp.clear();

    // Shape fill button
    makeMenu(&temp, { 50,50 }, { 870,0 }, 2, sf::Color(220, 220, 220), menuTexture, 1, 3);
    guiVector.push_back(temp);
    temp.clear();

    // Undo button
    makeMenu(&temp, { 50,50 }, { 1126,0 }, 2, sf::Color(220, 220, 220), menuTexture, 1, 4);
    guiVector.push_back(temp);
    temp.clear();

    // Save button
    makeMenu(&temp, { 50,50 }, { 1178,0 }, 2, sf::Color(220, 220, 220), menuTexture, 1, 5);
    guiVector.push_back(temp);
    temp.clear();

    // Load button
    makeMenu(&temp, { 50,50 }, { 1230,0 }, 2, sf::Color(220, 220, 220), menuTexture, 1, 6);
    guiVector.push_back(temp);
    temp.clear();

    // Default values
    guiVector[0][0].setActive(true);
    guiVector[1][2].setActive(true);
}
