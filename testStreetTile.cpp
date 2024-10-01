// main.cpp

#include <SFML/Graphics.hpp>
#include <iostream>
#include "streetTile.hpp" // Include the LabeledRectangle class header
#include <vector>
#include <utility>
#include "player.hpp"
#include <memory>
#include <string>
#include "coloredTextBox.hpp"

using std::vector, std::pair;

//func that returns a pair:
pair<vector<StreetTile>,vector<sf::Text>> createStreetTilesInAllDirections(sf::Font *font){
    
    // setting up an owner:
    std::shared_ptr<Player> owner = std::make_shared<Player>("John");

    vector<StreetTile> streetTiles;
    vector<sf::Text> texts;
    // create a up StreetTile in the top-left corner of the screen
    sf::Text text("Up", *font, 24);
    text.setPosition(30,50);
    texts.push_back(text);

    StreetTile streetTile(std::string("product name"), (unsigned int)100, *font, \
                                StreetTile::ReadingDirection::Up, sf::Color::Blue);
    streetTile.setOwner(owner);
    streetTile.setBounds(sf::FloatRect(100.f, 50.f, 200.f, 300.f));
    streetTile.setOwnerStripePercentage(0.1);
    streetTile.setBuildingType(StreetTile::BuildingType::OneHouse);
    streetTiles.push_back(streetTile);

    // create Down StreetTile in the top-right corner
    sf::Text text2("Down", *font, 24);
    text2.setPosition(400,50);
    texts.push_back(text2);
    
    StreetTile streetTile2("product name", \
                                100, *font, StreetTile::ReadingDirection::Down);
    streetTile2.setOwner(owner);
    streetTile2.setBounds(sf::FloatRect(500.f, 50.f, 200.f, 300.f));
    streetTile2.setOwnerStripePercentage(0.5);
    streetTile2.setBuildingType(StreetTile::BuildingType::TwoHouses);
    streetTiles.push_back(streetTile2);

    // create Left StreetTile in the bottom-left corner
    sf::Text text3("Left", *font, 24);
    text3.setPosition(30,400);
    texts.push_back(text3);

    StreetTile streetTile3("product name",\
                                100, *font, StreetTile::ReadingDirection::Left);
    streetTile3.setOwner(owner);
    streetTile3.setBounds(sf::FloatRect(100.f, 400.f, 200.f, 300.f));
    streetTile3.setOwnerStripePercentage(0.1);
    streetTile3.setBuildingType(StreetTile::BuildingType::ThreeHouses);
    streetTiles.push_back(streetTile3);

    // create Right StreetTile in the bottom-right corner
    sf::Text text4("Right", *font, 24);
    text4.setPosition(400,400);
    texts.push_back(text4);

    StreetTile streetTile4("product name", \
                                100, *font, StreetTile::ReadingDirection::Right);
    streetTile4.setOwner(owner);
    streetTile4.setBounds(sf::FloatRect(500.f, 400.f, 120.f, 300.f));
    streetTile4.setOwnerStripePercentage(0.1);
    streetTile4.setBuildingType(StreetTile::BuildingType::ThreeHouses);
    streetTiles.push_back(streetTile4);

    return pair<vector<StreetTile>, vector<sf::Text>>(streetTiles, texts);
}

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Labeled Rectangle Example");

    // Load a font
    sf::Font font;
    if (!font.loadFromFile("Montserrat-Black.ttf")){
        std::cerr << "Error loading font 'Montserrat-Black.ttf'. Make sure the font file is in the working directory.\n";
        return -1;
    }

    // ? FUNC StreetTile check:
        auto pair = createStreetTilesInAllDirections(&font);
        auto StreetTiles = pair.first;
        auto texts = pair.second;
    
    vector<sf::Drawable*> drawables;
    for(auto &textBox : StreetTiles){
        drawables.push_back(&textBox);
    }
    
    // Main loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();

            // show position of mouse click:
            if (event.type == sf::Event::MouseButtonPressed)
            {
                std::cout << "Mouse click position: " << event.mouseButton.x << ", " << event.mouseButton.y << std::endl;
            }
        }

        // Clear screen
        window.clear(sf::Color::Black);

        // window.draw(StreetTiles[0]);

        // Draw drawables and after it - draw the texts:
        for (auto drawable : drawables){
            window.draw(*drawable);
        }
        for(auto text : texts){
            window.draw(text);
        }

        // Update the window
        window.display();
    }

    return 0;
}
