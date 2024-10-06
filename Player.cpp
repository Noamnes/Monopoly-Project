#include "Player.hpp"

Player::Player(const std::string& name)
    : m_name(name), m_money(1500), m_currStreetTile(nullptr), m_inJail(false)
{
}

StreetTile* Player::getStreetTile() const
{
    return m_currStreetTile;
}

void Player::setStreetTile(StreetTile* tile)
{
    m_currStreetTile = tile;
}

bool Player::isInJail() const
{
    return m_inJail;
}

void Player::setInJail(bool inJail)
{
    m_inJail = inJail;
}

bool Player::hasStreetTile() const
{

    if (m_ownedStreetTiles.empty())
    {
        return false;
    }
    return true;
}

unsigned int Player::getMoney() const
{
    return m_money;
}

void Player::deductMoney(unsigned int amount)
{
    if (amount >= m_money)
    {
        m_money = 0;
        // Handle bankruptcy if necessary
    }
    else
    {
        m_money -= amount;
    }
}

void Player::addMoney(unsigned int amount)
{
    m_money += amount;
}

const std::vector<StreetTile*>& Player::getProperties() const
{
    return m_ownedStreetTiles;
}

const std::string& Player::getName() const
{
    return m_name;
}

void Player::addProperty(StreetTile* property)
{
    m_ownedStreetTiles.push_back(property);
}
