#include "StreetTile.hpp"

// Constructor
StreetTile::StreetTile(const std::string& name, unsigned int price, sf::Font& font,
                       ReadingDirection direction, sf::Color stripColor)
    : m_name(name), m_price(price), m_font(font), m_readingDirection(direction),
      m_owner(nullptr), m_buildingType(BuildingType::None),
      m_ownerStripePercentage(0.1f), // Default owner stripe percentage
      m_mainTextBox(sf::FloatRect()), // Initialize m_mainTextBox with bounds
      m_ownerTextBox(sf::FloatRect()) // Initialize m_ownerTextBox with default bounds
{
    // Initialize the main colored text box
    m_mainTextBox.setBackgroundColor(sf::Color::White);
    m_mainTextBox.setOutlineColor(sf::Color::Black);
    m_mainTextBox.setOutlineThickness(1.f);
    m_mainTextBox.setTextDirection(getTextBoxDirection(direction));

    // Initialize the color strip
    m_colorStrip.setFillColor(stripColor);

    // Initialize rents (example values)
    m_basicRent = 50;
    m_oneHouseRent = 100;
    m_hotelRent = 200;

    // update the graphical components
    adjustAllComponents();
}

// Getters & Setters
std::string StreetTile::getName() const {
    return m_name;
}

void StreetTile::setName(const std::string& name) {
    m_name = name;
    // update the graphical components
    adjustAllComponents();
}

std::string StreetTile::getLandingPlayerName() const {
    return m_landingPlayerName;
}

void StreetTile::setLandingPlayerName(const std::string& landingPlayerName) {
    m_landingPlayerName = landingPlayerName;
    // update the graphical components
    adjustAllComponents();
}

StreetTile::ReadingDirection StreetTile::getReadingDirection() const {
    return m_readingDirection;
}

void StreetTile::setReadingDirection(ReadingDirection readingDirection) {
    m_readingDirection = readingDirection;
    // update the graphical components
    adjustAllComponents();
}

sf::FloatRect StreetTile::getBounds() const {
    return m_bounds;
}

void StreetTile::setBounds(const sf::FloatRect& bounds) {
    m_bounds = bounds;
    // update the graphical components
    adjustAllComponents();
}

unsigned int StreetTile::getPrice() const {
    return m_price;
}

void StreetTile::setPrice(unsigned int price) {
    m_price = price;
    // update the graphical components
    adjustAllComponents();
}

Player* StreetTile::getOwner() const {
    return m_owner;
}

void StreetTile::setOwner(Player* owner) {
    m_owner = owner;
    // update the graphical components
    adjustAllComponents();
}

// StreetTile specific methods
void StreetTile::setMainFillColor(const sf::Color& color) {
    m_mainTextBox.setBackgroundColor(color);
}

void StreetTile::setColorStripFillColor(const sf::Color& color) {
    m_colorStrip.setFillColor(color);
}

void StreetTile::setBuildingType(BuildingType buildingType) {
    m_buildingType = buildingType;
    // update the graphical components
    adjustAllComponents();
}

void StreetTile::setOwnerStripePercentage(float percentage) {
    m_ownerStripePercentage = percentage;
    // update the graphical components
    adjustAllComponents();
}

unsigned int StreetTile::calcRent() {
    switch (m_buildingType) {
    case BuildingType::None: return m_basicRent;
    case BuildingType::OneHouse: return m_oneHouseRent;
    case BuildingType::TwoHouses: return m_oneHouseRent * 2;
    case BuildingType::ThreeHouses: return m_oneHouseRent * 4;
    case BuildingType::FourHouses: return m_oneHouseRent * 8;
    case BuildingType::Hotel: return m_hotelRent;
    default: return 0;
    }
}

void StreetTile::adjustAllComponents() {
    // Update the TextBox content
    m_mainTextBox.setTextDirection(getTextBoxDirection(m_readingDirection));
    updateTextBox();
    updateOwnerTextBox();

    // Calculate the thicknesses
    if (m_readingDirection == ReadingDirection::Up || m_readingDirection == ReadingDirection::Down) {
        m_colorStripThickness = m_bounds.height * 0.15f;
        m_ownerStripThickness = m_bounds.height * m_ownerStripePercentage;
    } else {
        m_colorStripThickness = m_bounds.width * 0.15f;
        m_ownerStripThickness = m_bounds.width * m_ownerStripePercentage;
    }

    // Adjust the color strip position and size
    adjustColorStrip();

    // Adjust the main text box bounds
    adjustMainTextBoxBounds();

    // Adjust the owner text box if there is an owner
    if (m_owner) {
        adjustOwnerTextBox();
    }
}

TextBox::TextDirection StreetTile::getTextBoxDirection(ReadingDirection direction) {
    switch (direction) {
    case ReadingDirection::Up: return TextBox::TextDirection::Up;
    case ReadingDirection::Down: return TextBox::TextDirection::Down;
    case ReadingDirection::Left: return TextBox::TextDirection::Left;
    case ReadingDirection::Right: return TextBox::TextDirection::Right;
    default: return TextBox::TextDirection::Up;
    }
}

