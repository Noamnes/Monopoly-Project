#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "StreetTile.hpp"

class Player;  // Forward declaration for Player class

class Board : public sf::Drawable, public sf::Transformable {
public:
    /** @brief creates a squere Board with the given edges size and font
     * 
     * @param edgeSize the size of the edges of the board
     * @param cornersRatio the ratio of the squere corners of the board to the edges
     * @param font the font to be used for the text on the board
     */
    Board(float edgeSize, float cornersRatio, sf::Font& font);
    /** @brief create the tiles of the standard monopoly board */
    void createTiles(); 
    /** @brief Calculates the tile a player would land on if they move dicesum steps from their currTile
     * 
     * @param currTile the tile the player is currently on
     * @param diceSum the sum of the dice rolls
    */
    StreetTile* getTileAfterMove(StreetTile* currTile, unsigned int diceSum);
    /** @brief Moves the player to the new tile
     * 
     * @param player the player to move
     * @param currTile the tile the player is currently on
     * @param newTile the tile the player is moving to
     */
    void movePlayer(Player& player, StreetTile* currTile, StreetTile* newTile);
    /** @brief move the given player to the jail tail.
     * 
     * @param player the player to move to jail
    */
    void movePlayerToJail(Player& player);
    /** @brief get the jail tile of the board
     * 
     * @return the jail tile of the board
     */
    StreetTile* getJailTile();
    
    /** @brief whether the given player has all the streets of a given color.
     * 
     * @param player the player to check
     * @param color the color to check
    */
    bool hasAllStreetOfColor(Player& player, sf::Color color);

private:
    // Inherited via Drawable
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override; // Implemented
    /** @brief adjust all the graphical components of the board 
     * 
     * This function should be called right after a change to the data has accured.
    */
    void adjustAllComponents();
    /** @brief set the grapical attributes of a horizontal edge of the board(Up or Down).*/
    void setHorizontalEdgeBounds(std::vector<std::unique_ptr<StreetTile>>& edge, sf::FloatRect bounds);
    /** @brief set the grapical attributes of a vertical edge of the board(Left or Right).*/
    void setVerticalEdgeBounds(std::vector<std::unique_ptr<StreetTile>>& edge, sf::FloatRect bounds);

    // Members
    std::vector<std::unique_ptr<StreetTile>> m_downEdge;
    std::vector<std::unique_ptr<StreetTile>> m_leftEdge;
    std::vector<std::unique_ptr<StreetTile>> m_upEdge;
    std::vector<std::unique_ptr<StreetTile>> m_rightEdge;

    std::unique_ptr<StreetTile> m_BottomRightCorner; // Corrected spelling
    std::unique_ptr<StreetTile> m_BottomLeftCorner;  // Corrected spelling
    std::unique_ptr<StreetTile> m_TopLeftCorner;
    std::unique_ptr<StreetTile> m_TopRightCorner;

    // the size of the edges of the board
    float m_edgeSize;
    // the presentage of the squere corners of the board to the edges
    float m_cornersRatio;

    sf::Font& m_font;
};