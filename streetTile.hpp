#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <memory> // For smart pointers
#include "player.hpp"
#include "coloredTextBox.hpp"
#include "menu.hpp"

/** @class StreetTile
 *  @brief Represents a tile on the game street with properties like name, price, owner, and buildings.
 *
 *  The StreetTile class inherits from sf::Drawable and encapsulates the visual and logical
 *  aspects of a street tile, including ownership, building types, and directional text display.
 */
class StreetTile : public sf::Drawable, PropertyTile
{
public:
    /** @enum BuildingType
     *  @brief Enumerates the types of buildings that can exist on a StreetTile.
     */
    enum class BuildingType { None, OneHouse, TwoHouses, ThreeHouses, FourHouses, Hotel };

    /** @enum ReadingDirection
     *  @brief Enumerates the possible text reading directions for the StreetTile.
     */
    enum class ReadingDirection { Up, Down, Left, Right };

    /** @brief Constructs a StreetTile with specified properties.
     *
     *  @param bounds The rectangular bounds of the tile.
     *  @param name The name of the street.
     *  @param price The price of the street.
     *  @param font The font used for displaying text.
     *  @param direction The initial reading direction for text.(default is Up)
     *  @param stripColor The color of the owner stripe.(defualt is Blue)
     */
    StreetTile(const std::string& name, unsigned int price, const sf::Font& font,
               ReadingDirection direction = ReadingDirection::Up, sf::Color stripColor = sf::Color::Blue);

    /** @brief Sets the owner of the StreetTile.
     *
     *  @param owner A shared pointer to the Player who owns the tile.
     */
    void setOwner(std::shared_ptr<Player> owner);

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

    /** @brief Sets the text reading direction and adjusts component layouts accordingly.
     *
     *  @param direction The new reading direction for text.
     */
    void setReadingDirection(ReadingDirection direction);

    /** @brief Sets the percentage size of the owner stripe.
     *
     *  @param percentage The percentage size to set for the owner stripe.
     */
    void setOwnerStripePercentage(float percentage);

    /** @brief Sets the bounds of the StreetTile and adjusts components accordingly.
     *
     *  @param bounds The new rectangular bounds of the tile.
     */
    void setBounds(const sf::FloatRect& bounds);

    /** @brief execute the imidite and un-initiated actions that start at landing and return the type of Menu to display next */
    Menu::Type onLanding(shared_ptr<Player> player) override;

private:
    /** @brief Converts ReadingDirection to ColoredTextBox::TextDirection.
     *
     *  @param direction The reading direction to convert.
     *  @return The corresponding TextDirection.
     */
    ColoredTextBox::TextDirection getTextBoxDirection(ReadingDirection direction);

    /** @brief Adjusts the layout of all components based on the current reading direction and ownership. */
    void adjustComponents();

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

    unsigned int calcRent();

    // MEMBERS
    sf::FloatRect m_bounds;                      ///< The bounds of the tile.
    float m_colorStripThickness;                 ///< Thickness of the color strip.
    float m_ownerStripThickness;                 ///< Thickness of the owner strip.
    float m_ownerStripePercentage;               ///< Percentage size of the owner stripe.

    ColoredTextBox m_mainTextBox;                ///< The main text box displaying tile information.
    sf::RectangleShape m_colorStrip;             ///< The colored strip indicating ownership.
    ColoredTextBox m_ownerTextBox;               ///< The text box displaying the owner's name.

    std::string m_name;                          ///< Name of the street.
    unsigned int m_price;                        ///< Price of the street.
    BuildingType m_buildingType;                 ///< Current building type on the street.
    ReadingDirection m_readingDirection;         ///< Current text reading direction.

    // rent prices:
    unsigned int m_basicRent;
    unsigned int m_oneHouseRent;
    unsigned int m_hotelRent;

    std::shared_ptr<Player> m_owner;             ///< The owner of the street tile.
    const sf::Font& m_font;                      ///< Font used for displaying text.
};

// ================= Implementation =================

