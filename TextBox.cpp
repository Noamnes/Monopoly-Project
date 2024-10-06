#include <SFML/Graphics.hpp>
#include <vector>
#include "TextBox.hpp"

TextBox::TextBox(const sf::FloatRect& bounds)
    : m_bounds(bounds)
    , m_textDirection(TextDirection::Up)
    , m_needsUpdate(true)
{
    // Initialize background rectangle
    m_background.setPosition(sf::Vector2f(m_bounds.left, m_bounds.top));
    m_background.setSize(sf::Vector2f(m_bounds.width, m_bounds.height));
    m_background.setFillColor(sf::Color::Transparent); // Default transparent
    m_background.setOutlineColor(sf::Color::Transparent);
    m_background.setOutlineThickness(0);
}

TextBox::TextBox(
    const sf::FloatRect& bounds,
    const std::vector<std::pair<sf::Text, Alignment>>& texts,
    TextDirection direction,
    const sf::Color& backgroundColor)
    : m_bounds(bounds)
    , m_textDirection(direction)
    , m_needsUpdate(true)
{
    setTexts(texts);

    // Initialize background rectangle
    m_background.setPosition(sf::Vector2f(m_bounds.left, m_bounds.top));
    m_background.setSize(sf::Vector2f(m_bounds.width, m_bounds.height));
    m_background.setFillColor(backgroundColor);
    m_background.setOutlineColor(sf::Color::Transparent);
    m_background.setOutlineThickness(0);
}

void TextBox::setTextDirection(TextDirection direction)
{
    if (m_textDirection != direction)
    {
        m_textDirection = direction;
        m_needsUpdate = true;
    }
}

void TextBox::addText(const sf::Text& text, Alignment alignment)
{
    m_textEntries.push_back({ text, alignment });
    m_needsUpdate = true;
}

void TextBox::setBounds(const sf::FloatRect& bounds)
{
    m_bounds = bounds;
    m_background.setPosition(sf::Vector2f(m_bounds.left, m_bounds.top));
    m_background.setSize(sf::Vector2f(m_bounds.width, m_bounds.height));
    m_needsUpdate = true;
}

void TextBox::setTexts(const std::vector<std::pair<sf::Text, Alignment>>& texts){
    m_textEntries.clear();
    for (const auto& pair : texts)
    {
        m_textEntries.push_back({ pair.first, pair.second });
    }
    m_needsUpdate = true;
}

void TextBox::setBackgroundColor(const sf::Color& color)
{
    m_background.setFillColor(color);
}

void TextBox::setOutlineColor(const sf::Color& color)
{
    m_background.setOutlineColor(color);
}

void TextBox::setOutlineThickness(float thickness)
{
    m_background.setOutlineThickness(thickness);
}

void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_needsUpdate)
    {
        update();
        m_needsUpdate = false;
    }

    states.transform *= getTransform();

    // Draw background rectangle first
    target.draw(m_background, states);

    for (const auto& text : m_displayTexts)
    {
        target.draw(text, states);
    }
}

void TextBox::update() const
{
    m_displayTexts.clear();

    if (m_textEntries.empty())
        return;

    // Compute the maximum font size that will fit the texts within the bounds
    unsigned int fontSize = computeMaxFontSize();

    float positionOffset = 0.f; // Accumulated offset along the stacking direction

    for (const auto& entry : m_textEntries)
    {
        const sf::String& string = entry.text.getString();
        const sf::Font* font = entry.text.getFont();
        if (!font)
            continue; // Can't process without font

        sf::Text text;
        text.setFont(*font);
        text.setString(string);
        text.setCharacterSize(fontSize);

        // Copy additional properties
        text.setFillColor(entry.text.getFillColor());
        text.setStyle(entry.text.getStyle());
        text.setOutlineColor(entry.text.getOutlineColor());
        text.setOutlineThickness(entry.text.getOutlineThickness());

        // Set rotation
        float rotationAngle = getRotationAngle();
        text.setRotation(rotationAngle);

        // Get local bounds after setting character size
        sf::FloatRect lb = text.getLocalBounds();

        // Adjust origin and position to keep text within bounds after rotation
        adjustTextPosition(text, lb, entry.alignment, positionOffset);

        // Add to display list
        m_displayTexts.push_back(text);

        // Update position offset for next text
        float lineSpacing = font->getLineSpacing(fontSize);

        positionOffset += lineSpacing;
    }
}

