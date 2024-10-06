#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <unordered_map>
#include "Player.hpp"
#include "Board.hpp"
// #include "Menu.hpp"

/** @class MonopolyGame
 * 
 * @brief Represents the Monopoly game with all it's logic and graphics.
 */
class MonopolyGame : public sf::Drawable {
public:
    /** @brief initilize the MonopolyGame in the windowSize and the font
     * 
     * @param windowSize The size of the window.
     * @param cornersRatio The percentage of y-axis(WINDOW_HEIGHT) covered by one corner of the board.
     * @param font The font used in the game.
    */
    MonopolyGame(const sf::Vector2u& windowSize, float cornersRatio, sf::Font& font);

    /** @brief Set the names of the players in the game.
     * 
     * @param names The names of the players.
     */
    void setPlayersNames(std::vector<std::string> names); 
    
    /** @brief set the game to it's starting state(strat menu, starting player etc.) */
    void startGame(); // implement at the end

    /** @brief handle the mouse click on the window.
     * 
     * checks the current menu and the position of the mouse on it and change the game state accordingly.
     * @param mousePos The position of the mouse when clicked.
     */
    void handleMouseClick(sf::Vector2i& mousePos); 

private:
    
    /** @brief draw the game to the render target.
     * 
     * this functions is of the sf::Drawable interface.
     * it is called by the window to draw the game.
    */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // set the current menu to the menu with the given type and set the game state accordingly
    // void setMenu(Menu::Type menuType); //! UNCOMMENT

    //* MEMBERS
    // members that don't change often during the game:
    
        // players
        std::vector<Player> m_players; //! UNCOMMENT
    
        // board contaning tiles
        Board m_board;
    
        // the menus
        // std::unordered_map<Menu::Type, Menu> m_menus; //! UNCOMMENT
    
        // the dice
        // Dice m_dice; //! UNCOMMENT
    
    // members that change regularly:
        
        // current player
        unsigned int m_currentPlayerIndex; //! UNCOMMENT
        
        // current menu
        // Menu m_currentMenu; //! UNCOMMENT
        
        // the number of doubles the current player rolled
        unsigned int m_doublesCount; //! UNCOMMENT
        
        // the sum of the dice in the current roll
        unsigned int m_diceSum; //! UNCOMMENT

};