/** @brief Constructs a StreetTile with specified properties. */
StreetTile::StreetTile(const std::string& name, unsigned int price, const sf::Font& font,
                       ReadingDirection direction, sf::Color stripColor)
    : m_bounds(sf::FloatRect()), m_name(name), m_price(price), m_buildingType(BuildingType::None),
      m_readingDirection(direction), m_font(font), m_owner(nullptr),
      m_ownerStripePercentage(0.1f), // Default owner stripe percentage
      m_mainTextBox(m_bounds), // Initialize m_mainTextBox with bounds
      m_ownerTextBox(sf::FloatRect()) // Initialize m_ownerTextBox with default bounds
{
    // Initialize the main colored text box
    m_mainTextBox.setBackgroundColor(sf::Color::White);
    m_mainTextBox.setOutlineColor(sf::Color::Black);
    m_mainTextBox.setOutlineThickness(1.f);
    m_mainTextBox.setTextDirection(getTextBoxDirection(direction));

    // Initialize the color strip
    m_colorStrip.setFillColor(stripColor);

    // Update components based on the reading direction
    adjustComponents();
}

/** @brief Sets the owner of the StreetTile. */
void StreetTile::setOwner(std::shared_ptr<Player> owner)
{
    m_owner = owner;
    adjustComponents();
}

/** @brief Sets the background fill color of the main text box. */
void StreetTile::setMainFillColor(const sf::Color& color)
{
    m_mainTextBox.setBackgroundColor(color);
}

/** @brief Sets the fill color of the owner color strip. */
void StreetTile::setColorStripFillColor(const sf::Color& color)
{
    m_colorStrip.setFillColor(color);
}

/** @brief Sets the building type on the StreetTile and updates the text display. */
void StreetTile::setBuildingType(BuildingType buildingType)
{
    m_buildingType = buildingType;
    updateTextBox();
}

/** @brief Sets the text reading direction and adjusts component layouts accordingly. */
void StreetTile::setReadingDirection(ReadingDirection direction)
{
    m_readingDirection = direction;
    m_mainTextBox.setTextDirection(getTextBoxDirection(direction));
    adjustComponents();
}

/** @brief Converts ReadingDirection to ColoredTextBox::TextDirection. */
ColoredTextBox::TextDirection StreetTile::getTextBoxDirection(ReadingDirection direction)
{
    switch (direction)
    {
    case ReadingDirection::Up: return ColoredTextBox::TextDirection::Up;
    case ReadingDirection::Down: return ColoredTextBox::TextDirection::Down;
    case ReadingDirection::Left: return ColoredTextBox::TextDirection::Left;
    case ReadingDirection::Right: return ColoredTextBox::TextDirection::Right;
    default: return ColoredTextBox::TextDirection::Up;
    }
}

/** @brief Adjusts the layout of all components based on the current reading direction and ownership. */
void StreetTile::adjustComponents()
{
    // Update the TextBox content
    updateTextBox();
    updateOwnerTextBox();

    // Adjust the positions and sizes based on the reading direction
    // Calculate the thicknesses
    if (m_readingDirection == ReadingDirection::Up || m_readingDirection == ReadingDirection::Down)
    {
        m_colorStripThickness = m_bounds.height * 0.15f;
        m_ownerStripThickness = m_bounds.height * m_ownerStripePercentage;
    }
    else // Left or Right
    {
        m_colorStripThickness = m_bounds.width * 0.15f;
        m_ownerStripThickness = m_bounds.width * m_ownerStripePercentage;
    }

    // Adjust the color strip position and size
    adjustColorStrip();

    // Adjust the main text box bounds
    adjustMainTextBoxBounds();

    // Adjust the owner text box if there is an owner
    if (m_owner)
    {
        adjustOwnerTextBox();
    }
}

/** @brief Adjusts the position and size of the color strip. */
void StreetTile::adjustColorStrip()
{
    switch (m_readingDirection)
    {
    case ReadingDirection::Up:
        m_colorStrip.setPosition(m_bounds.left, m_bounds.top);
        m_colorStrip.setSize(sf::Vector2f(m_bounds.width, m_colorStripThickness));
        break;
    case ReadingDirection::Down:
        m_colorStrip.setPosition(m_bounds.left, m_bounds.top + m_bounds.height - m_colorStripThickness);
        m_colorStrip.setSize(sf::Vector2f(m_bounds.width, m_colorStripThickness));
        break;
    case ReadingDirection::Left:
        // Color strip on the right
        m_colorStrip.setPosition(m_bounds.left + m_bounds.width - m_colorStripThickness, m_bounds.top);
        m_colorStrip.setSize(sf::Vector2f(m_colorStripThickness, m_bounds.height));
        break;
    case ReadingDirection::Right:
        // Color strip on the left
        m_colorStrip.setPosition(m_bounds.left, m_bounds.top);
        m_colorStrip.setSize(sf::Vector2f(m_colorStripThickness, m_bounds.height));
        break;
    }
}

