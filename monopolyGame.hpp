#pragma once

#include <SFML/Graphics.hpp>
#include <cassert>

/** @class MonopolyGame
 * 
 * @brief Represents a Monopoly game board with edges and tiles.
 */
class MonopolyGame : public sf::Drawable, sf::Transformable{
    public: 
        MonopolyGame();
        
        /** @brief creates the game tiles. */
        void createTiles();

        void handleMouseClick(sf::Vector2i mousePos);
    
    private:
        /** @brief draws the game board. */
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        
        //* MEMBERS
        /** @brief All menus of the game */
        std::unordered_map<Menu::Type, Menu> m_menus;
        Menu m_currMenu; // need to impl Menu 3 moscetures: copy ctor, operator=, and a dtor.
        std::vector<std::shared_ptr<Player>> m_players;
        TableTextBox m_playersTable;
        std::shared_ptr<Player> m_currPlayer;
        ColoredTextBox m_currPlayerTextBox;
        unsigned int m_doublesCount = 0;
        Dice m_dice;
        unsigned int m_diceSum;
        Board m_board;
        sf::Font& m_font;
};

void MonopolyGame::createTiles(){
    m_board.createTiles();
}

void MonopolyGame::handleMouseClick(sf::Vector2i mousePos){

    // if the player clicked on something other than an active button, return.
    if(m_currMenu.getDecision(mousePos) == ""){
        return;
    }
    
    // if the button clicked is active, handle the click:

    // define usful variable:
    auto currTile = m_currPlayer->getTile();

    // things to consider:
    // 1. isThere a double? // keep as a member of the game
    // 2. is the player bunkrupt? // keep in player class
    // 3. is the player in jail? // keep the number of times left in jail in player class

    // info that need to move between the menus:
    // 1. number of doubles in a row
    // 2. the sum of the dice
    switch(m_currMenu.getType()){
        // the start of a normal turn: button to roll the dice
        case Menu::Type::RollDice:
            if(m_currMenu.getDecision(mousePos) == "Roll Dice"){
                // roll the dices
                unsigned int dice1 = m_dice.roll();
                unsigned int dice2 = m_dice.roll();
                // if the dice are equal, increment the doubles count
                if(dice1 == dice2){
                    m_doublesCount++;
                }else{ // dice1 != dice2, meaning it's not a double and we need to reset the doubles count to signal the player doesn't have another turn.
                    m_doublesCount = 0; // reset the doubles count
                } 

                // if the player had 3 doubles in a row, move him to jail
                if(m_doublesCount == 3){
                    // move player to jail NOW
                    m_currPlayer.setTile(/*Jail Tile Refference*/); // first: clear the m_landingPlayerName from curr tile and set it in the jail tile, second: set the player positon tile to the jail tile.
                    m_currPlayer.setInJain(); // bassically change a member of Player
                    m_doublesCount = 0;
                    setMenu(Menu::Type::EndTurn);
                }else{
                    m_diceSum = dice1 + dice2;
                    setMenu(Menu::Type::DiceInRoll);
                }
            }
        break;      
        // the presentation of the dice roll result:
        case Menu::Type::DiceInRoll:
            if(m_currMenu.getDecision(mousePos) == "Continue"){
                m_board.move(m_currPlayer, m_diceSum); // have to use the board.. can't use player data only. // first: clear the m_landingPlayerName from curr tile and set it in the new tile, second: set the player positon tile to new tile
                Menu::Type nextMenu = m_currPlayer->tile()->onLanding(m_currPlayer); // execute the imidite and un-initiated actions that start at landing and return the type of Menu to display next.
                //! need to impl now!!!! onlanding of StreetTile!
                // there is no tile that need to display the AffirmBuild menu after it, so no need to check whether to use setMenu(Menu::Type) or setMenu(Menu::Type, shared_ptr<StreetTile>)
                setMenu(nextMenu);
            }
        break;
        // present to the player that he is bunkrupt and have to end his turn.
        case Menu::PlayerBankrupt: // same as EndTurn only this displays "you are bunkrupt" and change the player accordingly
            if(m_currMenu->getDecition(mousePos) == "End Turn"){
                m_currPlayer.setBunkrupt();
                game.advanceTurn(); // change m_currPlayer and set the next menu according to this player state
                
                // set menu for next player:
                if(m_currPlayer.timesLeftInJail() > 0){
                    setMenu(Menu::Type::JailMenu);
                }else{
                    setMenu(Menu::Type::RollDice);
                }
            }
        break;
        // tell the player that his turn is over.
        case Menu::EndTurn:
            if(m_currMenu->getDecition(mousePos) == "End Turn"){
                game.advanceTurn(); // get the next not-bunkrupted player.
                // set menu for next player:
                if(m_currPlayer.timesLeftInJail() > 0){
                    setMenu(Menu::Type::JailMenu);
                }else{
                    setMenu(Menu::Type::RollDice);
                }
            }
        break;
        // present the player the option to buy the property he landed on.
        case Menu::Type::BuyMenu: // the buy menu have the curr tile saved in the game.
            // if the player can't buy the property
            // change nothing.
            if((currMenu.getDecition(mousePos) == "Buy" && currPlayer.getMoney() < currTile.getCost())){
                break;
            }
            // in this line of code we know that either 
            // 1. the player clicked "Don't Buy"
            // 2. or he clicked "Buy" and he has enough money.
            
            // if he click "Buy": make the Property his:
            if(currMenu.getDecition(mousePos) == "Buy" && currPlayer.getMoney()>=currTile.getCost()){
                currPlayer.deducteMoney(currTile.getCost());
                currTile.setOwner(m_currPlayer); // copying the shared_ptr
            }

            // wheter he bought or choose not to: continue to the next menus:
            setMenu(Menu::Type::PreEndTurn);
            break;
        //* building menus:
            // asks the player if he want to build (in general, not in a specific property)
            case Menu::Type::Want2Build:
                if(currMenu->getDecition(mousePos) == "Don't Build"){
                    if(m_doublesCount>0){ // we had double
                        setMenu(Menu::Type::RollDice);
                    }else{ // we didn't had double
                        setMenu(Menu::Type::EndTurn);
                    }
                }else if(currMenu->getDecition(mousePos) == "Build"){
                    setMenu(Menu::Type::ChooseBuild);
                }
            // let the player choose one of it's properties by selecting it on the board
            case Menu::Type::ChooseBuild:
                // get the *name* of the Property tile that the player Selected
                std::string optintialName = m_board.getTileSelected(mousePos, m_currPlayer);
                // if he didn't choose any of his property
                if (optintialName == ""){
                    // do nothing!
                }else{
                    std::shared_ptr<StreetTile> selectedStreetTile = m_board.getTileByName(potintialName);
                    // display the BuildMenu with the Build button and the details of the StreetTile
                    //  details to display: name, cost of house, cost of hotel, rent with each house.
                    setMenu(Menu::Type::AffirmBuild, selectedStreetTile); // display the AffirmBuild menu and the selectedTile detials.
                }
            // let the player affirm/cancel that he want to build in the selected property
            case Menu::Type::AffirmBuild:
                // if the player want to Build in the selected StreetTile:
                if(currMenu->getDecition(mousePos) == "Build"){
                    std::shared_ptr<StreetTile> selectedStreetTile = currMenu->getSelectedStreetTile();
                    // if: 
                    // player has money
                    // he has all the streets of the same color
                    // the current house number isn't high too much
                    if(selectedStreetTile.BuildCost() <= m_currPlayer.money() &&
                       m_board.hasAllStreets(m_currPlayer, selectedStreetTile.getColor()) &&
                       m_board.notTooMuchHouses(selectedStreetTile)){
                        // deduce from the player
                        m_currPlayer.deducteMoney(selectedStreetTile.BuildCost());
                        selectedStreetTile.upgradeBuild() // update the Building type enum.
                        // stay in this menu! in case player want to build more(it's *sometimes* possible for him)
                    }
                }else if(currMenu->getDecition(mousePos) == "Cancel"){
                    // return to the chooseBuild menu
                }
        //* special tiles:
        // shows the player the Tax he have to pay for the TaxTile he landed on
        case Menu::Type::Tax:
            if(currMenu->getDecition(mousePos) == "Pay"){
                assert(m_currPlayer.getMoney() >= currTile.getTax());
                m_currPlayer.deducteMoney(currTile.getTax());
                
                // standart end of turn:
                setMenu(Menu::Type::PreEndTurn);
            }
        break;
        // shows the player the details of the JailTile and the options to pay or wait
        case Menu::Type::JailMenu:
            // in this line we know that the player has at least one turn left in jail
            if(currMenu->getDecition(mousePos) == "Pay" && m_currPlayer.getMoney() >= 50){
                m_currPlayer.deducteMoney(50);
                m_currPlayer.setOutOfJail(); // set the player m_leftInJail to 0
                setMenu(Menu::Type::RollDice); // normal and free-of-jail dice roll
            }else if(currMenu->getDecition(mousePos) == "RollDices"){
                // roll the dices
                unsigned int dice1 = m_dice.roll();
                unsigned int dice2 = m_dice.roll();
                // if the dice are equal, get out of jail and move player
                if(dice1 == dice2){
                    m_currPlayer.setOutOfJail(); // set the player m_leftInJail to 0
                    
                setMenu(Menu::Type::JailDiceInRoll);
            }
        break;

        case Menu::Type::JailDiceInRoll:
            if(m_currMenu->getDecision(mousePos) == "Continue"){
                if(m_currPlayer.turnsLeftInJail() == 0){ // there was a double
                    // similir code as in the DiceInRoll case
                    m_board.move(m_currPlayer, m_diceSum); // have to use the board.. can't use player data only. // first: clear the m_landingPlayerName from curr tile and set it in the new tile, second: set the player positon tile to new tile
                    Menu::Type nextMenu = m_currPlayer->tile()->onLanding(m_currPlayer); // execute the imidite and un-initiated actions that start at landing and return the type of Menu to display next.
                    setMenu(nextMenu);
                    // end similir code
                }else if(m_currPlayer->turnsLeftInJail()>1){ // if there wasn't a double and the player still have time in jail
                    
                    setMenu(Menu::Type::EndTurn); 
                }
            }
        break;
    update();
}
//! now impl EndTurn.
// for setting all menus except AffirmBuild menu:
void setMenu(Menu::Type menuType){
    // Copy the menu template (no game info - only buttons)
    m_currMenu = m_menus[menuType]; // should work with map syntax
    
    // EndTurn, RollDice, PlayerBankrupt, Want2Build, JailMenu  won't execute any of the lines below
    
    // DiceInRoll, BuyMenu, chooseBuild, Tax, JailDiceInRoll will execute the lines below
    
    //* if the menu needs game info: modiy the m_currMenu withouth affection m_menus
    switch(menuType){
        case Menu::Type::DiceInRoll:
            // insert the dice sum to the menu
            m_currMenu.insertInfoTextBox("The sum of the dice is: " + std::to_string(m_diceSum));

        case Menu::Type::BuyMenu:
            // get the current tile
            shared_ptr<Tile> currTile = m_currPlayer->tile();

            // convert it to propertyTile to get PropertyTile functionallity
            shared_ptr<PropertyTile> propertyTile = std::dynamic_pointer_cast<PropertyTile>(currTile);
            
            // inserting the property details to the menu
            m_currMenu.insertInfoTextBox(propertyTile->getBuyTextBox());  // method of PropertyTile!
        
        case Menu::Type::chooseBuild: //! need to design the Menu for this to work!
            // get all the player's streets
            std::vector<shared_ptr<StreetTile>> playerStreets = m_board.getPlayerStreets(m_currPlayer);

            // insert the streets to the menu
            m_currMenu.insertInfoTextBox(playerStreets); // method of Menu! //! need to design the Menu for this to work!
        break;
        case Menu::Type::Tax:
            // get the current tile
            shared_ptr<Tile> currTile = m_currPlayer->tile();

            // convert it to TaxTile to get TaxTile functionallity
            shared_ptr<TaxTile> taxTile = std::dynamic_pointer_cast<TaxTile>(currTile);
            
            // inserting the tax details to the menu
            m_currMenu.insertInfoTextBox(taxTile->getTaxTextBox());  // method of TaxTile!
        break;
        case Menu::Type::JailDiceInRoll:
            // insert the dice sum to the menu
            m_currMenu.insertInfoTextBox("The sum of the dice is: " + std::to_string(m_diceSum));
        break;
        case Menu::Type::PreEndTurn:
            if(m_currPlayer->hasPro)
    }

}

// for setting the AffirmBuild menu (and maybe other future menus that need the info of a selected StreetTile)
void setMenu(Menu::Type menuType, shared_ptr<StreetTile> selectedStreetTile){
    switch(menuType){
        case Menu::Type::AffirmBuild:
            // set the new menu *template* (no game info - only buttons)
            m_currMenu = m_menus[menuType];

            // convert the selectedStreetTile to StreetTile to get its' functionallity
            shared_ptr<StreetTile> streetTile = std::dynamic_pointer_cast<StreetTile>(selectedStreetTile);

            // insert the Street detail to the menu:
            m_currMenu.insertInfoTextBox(streetTile->getBuildTextBox());
        break;
        // set defualt exceptions
        default:
            throw std::invalid_argument("menuType is not a known type for setMenu(Menu::Type, shared_ptr<StreetTile>) function!");        
    }
}

void MonopolyGame::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_board, states);
    target.draw(m_currMenu, states);
    target.draw(m_currPlayerTextBox, states); // i don't know what to draw the curr player
    target.draw(m_playersTable, states); // the table also prints if the player is bunkrupt
}

