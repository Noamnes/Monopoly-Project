#pragma once
// create a player class with name
#include <string>
#include "Tile.hpp"

class Player{
    public:
        Player(std::string name): name(name){}
        std::string getName() const {return name;}
        shared_ptr<Tile> getTile() const {return tile;}
        void setTile(shared_ptr<Tile> tile) { m_tile = tile;}
        void setInJain() {m_turnsLeftInJail = 3;}
        unsigned int getMoneyAmount();
    private:
        //* MEMBERS
        std::string m_name;
        shared_ptr<Tile> m_tile;
        unsigned int m_money;
        unsigned int m_turnsLeftInJail;
};