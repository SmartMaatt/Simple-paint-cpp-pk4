#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "menu.h"   // Classes and functions related to GUI
#include "canvas.h" // Class and functions for the workspace
#include "classes.h" // Main classes and functions of shapes, list management, file read and write

int main() {
    // Main application window
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Graphic Editor - PK4 project", sf::Style::Close | sf::Style::Titlebar);

    // Loading the "Arial" font
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Font not found!\n";
    }

    // Loading the icon textures file
    sf::Texture menuTexture;
    if (!menuTexture.loadFromFile("menuTexture.png")) {
        std::cout << "Texture file could not be loaded correctly!" << std::endl;
    }

    // Variables storing information about active tools, selected points and the drawing process
    int click[4] = { 0, 2, 0, 0 };
    float points[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    bool mouseHeld = false;

    ListManager* pHead = nullptr; // Head of the main singly linked list storing shapes
    Gui mainGui(window, &menuTexture, &font); // GUI program constructor
    Canvas field; // Workspace constructor

    // Main program loop
    while (window.isOpen()) {

        sf::Event event; // SFML library event variable
        while (window.pollEvent(event)) {
            
            // Switch determining the response to the given event "event"
            switch (event.type) {
            
            // Closing the program by clicking the cross
            case sf::Event::Closed:
                window.close();
                break;

            // Changing the highlight color of interface buttons on mouse hover
            case sf::Event::MouseMoved:
                for (int i = 0; i < static_cast<int>(mainGui); ++i) {
                    mainGui.menuReact(window, i);
                }
                break;

            // Reaction to pressing the mouse button
            case sf::Event::MouseButtonPressed:
                // Confirming left mouse button click
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Buttons for color/shape selection
                    for (int i = 0; i < 2; ++i) {
                        int clickResult = mainGui.menuListClick(window, i);
                        if (clickResult > -1) {
                            click[i] = clickResult;
                        }
                    }

                    // Button to change line thickness
                    if (mainGui.menuClick(window, 2)) {
                        click[2]++;
                        if (click[2] > 4) click[2] = 0;
                        mainGui.changeText(0, click[2]);
                    }

                    // Button to change shape fill
                    if (mainGui.menuClick(window, 3)) {
                        click[3]++;
                        if (click[3] > 1) click[3] = 0;
                        mainGui.changeText(1, click[3]);
                    }

                    // Undo button
                    if (mainGui.menuClick(window, 4)) {
                        deleteLast(pHead);
                    }

                    // Save project
                    if (mainGui.menuClick(window, 5)) {
                        writeToFile(pHead, "project.json");
                    }

                    // Read project
                    if (mainGui.menuClick(window, 6)) {
                        readFile(pHead, "project.json");
                    }

                    // Reaction to clicking in the drawing area
                    if (field.isMouseOver(window)) {
                        points[0] = static_cast<float>(sf::Mouse::getPosition(window).x); // Saving coordinates
                        points[1] = static_cast<float>(sf::Mouse::getPosition(window).y);
                        std::cout << "Mouse clicked: ";
                        std::cout << "X: " << points[0] << " Y: " << points[1] << std::endl;
                        mouseHeld = true;
                    }
                }
                break;

            // Reaction to releasing the mouse button
            case sf::Event::MouseButtonReleased:
                // Confirming left mouse button click
                if (event.mouseButton.button == sf::Mouse::Left && field.isMouseOver(window)) {
                    points[2] = static_cast<float>(sf::Mouse::getPosition(window).x); // Saving coordinates
                    points[3] = static_cast<float>(sf::Mouse::getPosition(window).y);

                    std::cout << "Mouse released: ";
                    std::cout << "X: " << points[2] << " Y: " << points[3] << std::endl << std::endl;

                    addElement(pHead, click, points, true); // Adding a new element to the list
                    mouseHeld = false;
                }
                break;
            }
        }

        window.clear(sf::Color::White); // Clearing the window
        field.drawTo(window);           // Displaying the workspace
        drawList(pHead, window);        // Displaying all drawn shapes

        if (mouseHeld) {
            virtualShape(click, points, window); // When the mouse is pressed, draw the visualization of the shape to be drawn
        }

        mainGui.drawGui(window); // Displaying the GUI
        window.display();        // Displaying the program window
    }

    deleteList(pHead); // Deleting the dynamically allocated list
    return 0;
}
