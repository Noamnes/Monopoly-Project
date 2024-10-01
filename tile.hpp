#pragma once

#include <SFML/Graphics.hpp>
#include "menu.hpp"

class Tile : sf::Drawable, sf::Transformable{
    public:
        Tile(std::string name, sf::Font& font);
        virtual Menu::Type onLanding(Player& player) = 0;
    
    private:
        std::string m_name;
}