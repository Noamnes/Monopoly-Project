#pragma once

#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "TextBox.hpp"

class Player;  // Forward declaration for Player class

/** @class StreetTile
 *  @brief Represents a tile on the game street with properties like name, price, owner, and buildings.
 *
 *  The StreetTile class encapsulates the visual and logical aspects of a street tile, including
 *  ownership, building types, and directional text display.
 */
class StreetTile : public sf::Drawable, public sf::Transformable {
public:
    /** @enum ReadingDirection
     *  @brief Enumerates the possible text reading directions for the StreetTile.
     */
    enum class ReadingDirection { Up, Down, Left, Right };

    /** @enum BuildingType
     *  @brief Enumerates the types of buildings that can exist on a StreetTile.
     */
    enum class BuildingType { None, OneHouse, TwoHouses, ThreeHouses, FourHouses, Hotel };

    /** @brief Constructs a StreetTile with specified properties.
     *
     *  @param name The name of the street.
     *  @param price The price of the street.
     *  @param font The font used for displaying text.
     *  @param direction The initial reading direction for text (default is Up).
     *  @param stripColor The color of the owner stripe (default is Blue).
     */
    StreetTile(const std::string& name, unsigned int price, sf::Font& font,
               ReadingDirection direction = ReadingDirection::Up, sf::Color stripColor = sf::Color::Blue);

    /** @brief Executes actions when a player lands on the tile and returns the next menu to display.
     *
     *  @param player The player landing on the tile.
     *  @return The type of the next menu to display.
     */
    // Menu::Type onLanding(Player& player); //! UNCOMMENT

    //* Getters & Setters
    // m_name
    std::string getName() const;
    void setName(const std::string& name);
    // m_landingPlayerName
    std::string getLandingPlayerName() const;
    void setLandingPlayerName(const std::string& landingPlayerName);
    // m_readingDirection
    ReadingDirection getReadingDirection() const;
    void setReadingDirection(ReadingDirection readingDirection);
    // m_bounds
    sf::FloatRect getBounds() const;
    void setBounds(const sf::FloatRect& bounds);
    // m_price
    unsigned int getPrice() const;
    void setPrice(unsigned int price);
    // m_owner
    Player* getOwner() const;
    void setOwner(Player* owner);

    /** @brief Sets the background fill color of the main text box.
     *
     *  @param color The color to set as the background.
     */
    void setMainFillColor(const sf::Color& color);

    /** @brief Sets the fill color of the owner color strip.
     *
     *  @param color The color to set for the strip.
     */
    void setColorStripFillColor(const sf::Color& color);

    /** @brief Sets the building type on the StreetTile and updates the text display.
     *
     *  @param buildingType The type of building to set.
     */
    void setBuildingType(BuildingType buildingType);

    /** @brief Sets the percentage size of the owner stripe.
     *
     *  @param percentage The percentage size to set for the owner stripe.
     */
    void setOwnerStripePercentage(float percentage);

    /** @brief Calculates the rent of the property.
     *
     *  @return The rent amount.
     */
    unsigned int calcRent();

private:
    /** @brief Adjusts the graphical components of the tile according to the data contained in the tile.
     *
     *  This function should be called right after a change to the data has accured.
     */
    void adjustAllComponents();

    /** @brief Converts ReadingDirection to TextBox::TextDirection.
     *
     *  @param direction The reading direction to convert.
     *  @return The corresponding TextDirection.
     */
    TextBox::TextDirection getTextBoxDirection(ReadingDirection direction);

    /** @brief Adjusts the position and size of the color strip. */
    void adjustColorStrip();

    /** @brief Adjusts the bounds of the main text box based on the reading direction. */
    void adjustMainTextBoxBounds();

    /** @brief Adjusts the owner text box layout and content. */
    void adjustOwnerTextBox();

    /** @brief Updates the main text box content based on the current state. */
    void updateTextBox();

    /** @brief Updates the owner text box content. */
    void updateOwnerTextBox();

    /** @brief Draws the StreetTile components to the render target.
     *
     *  @param target The render target to draw to.
     *  @param states The current render states.
     */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    //* MEMBERS
    // From Tile
    std::string m_name;                   ///< Name of the street.
    std::string m_landingPlayerName;      ///< Name of the player landing on the tile.
    sf::Font& m_font;                     ///< Font used for displaying text.
    sf::FloatRect m_bounds;               ///< The bounds of the tile.
    ReadingDirection m_readingDirection;  ///< Current text reading direction.

    // From PropertyTile
    unsigned int m_price;                 ///< Price of the street.
    Player* m_owner;                      ///< The owner of the street tile.

    // Specific to StreetTile
    float m_colorStripThickness;          ///< Thickness of the color strip.
    float m_ownerStripThickness;          ///< Thickness of the owner strip.
    float m_ownerStripePercentage;        ///< Percentage size of the owner stripe.

    TextBox m_mainTextBox;         ///< The main text box displaying tile information.
    sf::RectangleShape m_colorStrip;      ///< The colored strip indicating property color.
    TextBox m_ownerTextBox;        ///< The text box displaying the owner's name.

    BuildingType m_buildingType;          ///< Current building type on the street.

    // Rent prices
    unsigned int m_basicRent;
    unsigned int m_oneHouseRent;
    unsigned int m_hotelRent;
};