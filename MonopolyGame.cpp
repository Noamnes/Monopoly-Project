#include "MonopolyGame.hpp"

MonopolyGame::MonopolyGame(const sf::Vector2u& windowSize, float cornersRatio, sf::Font& font)
    : m_board(windowSize.y, cornersRatio, font) 
    {
        // create the menus with the font. //! need to implement!

    }

//! UNCOMMENT
void MonopolyGame::setPlayersNames(std::vector<std::string> names){
    // clear the m_players vector
    m_players.clear(); //! UNCOMMENT

    // populate m_players with Player objects using the provided names
    for (const auto& name : names) { //! UNCOMMENT
        m_players.emplace_back(name);  //! UNCOMMENT 
    }                                //! UNCOMMENT
}

void MonopolyGame::startGame(){
    // set the current player to the first player
    m_currentPlayerIndex = 0; //! UNCOMMENT
    // set the menu to the first player menu
    // setMenu(Menu::Type::newTurn);  //! UNCOMMENT
}

void MonopolyGame::handleMouseClick(sf::Vector2i &mousePos){
    //! UNCOMMENT: all this functions' body
    // // check if the click is on a button(pressable textbox) on the current menu
    // std::string buttonPressed = m_currentMenu.getButtonName(mousePos);
    
    // // if no button was pressed - return:
    // if (buttonPressed == ""){
    //     return;
    // }
    
    // switch(m_currentMenu.getType()){
    //     // display the option to roll the dice: button is "Roll Dice"
    //     case Menu::Type::RollDice: // Implemented
    //         if (buttonPressed == "Roll Dice"){
    //             // roll the dice twice
    //             unsigned int dice1 = m_dice.roll();
    //             unsigned int dice2 = m_dice.roll();
                
    //             // if there is a double - increament the doubles count
    //             if (dice1 == dice2){
    //                 m_doublesCount++;
    //             } else { // if not - reset the doubles count
    //                 m_doublesCount = 0;
    //             }
                
    //             // if the player rolled 3 doubles - move him to jail
    //             if (m_doublesCount == 3){
    //                 // go to jail
    //                 setMenu(Menu::Type::Move2Jail); // moves the currernt player to the jail
    //                 m_doublesCount = 0;
    //             } else {
    //                 m_diceSum = dice1 + dice2;
    //                 setMenu(Menu::Type::DiceInRoll); // show the dice and the sum
    //             }
    //         }
    //     break;
    //     // display the dice sum: button is "Continue"
    //     case Menu::Type::DiceInRoll: // Implemented
    //         if (buttonPressed == "Continue"){
    //             // usfule variables
    //             auto currPlayer = m_players[m_currentPlayerIndex];
    //             auto currTile = currPlayer.getTile();
                
    //             // move the player:
    //             auto newTile = m_board.getTileAfterMove(currPlayer.getTile(), m_diceSum); // get the new tile reference //TODO:IMPLEMENT
    //             board.movePlayer(currPlayer, currTile, newTile); // move the m_landingPlayerName from the currTile to the newTile //TODO:IMPLEMENT
    //             currPlayer.setTile(newTile); // set the m_currentTile of the player to the newTile
                
    //             // get the menu of the new tile
    //             Menu::Type newMenu = newTile->onLanding(currPlayer); //TODO:IMPLEMENT

    //             // set the menu according to the landing tile
    //             setMenu(newMenu); //TODO:IMPLEMENT
    //         }
    //     break;
    //     // display that the player's turn has ended: button is "End Turn"
    //     case Menu::Type::EndTurn: // Implemented
    //         if (buttonPressed == "End Turn"){
    //             // continue to the next player
    //             m_currentPlayerIndex++;
    //             // set the menu for the next player
    //             setMenu(Menu::Type::newTurn);
    //         }
    //     break;
    //     // display the player the option to buy the PropertyTile he landed on: buttons are "Buy" and "Do Not Buy"
    //     case Menu::Type::BuyMenu: // Implemented
    //         // usefull variables:
    //         auto currPlayer = m_players[m_currentPlayerIndex];
    //         auto currTile = currPlayer.getTile();
    //         unsigned int price = currTile->getPrice();
            
    //         // if the player clicked "Buy" and has enough money
    //         if(buttonPressed == "Buy" && currPlayer.getMoney() >= price){ 
    //             // deduct the price of the tile from the player
    //             currPlayer.deductMoney(price);
    //             // make the player the owner of the tile
    //             acquireTile(currPlayer, currTile); // change tile members and player members //TODO:IMPLEMENT
    //             // set PreEndTurn menu
    //             setMenu(Menu::Type::PreEndTurn); 
    //         }else if(buttonPressed == "Do Not Buy"){
    //             setMenu(Menu::Type::PreEndTurn);
    //         }
    //     break;
    //     //Building menus:
    //     // display the option to bulid in the player's properties, buttons are "Build" and "Do Not Build"
    //     case Menu::Type::Want2Build: // Implemented
    //         if(buttonPressed == "Build"){
    //             setMenu(Menu::Type::ChooseBuild);
    //         }else if(buttonPressed == "Do Not Build"){
    //             // END TURN:
    //             if(m_doublesCount > 0){ 
    //                 setMenu(Menu::Type::RollDice);
    //             }else{ // if he did not rolled a double
    //                 setMenu(Menu::Type::EndTurn);
    //             }
    //         }
    //     break;
    //     // display the StreetTiles of the player so he can build on them, buttons are "Cancel" and all the StreetTiles of the player(displayed as a row in the menu)
    //     case Menu::Type::ChooseBuild: // Implemented
    //         // if the player regreted and choose not to build:
    //         if(buttonPressed == "Cancel"){
    //             // END TURN:
    //             if(m_doublesCount > 0){ 
    //                 setMenu(Menu::Type::RollDice);
    //             }else{ // if he did not rolled a double
    //                 setMenu(Menu::Type::EndTurn);
    //             }
    //         }else{ 
    //             // check what StreetTile the player chose to build on
    //             properties = currPlayer.getProperties() //TODO:IMPLEMENT
                
    //             // check if one of the properties has that name
    //             for(auto& property : properties){
    //                 if(property.getName() == buttonPressed){
    //                     // convert the property to StreetTile
    //                     StreetTile* streetTile = dynamic_cast<StreetTile*>(property);
    //                     // display the menu to affirm the PropertyTile to build on, and send the property selected
    //                     setMenu(Menu::Type::AffirmBuild, streetTile);
    //                 }
    //             }   
    //             // if the buttonPressed is not a property name and not "Cancel" - an error accured
    //             throw std::invalid_argument("The buttonPressed is not a property name and not 'Cancel'");
    //         }
    //     break;
    //     // display the player is bunkrupt and his game is over: button is "End Game"
    //     case Menu::Type::PlayerBunkrupt:
    //         if(buttonPressed == "End Game"){
                
    //         }
    // }
}