/** @brief Adjusts the bounds of the main text box based on the reading direction. */
void StreetTile::adjustMainTextBoxBounds()
{
    sf::FloatRect textBoxBounds;

    switch (m_readingDirection)
    {
    case ReadingDirection::Up:
        textBoxBounds = sf::FloatRect(
            m_bounds.left,
            m_bounds.top + m_colorStripThickness,
            m_bounds.width,
            m_bounds.height - m_colorStripThickness);
        break;
    case ReadingDirection::Down:
        textBoxBounds = sf::FloatRect(
            m_bounds.left,
            m_bounds.top,
            m_bounds.width,
            m_bounds.height - m_colorStripThickness);
        break;
    case ReadingDirection::Left:
        textBoxBounds = sf::FloatRect(
            m_bounds.left,
            m_bounds.top,
            m_bounds.width - m_colorStripThickness,
            m_bounds.height);
        break;
    case ReadingDirection::Right:
        textBoxBounds = sf::FloatRect(
            m_bounds.left + m_colorStripThickness,
            m_bounds.top,
            m_bounds.width - m_colorStripThickness,
            m_bounds.height);
        break;
    }

    m_mainTextBox.setBounds(textBoxBounds);
}

/** @brief Adjusts the owner text box layout and content. */
void StreetTile::adjustOwnerTextBox()
{
    sf::FloatRect ownerTextBoxBounds;

    switch (m_readingDirection)
    {
    case ReadingDirection::Up:
        ownerTextBoxBounds = sf::FloatRect(
            m_bounds.left,
            m_bounds.top - m_ownerStripThickness,
            m_bounds.width,
            m_ownerStripThickness);
        break;
    case ReadingDirection::Down:
        ownerTextBoxBounds = sf::FloatRect(
            m_bounds.left,
            m_bounds.top + m_bounds.height,
            m_bounds.width,
            m_ownerStripThickness);
        break;
    case ReadingDirection::Left:
        // Owner strip on the right
        ownerTextBoxBounds = sf::FloatRect(
            m_bounds.left + m_bounds.width,
            m_bounds.top,
            m_ownerStripThickness,
            m_bounds.height);
        break;
    case ReadingDirection::Right:
        // Owner strip on the left
        ownerTextBoxBounds = sf::FloatRect(
            m_bounds.left - m_ownerStripThickness,
            m_bounds.top,
            m_ownerStripThickness,
            m_bounds.height);
        break;
    }

    m_ownerTextBox.setBounds(ownerTextBoxBounds);
    m_ownerTextBox.setTextDirection(getTextBoxDirection(m_readingDirection));

    // Set background color and outline
    m_ownerTextBox.setBackgroundColor(sf::Color(173, 216, 230)); // Light blue
    m_ownerTextBox.setOutlineColor(sf::Color::Black);
    m_ownerTextBox.setOutlineThickness(1.f);

    // Update owner text content
    sf::Text ownerText;
    ownerText.setFont(m_font);
    ownerText.setString(m_owner->getName()); // Assuming Player has getName() method
    ownerText.setFillColor(sf::Color::Black);
    ownerText.setCharacterSize(20); // Placeholder size

    m_ownerTextBox.setTexts({ { ownerText, ColoredTextBox::Alignment::Center } });
}

