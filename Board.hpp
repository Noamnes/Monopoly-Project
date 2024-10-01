#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "Tile.hpp"

class Board : public sf::Drawable, sf::Transformable{
    public:
        Board(sf::Vector2u windowSize, float cornersRatio, sf::Font& font);
        /** @brief creates the game tiles. */
        void createTiles();
        void move(Player& player, unsigned int steps);
    private:
        /** @brief draws the game board. */
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        
        //* MEMBERS
            // Edges
            std::vector<std::shared_ptr<Tile>> m_downEdge;
            std::vector<std::shared_ptr<Tile>> m_leftEdge;
            std::vector<std::shared_ptr<Tile>> m_upEdge;
            std::vector<std::shared_ptr<Tile>> m_rightEdge;

            // Corners
            std::shared_ptr<Tile> m_bottomRightCorner;
            std::shared_ptr<Tile> m_bottomLeftCorner;
            std::shared_ptr<Tile> m_topLeftCorner;
            std::shared_ptr<Tile> m_topRightCorner;

};

Board::Board(sf::Vector2u windowSize, float cornersRatio, sf::Font& font): m_font(font){
    
}

void Board::createTiles(){
    // create the corners
    //? not sure what is the class for the corners
    m_bottomRightCorner = std::make_unique<?>(/*params*/);
    m_bottomLeftCorner = std::make_unique<?>(/*params*/);
    m_topLeftCorner = std::make_unique<?>(/*params*/);
    m_topRightCorner = std::make_unique<?>(/*params*/);

    // create the edges
    
    // down edge
    m_downEdge.push_back(std::make_unique<StreetTile>("Ofakim", 100, m_font, StreetTile::ReadingDirection::Up, sf::Color::Brown));
    m_downEdge.push_back(std::make_unique<CommunityTile>("Community", m_font)); //! need to create
    m_downEdge.push_back(std::make_unique<StreetTile>("Netivot", 60, m_font, StreetTile::ReadingDirection::Up, sf::Color::Brown));
    m_downEdge.push_back(std::make_unique<TaxTile>("Income Tax", 200, m_font)); //! need to create
    m_downEdge.push_back(std::make_unique<TrainTile>("Western Negev Train", 200, m_font)); //! need to create
    m_downEdge.push_back(std::make_unique<StreetTile>("Ashkelon", 50, m_font, StreetTile::ReadingDirection::Up, sf::Color::LightBlue));
    m_downEdge.push_back(std::make_unique<ChanceTile>("Chance", m_font)); //! need to create
    m_downEdge.push_back(std::make_unique<StreetTile>("Nitzanim", 50, m_font, StreetTile::ReadingDirection::Up, sf::Color::LightBlue));
    m_downEdge.push_back(std::make_unique<StreetTile>("Palmachim", 60, m_font, StreetTile::ReadingDirection::Up, sf::Color::LightBlue));
    m_downEdge.push_back(std::make_unique<JailTile>("Jail", m_font)); //! need to create

    // left edge
    m_leftEdge.push_back(std::make_unique<StreetTile>("Eilat", 100, m_font, StreetTile::ReadingDirection::Left, sf::Color::Pink));
    m_leftEdge.push_back(std::make_unique<UtilityTile>("Electric Company", 150, m_font)); //! need to create
    m_leftEdge.push_back(std::make_unique<StreetTile>("Yotvata", 60, m_font, StreetTile::ReadingDirection::Left, sf::Color::Pink));
    m_leftEdge.push_back(std::make_unique<StreetTile>("Mitzpe Ramon", 60, m_font, StreetTile::ReadingDirection::Left, sf::Color::Pink));
    m_leftEdge.push_back(std::make_unique<TrainTile>("South Negev Train", 200, m_font)); //! need to create
    m_leftEdge.push_back(std::make_unique<StreetTile>("Sde Boker", 50, m_font, StreetTile::ReadingDirection::Left, sf::Color::Orange));
    m_leftEdge.push_back(std::make_unique<CommunityTile>("Community", m_font)); //! need to create
    m_leftEdge.push_back(std::make_unique<StreetTile>("Dimona", 50, m_font, StreetTile::ReadingDirection::Left, sf::Color::Orange));
    m_leftEdge.push_back(std::make_unique<StreetTile>("Arad", 60, m_font, StreetTile::ReadingDirection::Left, sf::Color::Orange));
    
    // up edge
    m_upEdge.push_back(std::make_unique<StreetTile>("Haifa", 100, m_font, StreetTile::ReadingDirection::Down, sf::Color::Red));
    m_upEdge.push_back(std::make_unique<ChanceTile>("Chance", m_font)); //! need to create
    m_upEdge.push_back(std::make_unique<StreetTile>("Kiryat Ata", 60, m_font, StreetTile::ReadingDirection::Down, sf::Color::Red));
    m_upEdge.push_back(std::make_unique<StreetTile>("Kiryat Motzkin", 60, m_font, StreetTile::ReadingDirection::Down, sf::Color::Red));
    m_upEdge.push_back(std::make_unique<TrainTile>("North Train", 200, m_font)); //! need to create
    m_upEdge.push_back(std::make_unique<StreetTile>("Tiberias", 50, m_font, StreetTile::ReadingDirection::Down, sf::Color::Yellow));
    m_upEdge.push_back(std::make_unique<StreetTile>("Karmiel", 50, m_font, StreetTile::ReadingDirection::Down, sf::Color::Yellow));
    m_upEdge.push_back(std::make_unique<UtilityTile>("Water Company", 150, m_font)); //! need to create
    m_upEdge.push_back(std::make_unique<StreetTile>("Tzfat", 60, m_font, StreetTile::ReadingDirection::Down, sf::Color::Yellow));

    // right edge
    m_rightEdge.push_back(std::make_unique<StreetTile>("Tel Aviv", 100, m_font, StreetTile::ReadingDirection::Right, sf::Color::Green));
    m_rightEdge.push_back(std::make_unique<StreetTile>("Ramat Gan", 60, m_font, StreetTile::ReadingDirection::Right, sf::Color::Green));
    m_rightEdge.push_back(std::make_unique<CommunityTile>("Community", m_font)); //! need to create
    m_rightEdge.push_back(std::make_unique<StreetTile>("Holon", 60, m_font, StreetTile::ReadingDirection::Right, sf::Color::Green));
    m_rightEdge.push_back(std::make_unique<TrainTile>("Center Train", 200, m_font)); //! need to create
    m_rightEdge.push_back(std::make_unique<ChanceTile>("Chance", m_font)); //! need to create
    m_rightEdge.push_back(std::make_unique<StreetTile>("Rishon LeZion", 50, m_font, StreetTile::ReadingDirection::Right, sf::Color::DarkBlue));
    m_rightEdge.push_back(std::make_unique<TaxTile>("Luxury Tax", 100, m_font)); //! need to create
    m_rightEdge.push_back(std::make_unique<StreetTile>("Rehovot", 50, m_font, StreetTile::ReadingDirection::Right, sf::Color::DarkBlue));

}

void Board::move(Player& player, unsigned int steps){
    // first: clear the m_landingPlayerName from curr tile and set it in the new tile, 
    // second: set the player positon tile to new tile

    // get the current tile
    auto currTile = player->getTile();

    // get the new tile
    auto newTile = getNextTile(currTile, steps);

    // clear the m_landingPlayerName from curr tile
    currTile->setLandingPlayerName("");

    // set the m_landingPlayerName in the new tile
    newTile->setLandingPlayerName(player->getName());

    player->setTile(newTile);
}