void MonopolyGame::startGame(){
    // create the game tiles
    createTiles();
    // set the first player
    m_currPlayer = m_players[0];
    // set the first menu
    setMenu(Menu::Type::RollDice);
}

void MonopolyGame::setPlayersNames(const std::vector<std::string>& names){
    for(const auto& name : names){
        m_players.push_back(std::make_shared<Player>(name));
    }
    // create the players table.
    // the table is a matrix of ColoredTextBox
    // it gets to it's ctor a FloatRect (that define it's place on the screen) and a font
    // and it enables to overwrite a line, by entering a vector of strings

}

// update the game state (e.g. player position, player money, player jail time, etc.)
void MonopolyGame::update(){
    // update the current player text box:
        m_currPlayerTextBox.setTexts({{m_currPlayer->getName(), Alignment::Center}});
    
    // update the players table:
        // initilize first line of the table
        std::vector<std::string> columnsLine = {"Player", "Money", "Position", "Jail Time"}; // position is the name of the tail the player is on.
        m_playersTable.setNumOfColumns(columnsLine.size());
        m_playersTable.insertLine(0, columnsLine); // insert the line as the 0'th line
        
        // insert the players data to the table
        for(unsigned int i=0; i<m_players.size(); i++){
            std::vector<std::string> playerData = {m_players[i]->getName(), std::to_string(m_players[i]->getMoney()), m_players[i]->getTile()->getName(), std::to_string(m_players[i]->timesLeftInJail())};
            m_playersTable.insertLine(i+1, playerData);
        }
        // the table will be drawn as defined in the Table class.
    
    // draw the curr menu:
        target.draw(m_currMenu, states); // m_currMenu updated in the setMenu function
    
}