/** @brief Updates the main text box content based on the current state. 
 * 
 * assumes m_mainTextBox has the right ReadingDirection
*/
void StreetTile::updateTextBox()
{
    // Clear existing texts
    m_mainTextBox.setTexts({});

    std::vector<std::pair<sf::Text, ColoredTextBox::Alignment>> texts;

    // Create sf::Text for name if not empty
    if (!m_name.empty())
    {
        sf::Text nameText;
        nameText.setFont(m_font);
        nameText.setString(m_name);
        nameText.setFillColor(sf::Color::Black);
        nameText.setCharacterSize(30); // Placeholder size

        texts.emplace_back(std::make_pair(nameText, ColoredTextBox::Alignment::Center));
    }

    // Create sf::Text for price if greater than zero
    if (m_price > 0)
    {
        sf::Text priceText;
        priceText.setFont(m_font);
        priceText.setString("$" + std::to_string(m_price));
        priceText.setFillColor(sf::Color::Black);
        priceText.setCharacterSize(30); // Placeholder size

        texts.emplace_back(std::make_pair(priceText, ColoredTextBox::Alignment::Center));
    }

    // Add house/hotel information if applicable
    if (m_buildingType != BuildingType::None)
    {
        sf::Text buildingText;
        buildingText.setFont(m_font);
        buildingText.setFillColor(sf::Color::Black);
        buildingText.setCharacterSize(30);

        if (m_buildingType == BuildingType::Hotel)
        {
            buildingText.setString("Hotel");
        }
        else
        {
            int houseNumber = 0;
            switch (m_buildingType)
            {
            case BuildingType::OneHouse:    houseNumber = 1; break;
            case BuildingType::TwoHouses:   houseNumber = 2; break;
            case BuildingType::ThreeHouses: houseNumber = 3; break;
            case BuildingType::FourHouses:  houseNumber = 4; break;
            default: break;
            }
            buildingText.setString("Houses num: " + std::to_string(houseNumber));
        }

        texts.emplace_back(std::make_pair(buildingText, ColoredTextBox::Alignment::Center));
    }

    // Set texts to main TextBox
    m_mainTextBox.setTexts(texts); // assumes m_mainTextBox has the right ReadingDirection
}

/** @brief Updates the owner text box content. */
void StreetTile::updateOwnerTextBox()
{
    if (!m_owner)
    {
        // Clear owner text box if no owner (to avoid storing redundant data)
        m_ownerTextBox.setTexts({});
        return;
    }

    // Owner text is set in *adjust*OwnerTextBox()
}

/** @brief Draws the StreetTile components to the render target. */
void StreetTile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Draw the owner text box if there is an owner
    if (m_owner)
    {
        target.draw(m_ownerTextBox, states);
    }

    // Draw the main text box (includes background and texts)
    target.draw(m_mainTextBox, states);

    // Draw the color strip
    target.draw(m_colorStrip, states);
}

inline unsigned int StreetTile::calcRent()
{
    switch (m_buildingType){
        case BuildingType::None: return m_basicRent;
        case BuildingType::OneHouse: return m_oneHouseRent;
        case BuildingType::TwoHouses: return m_oneHouseRent*2;
        case BuildingType::ThreeHouses: return m_oneHouseRent*pow(2, 2);
        case BuildingType::FourHouses: return m_oneHouseRent*pow(2, 3);
        case BuildingType::Hotel : return m_hotelRent;
    }
    return 0;
}

/** @brief Sets the percentage size of the owner stripe. */
void StreetTile::setOwnerStripePercentage(float percentage)
{
    m_ownerStripePercentage = percentage;
    adjustComponents();
}

/** @brief Sets the bounds of the StreetTile and adjusts components accordingly. */
void StreetTile::setBounds(const sf::FloatRect& bounds)
{
    m_bounds = bounds;
    adjustComponents();
}

/** @brief execute the imidite and un-initiated actions that start at landing and return the type of Menu to display next */
Menu::Type StreetTile::onLanding(shared_ptr<Player> player)
{
    // if the streetTile is un-owned, enable the player to buy it.
    if(m_owner == nullptr){
        return Menu::Type::BuyMenu;
    }else if(m_owner != player){ // if the tile is owned by other player, deducte money, and move straight to the end-of-turn menus, DO NOT SHOW A MENU
        unsigned int rent = calcRent();
        // if the player has enough money for rent:
        if(player->getMoneyAmount() >= rent){ // calc Rent based on number of houses
            player->deducteMoney(rent); // deducte from landing player
            m_owner->addMoney(rent); // add to owner
        }
        return Menu::Type::PreEndTurn;
    }
    return ;
}
