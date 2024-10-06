#pragma once

#include <string>
#include <vector>
#include "StreetTile.hpp"

// Forward declaration for StreetTile
class StreetTile;

class Player {
public:
    /** @brief Constructs a Player with a given name.
     *
     *  @param name The name of the player.
     */
    Player(const std::string& name);

    /** @brief Gets the current tile the player is on.
     *
     *  @return A pointer to the current StreetTile.
     */
    StreetTile* getStreetTile() const;

    /** @brief Sets the current tile the player is on.
     *
     *  @param tile A pointer to the new current StreetTile.
     */
    void setStreetTile(StreetTile* tile);

    /** @brief Checks if the player is currently in jail.
     *
     *  @return True if the player is in jail, false otherwise.
     */
    bool isInJail() const;

    /** @brief Sets the player's jail status.
     *
     *  @param inJail True if the player is in jail, false otherwise.
     */
    void setInJail(bool inJail);

    /** @brief Checks if the player owns any StreetTile properties.
     *
     *  @return True if the player owns at least one StreetTile, false otherwise.
     */
    bool hasStreetTile() const;

    /** @brief Gets the player's current amount of money.
     *
     *  @return The amount of money the player has.
     */
    unsigned int getMoney() const;

    /** @brief Deducts a specified amount of money from the player.
     *
     *  @param amount The amount to deduct.
     */
    void deductMoney(unsigned int amount);

    /** @brief Adds a specified amount of money to the player.
     *
     *  @param amount The amount to add.
     */
    void addMoney(unsigned int amount);

    /** @brief Gets the properties owned by the player.
     *
     *  @return A constant reference to a vector of StreetTile pointers.
     */
    const std::vector<StreetTile*>& getProperties() const;

    /** @brief Gets the player's name.
     *
     *  @return A constant reference to the player's name string.
     */
    const std::string& getName() const;

    /** @brief Adds a property to the player's list of owned properties.
     *
     *  @param property A pointer to the StreetTile to add.
     */
    void addProperty(StreetTile* property);

private:
    //* MEMBERS
    std::string m_name;                          ///< Name of the player.
    unsigned int m_money;                        ///< Amount of money the player has.
    StreetTile* m_currStreetTile;                            ///< The current tile the player is on.
    std::vector<StreetTile*> m_ownedStreetTiles;     ///< Properties owned by the player.
    bool m_inJail;                               ///< Jail status of the player.
};