void StreetTile::adjustColorStrip() {
    switch (m_readingDirection) {
    case ReadingDirection::Up:
        m_colorStrip.setPosition(m_bounds.left, m_bounds.top);
        m_colorStrip.setSize(sf::Vector2f(m_bounds.width, m_colorStripThickness));
        break;
    case ReadingDirection::Down:
        m_colorStrip.setPosition(m_bounds.left, m_bounds.top + m_bounds.height - m_colorStripThickness);
        m_colorStrip.setSize(sf::Vector2f(m_bounds.width, m_colorStripThickness));
        break;
    case ReadingDirection::Left:
        m_colorStrip.setPosition(m_bounds.left + m_bounds.width - m_colorStripThickness, m_bounds.top);
        m_colorStrip.setSize(sf::Vector2f(m_colorStripThickness, m_bounds.height));
        break;
    case ReadingDirection::Right:
        m_colorStrip.setPosition(m_bounds.left, m_bounds.top);
        m_colorStrip.setSize(sf::Vector2f(m_colorStripThickness, m_bounds.height));
        break;
    }
}

void StreetTile::adjustMainTextBoxBounds() {
    sf::FloatRect textBoxBounds;

    switch (m_readingDirection) {
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

void StreetTile::adjustOwnerTextBox() {
    sf::FloatRect ownerTextBoxBounds;

    switch (m_readingDirection) {
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
        ownerTextBoxBounds = sf::FloatRect(
            m_bounds.left + m_bounds.width,
            m_bounds.top,
            m_ownerStripThickness,
            m_bounds.height);
        break;
    case ReadingDirection::Right:
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

    m_ownerTextBox.setTexts({ { ownerText, TextBox::Alignment::Center } });
}

void StreetTile::updateTextBox() {
    // Clear existing texts
    m_mainTextBox.setTexts({});

    std::vector<std::pair<sf::Text, TextBox::Alignment>> texts;

    // Create sf::Text for name if not empty
    if (!m_name.empty()) {
        sf::Text nameText;
        nameText.setFont(m_font);
        nameText.setString(m_name);
        nameText.setFillColor(sf::Color::Black);
        nameText.setCharacterSize(30); // Placeholder size

        texts.emplace_back(std::make_pair(nameText, TextBox::Alignment::Center));
    }

    // Create sf::Text for price if greater than zero
    if (m_price > 0) {
        sf::Text priceText;
        priceText.setFont(m_font);
        priceText.setString("$" + std::to_string(m_price));
        priceText.setFillColor(sf::Color::Black);
        priceText.setCharacterSize(30); // Placeholder size

        texts.emplace_back(std::make_pair(priceText, TextBox::Alignment::Center));
    }

    // Add house/hotel information if applicable
    if (m_buildingType != BuildingType::None) {
        sf::Text buildingText;
        buildingText.setFont(m_font);
        buildingText.setFillColor(sf::Color::Black);
        buildingText.setCharacterSize(30);

        if (m_buildingType == BuildingType::Hotel) {
            buildingText.setString("Hotel");
        } else {
            int houseNumber = 0;
            switch (m_buildingType) {
            case BuildingType::OneHouse:    houseNumber = 1; break;
            case BuildingType::TwoHouses:   houseNumber = 2; break;
            case BuildingType::ThreeHouses: houseNumber = 3; break;
            case BuildingType::FourHouses:  houseNumber = 4; break;
            default: break;
            }
            buildingText.setString("Houses: " + std::to_string(houseNumber));
        }

        texts.emplace_back(std::make_pair(buildingText, TextBox::Alignment::Center));
    }

    // Set texts to main TextBox
    m_mainTextBox.setTexts(texts);
}

void StreetTile::updateOwnerTextBox() {
    if (!m_owner) {
        // Clear owner text box if no owner
        m_ownerTextBox.setTexts({});
        return;
    }

    // Owner text is set in adjustOwnerTextBox()
}

void StreetTile::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    // Draw the owner text box if there is an owner
    if (m_owner) {
        target.draw(m_ownerTextBox, states);
    }

    // Draw the main text box
    target.draw(m_mainTextBox, states);

    // Draw the color strip
    target.draw(m_colorStrip, states);
}

// Menu::Type StreetTile::onLanding(Player& player) {
//     // If the StreetTile is unowned, enable the player to buy it
//     if (m_owner == nullptr) {
//         return Menu::Type::BuyMenu;
//     } else if (m_owner != &player) {
//         // If the tile is owned by another player, deduct money and proceed to end-of-turn menus
//         unsigned int rent = calcRent();
//         if (player.getMoneyAmount() >= rent) {
//             player.deductMoney(rent);
//             m_owner->addMoney(rent);
//         }
//         return Menu::Type::PreEndTurn;
//     }
//     // If the player owns the tile, proceed normally
//     return Menu::Type::DefaultMenu;
// }
