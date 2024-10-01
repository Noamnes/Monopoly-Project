// INCLUDES
#include <SFML/Graphics.hpp>

// Defines
#define WINDOW_HEIGHT 1000
#define PLAYERS_MENU_WIDTH 200
#define WINDOW_WIDTH WINDOW_HEIGHT + PLAYERS_MENU_WIDTH
#define CORNERS_RATIO 2.f/13.f // defined the presentage of y-axis(WINDOW_HEIGHT) covered by one corner. so the Corner is WINDOW_HEIGHT*(CORNERS_RATIO) pixcels long
#define WINDOW_TITLE "Monopoly Game"

void initialGraphicalAttributes(monopolyGame& game){
    //set corners
    setCornersRectunglesAttributes(game);
    // set downEdge
    setHorizontalRectunglesAttributes(game, sf::FloatRect(CORNERSIZE, windowLength-CORNERSIZE ,windowLength - 2*CORNERSIZE , CORNERSIZE)); // declration: Rect(T rectLeft, T rectTop, T rectWidth, T rectHeight);
    // set leftEdge
    setVerticalRectunglesAttributes(game, sf::FloatRect(0, CORNERSIZE, CORNERSIZE, windowLength - 2*CORNERSIZE)) // declration: Rect(T rectLeft, T rectTop, T rectWidth, T rectHeight);
    // set upEdge
    setHorizontalRectunglesAttributes(game, sf::FloatRect(CORNERSIZE, 0, windowLength - 2*CORNERSIZE , CORNERSIZE)); // declration: Rect(T rectLeft, T rectTop, T rectWidth, T rectHeight);
    // set rightEdge
    setVerticalRectunglesAttributes(game, sf::FloatRect(0, CORNERSIZE, CORNERSIZE, windowLength - 2*CORNERSIZE)) // declration: Rect(T rectLeft, T rectTop, T rectWidth, T rectHeight);
}

// MAIN
int main() {
    // CREATE THE RENDER WINDOW
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);

    // load the common font of the game
    sf::Font font;
    if (!font.loadFromFile("path_to_font.ttf"))
    {
        std::cerr << "Failed to load font.\n";
        return -1;
    }

    // create the game:
    monopolyGame game(window.getSize(), CORNERS_RATIO, font);

    // initialize players names:
    game.setPlayersNames({"shoe", "hat", "dog", "car"});

    // start the game
    game.startGame();
    
    while(window.isOpen()){
        // POLL EVENTS
        sf::Event event;
        while(window.pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                // mouse left click
                case sf::Event::MouseButtonPressed:
                    if(event.mouseButton.button == sf::Mouse::Left){
                        // get the position of the mouse
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        
                        // let the game handle the mouse click
                        game.handleMouseClick(mousePos);
                    }
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Escape){
                        window.close();
                    }
                    break;
            }
        }

        // clear prev buffer
        window.clear();
        
        // draw the game
        window.draw(game);

        // display the new buffer
        window.display();
    }
    return 0;
}