void MonopolyGame::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    // draw the board(before the menu)
    target.draw(m_board, states);
    // draw the current menu
    // target.draw(m_currentMenu, states); //! UNCOMMENT
    // draw the players info table
    //TODO:IMPLEMENT
    // draw the current player name
    //TODO:IMPLEMENT
}

//! UNCOMMENT
// void MonopolyGame::setMenu(Menu::Type menuType){
//     m_currentMenu = m_menus[menuType];

//     // only if the menu need to display/update the game info the lines below should execute
//         // if the menu need to update the game info - update the game info
//         // if the menu need to display the game info - insert the game info into it
    
    // switch(menuType){
//         // displayable menus:
//             Menu::Type::DiceInRoll:
//                 m_currentMenu.addTextBox("Dice sum: " + std::to_string(m_diceSum)); // add the dice sum to the menu, //? not sure if to insert vector of string or just a string
//             break;
//             Menu::Type::BuyMenu: // Implemented
//                 // usefull variables:
//                 auto currPlayer = m_players[m_currentPlayerIndex];
//                 auto currTile = currPlayer.getTile();
//                 // create the textBox to display the buy info
//                 TextBox buyInfo = getBuyInfo(currTile); //TODO:IMPLEMENT
//                 // add the textBox to the menu
//                 m_currentMenu.addTextBox(buyInfo);
//         // non-displayable menus: (have to setMenu at their end)
//             // move the player to jail without any display and advance setMenu(newTurn)
//             Menu::Type::Move2Jail:
//                 auto currPlayer = m_players[m_currentPlayerIndex];
//                 // move the player to the jail
//                 board.movePlayerToJail(currPlayer); // set the m_landing player of the source and the jail according to the player
//                 // get the jail tile
//                 auto jailTile = board.getJailTile();
//                 // set the m_currentTile of the player to the jail
//                 currPlayer.setTile(jailTile);
//                 // advance to the next player
//                 m_currentPlayerIndex++;
//                 // set next player menu:
//                 setMenu(Menu::Type::newTurn);
//             break;
//             // set the menu of a new turn according to the game state(player in-jail/free)
//             Menu::Type::newTurn:
//                 auto currPlayer = m_players[m_currentPlayerIndex];
//                 // if the player is in jail - set the menu to the jail menu
//                 if (currPlayer.isInJail()){
//                     setMenu(Menu::Type::JailMenu);
//                 } else {
//                     setMenu(Menu::Type::RollDice);
//                 }
//             break;
//             // route to the Menu that sould be displayed to the player before the EndTurn menu
//             Menu::Type::PreEndTurn:
                
//                 auto currPlayer = m_players[m_currentPlayerIndex];
                
//                 // if the player has a StreetTile in his possestion - let him build on it
//                 if(currPlayer.hasStreetTile()){ //note, this condition can be checking in the player OR in the board. currently i'll implement it in the player class
//                     setMenu(Menu::Type::Want2Build); //! Want2Build must NOT direct to this menu!! it would cause a circular route
//                 }else if(m_doublesCount > 0){ // if the player rolled a double
//                     setMenu(Menu::Type::RollDice);
//                 }else{ // if the player doesn't have StreetTiles
//                     setMenu(Menu::Type::EndTurn);
//                 }
        
//     }
// }


// for setting the AffirmBuild menu (and maybe other future menus that need the info of a selected StreetTile)
//! UNCOMMENT
// void MonopolyGame::setMenu(Menu::Type menuType, StreetTile* streetTile){
//     m_currentMenu = m_menus[menuType];

//     switch(menuType){
//         case Menu::Type::AffirmBuild:
//             // insert the property details into the menu
//             // first, create the text box:
//             TextBox buildInfo = getBuildInfo(streetTile); // create a text box with the Build info to display //TODO:IMPLEMENT
//             m_currentMenu.addTextBox(buildInfo);
//         break;
//         // set defualt exceptions
//         default:
//             throw std::invalid_argument("menuType is not a known type for setMenu(Menu::Type, shared_ptr<StreetTile>) function!");   
// }
    
