// main.cpp

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "coloredTextBox.hpp"

using std::vector, std::pair;

pair<vector<ColoredTextBox>,vector<sf::Text>> createTextBoxesInAllDirections(sf::Font *font){
    
    vector<ColoredTextBox> textBoxes;
    vector<sf::Text> texts;
    // create a up ColoredTextBox in the top-left corner of the screen
    sf::Text text("Up", *font, 24);
    text.setPosition(30,50);
    texts.push_back(text);

    ColoredTextBox textBox(sf::FloatRect(100.f, 50.f, 200.f, 300), {{sf::Text("first line",*font), ColoredTextBox::Alignment::Center},{sf::Text("second line",*font), ColoredTextBox::Alignment::Right}}, ColoredTextBox::TextDirection::Up, sf::Color::Blue);
    textBoxes.push_back(textBox);

    // create a Down ColoredTextBox in the top-right corner of the screen
    sf::Text text2("Down", *font, 24);
    text2.setPosition(400,50);
    texts.push_back(text2);

    ColoredTextBox textBox2(sf::FloatRect(500.f, 50.f, 200.f, 300), {{sf::Text("first line",*font), ColoredTextBox::Alignment::Center},{sf::Text("second line",*font), ColoredTextBox::Alignment::Right}}, ColoredTextBox::TextDirection::Down, sf::Color::Blue);
    textBoxes.push_back(textBox2);

    // create a Left ColoredTextBox in the bottom-left corner of the screen
    sf::Text text3("Left", *font, 24);
    text3.setPosition(30,400);
    texts.push_back(text3);
    
    ColoredTextBox textBox3(sf::FloatRect(100.f, 400.f, 200.f, 300), {{sf::Text("first line",*font), ColoredTextBox::Alignment::Center},{sf::Text("second line",*font), ColoredTextBox::Alignment::Right}}, ColoredTextBox::TextDirection::Left, sf::Color::Blue);
    textBoxes.push_back(textBox3);

    // create a Right ColoredTextBox in the bottom-right corner of the screen
    sf::Text text4("Right", *font, 24);
    text4.setPosition(400,400);
    texts.push_back(text4);

    ColoredTextBox textBox4(sf::FloatRect(500.f, 400.f, 200.f, 300), {{sf::Text("first line",*font), ColoredTextBox::Alignment::Center},{sf::Text("second line",*font), ColoredTextBox::Alignment::Right}}, ColoredTextBox::TextDirection::Right, sf::Color::Blue);
    textBoxes.push_back(textBox4);

    return pair<vector<ColoredTextBox>, vector<sf::Text>>(textBoxes, texts);
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

    vector<sf::Drawable*> drawables;

    ColoredTextBox textBox(sf::FloatRect(100.f, 50.f, 800.f, 20), {{sf::Text("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz",font, 24),ColoredTextBox::Alignment::Center}}, ColoredTextBox::TextDirection::Up, sf::Color::Blue);    
    drawables.push_back(&textBox);

    // make a sf::Text right to the textBox
    // sf::Text text("ABCDEFGHIJKNLMOP", font, 18);
    // text.setPosition(250, 47);
    // drawables.push_back(&text);

    // // ? FUNC ColoredTextBox check:
    //     auto pair = createTextBoxesInAllDirections(&font);
    //     auto coloredTextBoxes = pair.first;
    //     auto texts = pair.second;  
    
    

    // // add the coloredTextBoxes to the drawables:
    // for(auto &textBox : coloredTextBoxes){
    //     drawables.push_back(&textBox);
    // }
    
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
        // for(auto text : texts){
        //     window.draw(text);
        // }

        // Update the window
        window.display();
    }

    return 0;
}
