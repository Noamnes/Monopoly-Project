// INCLUDES
#include <SFML/Graphics.hpp>
#include <iostream>
#include "MonopolyGame.hpp"

// Defines
#define WINDOW_HEIGHT 1000
#define PLAYERS_MENU_WIDTH 0 // the width of the players menu on the right side of the window
#define WINDOW_WIDTH WINDOW_HEIGHT + PLAYERS_MENU_WIDTH
#define CORNERS_RATIO 2.f/13.f // defined the percentage of y-axis(WINDOW_HEIGHT) covered by one corner of the board. So the corner is WINDOW_HEIGHT*(CORNERS_RATIO) pixels long
#define WINDOW_TITLE "Monopoly Game"

// MAIN
int main() {
    // CREATE THE RENDER WINDOW
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);

    // Load the common font of the game
    sf::Font font;
    if (!font.loadFromFile("Montserrat-Black.ttf"))
    {
        std::cerr << "Failed to load font.\n";
        return -1;
    }

    // Create the game:
    MonopolyGame game(window.getSize(), CORNERS_RATIO, font);

    // Initialize players' names:
    game.setPlayersNames({"shoe", "hat", "dog", "car"});

    // Start the game
    game.startGame();
    
    while (window.isOpen()) {
        // POLL EVENTS
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                // Mouse left click
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        // Get the position of the mouse
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        
                        // Let the game handle the mouse click
                        game.handleMouseClick(mousePos);
                    }
                    break;

                // Key pressed event
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) {
                        window.close();
                    }
                    break;
            }
        }

        // Clear previous buffer
        window.clear();
        
        // Draw the game
        window.draw(game);

        // Display the new buffer
        window.display();
    }

    return 0;
}