unsigned int TextBox::computeMaxFontSize() const
{
    if (m_textEntries.empty())
        return 0;

    unsigned int minFontSize = 1;
    unsigned int maxFontSize = 1000; // Some large maximum

    unsigned int bestFontSize = minFontSize;

    while (minFontSize <= maxFontSize)
    {
        unsigned int fontSize = (minFontSize + maxFontSize) / 2;
        bool fits = true;
        float totalStackLength = 0.0f; // Total length along the stacking direction

        for (const auto& entry : m_textEntries){
            const sf::String& string = entry.text.getString();
            const sf::Font* font = entry.text.getFont();
            if (!font)
            {
                fits = false;
                break; // Can't compute without font
            }

            // Create a temporary sf::Text to measure
            sf::Text tempText;
            tempText.setFont(*font);
            tempText.setString(string);
            tempText.setCharacterSize(fontSize);
            tempText.setRotation(getRotationAngle());

            sf::FloatRect gb = tempText.getGlobalBounds();

            float lineSpacing = font->getLineSpacing(fontSize); // Spacing between lines
            float lineLength = 0.0f; // Length along the perpendicular direction

            if (m_textDirection == TextDirection::Up || m_textDirection == TextDirection::Down)
            {
                // Vertical stacking
                lineLength = gb.width; // Width after rotation
                // if there is just one text entry, squeeze the biggest font you can get, not caring for line spacing:
                if(m_textEntries.size() == 1){
                    totalStackLength += gb.height;
                }
            }
            else // Left or Right
            {
                // Horizontal stacking
                lineLength = gb.height; // Height after rotation
                
                // if there is just one text entry, squeeze the biggest font you can get, not caring for line spacing:
                if(m_textEntries.size() == 1){
                    totalStackLength += gb.width;
                }
            }
            // if there is more than one text entry, give more space for line spacing
            if(m_textEntries.size() > 1){
                totalStackLength += lineSpacing; 
            }

            if ((m_textDirection == TextDirection::Up || m_textDirection == TextDirection::Down)
                && lineLength > m_bounds.width)
            {
                fits = false;
                break;
            }
            else if ((m_textDirection == TextDirection::Left || m_textDirection == TextDirection::Right)
                && lineLength > m_bounds.height)
            {
                fits = false;
                break;
            }
        }

        // Check if totalStackLength exceeds bounds along the stacking direction
        if ((m_textDirection == TextDirection::Up || m_textDirection == TextDirection::Down)
            && totalStackLength > m_bounds.height)
        {
            fits = false;
        }
        else if ((m_textDirection == TextDirection::Left || m_textDirection == TextDirection::Right)
            && totalStackLength > m_bounds.width)
        {
            fits = false;
        }

        if (fits)
        {
            // All constraints satisfied, try a larger font size
            bestFontSize = fontSize;
            minFontSize = fontSize + 1;
        }
        else
        {
            // Constraints not satisfied, try a smaller font size
            maxFontSize = fontSize - 1;
        }
    }
    // std::cout<<bestFontSize<<std::endl; DEBUG
    // std::cout<<m_textEntries.size()<<std::endl; DEBUG
    return bestFontSize;
}

float TextBox::getRotationAngle() const
{
    switch (m_textDirection)
    {
    case TextDirection::Up:
        return 0.f;
    case TextDirection::Left:
        return 90.f;
    case TextDirection::Down:
        return 180.f;
    case TextDirection::Right:
        return 270.f;
    }
    return 0.f;
}

void TextBox::adjustTextPosition(
    sf::Text& text,
    const sf::FloatRect& lb,
    Alignment alignment,
    float positionOffset) const
{
    float x = 0.f;
    float y = 0.f;

    // Set origin to the center of the local bounds for rotation
    sf::Vector2f origin(lb.left + lb.width / 2.f, lb.top + lb.height / 2.f);
    text.setOrigin(origin);

    // Adjust position and alignment based on text direction
    switch (m_textDirection)
    {
    case TextDirection::Up:
    {
        // Vertical stacking (y increases)
        y = m_bounds.top + positionOffset + lb.height / 2.f;
        // Horizontal alignment
        switch (alignment)
        {
        case Alignment::Left:
            x = m_bounds.left + lb.width / 2.f;
            break;
        case Alignment::Center:
            x = m_bounds.left + m_bounds.width / 2.f;
            break;
        case Alignment::Right:
            x = m_bounds.left + m_bounds.width - lb.width / 2.f;
            break;
        }
        break;
    }
    case TextDirection::Down:
    {
        // Vertical stacking (y increases from bottom)
        y = m_bounds.top + m_bounds.height - positionOffset - lb.height / 2.f;
        // Horizontal alignment
        switch (alignment)
        {
        case Alignment::Left:
            x = m_bounds.left + lb.width / 2.f;
            break;
        case Alignment::Center:
            x = m_bounds.left + m_bounds.width / 2.f;
            break;
        case Alignment::Right:
            x = m_bounds.left + m_bounds.width - lb.width / 2.f;
            break;
        }
        break;
    }
    case TextDirection::Left:
    {
        // Horizontal stacking (x decreases)
        x = m_bounds.left + m_bounds.width - positionOffset - lb.height / 2.f;
        // Vertical alignment
        switch (alignment)
        {
        case Alignment::Left:
            y = m_bounds.top + lb.width / 2.f;
            break;
        case Alignment::Center:
            y = m_bounds.top + m_bounds.height / 2.f;
            break;
        case Alignment::Right:
            y = m_bounds.top + m_bounds.height - lb.width / 2.f;
            break;
        }
        break;
    }
    case TextDirection::Right:
    {
        // Horizontal stacking (x increases)
        x = m_bounds.left + positionOffset + lb.height / 2.f;
        // Vertical alignment
        switch (alignment)
        {
        case Alignment::Left:
            y = m_bounds.top + m_bounds.height - lb.width / 2.f;
            break;
        case Alignment::Center:
            y = m_bounds.top + m_bounds.height / 2.f;
            break;
        case Alignment::Right:
            y = m_bounds.top + lb.width / 2.f;
            break;
        }
        break;
    }
    }

    text.setPosition(x, y);
}
