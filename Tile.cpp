
#include "Tile.hpp"

//* Getters ONLY
    //m_name
    std::string Tile::getName(){
        return m_name;
    }
    //m_landingPlayerName
    std::string Tile::getLandingPlayerName(){
        return m_landingPlayerName;
    }
    //m_font
    sf::Font& Tile::getFont(){
        return m_font;
    }
    //m_readingDirection
    Tile::ReadingDirection Tile::getReadingDirection(){
        return m_readingDirection;
    }
    //m_bounds
    sf::FloatRect Tile::getBounds(){
        return m_bounds;
    }