#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Button.hpp"

class Menu{
    public:
        enum class Type{
            RollDice,
            DiceInRoll,
            PlayerBankrupt,
            EndTurn,
            BuyMenu,
            Want2Build,
            chooseBuild,
            AffirmBuild,
            Tax,
            JailMenu,
            JailDiceInRoll,
            PreEndTurn
        };
        Type getType() const {return m_type;}
        void setType(Type type) {m_type = type;}

        /** @brief get the decision of the player 
         * 
         * @pre the menu is displayed to the player.
        */
        std::string getDecision(sf::Vector2i mousePos) const;

    private:
        Type m_type;
        std::vector<Button> m_buttons;
};

std::string Menu::getDecision(sf::Vector2i mousePos) const{
    for(const Button& button : m_buttons){
        if(button.isClicked(mousePos)){
            return button.getName();
        }
    }
    return "";
}
