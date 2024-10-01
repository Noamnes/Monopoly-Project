#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

//* CLASS + DEFINITIONS
/**
 * @class ColoredTextBox
 * @brief A class that represents a text box with multiple colored texts.
 *
 * The ColoredTextBox class allows you to display multiple pieces of text with different alignments and directions within a specified bounding rectangle.
 */
class ColoredTextBox : public sf::Drawable, public sf::Transformable{
public:

    /** @enum Alignment
     * @brief Enumeration for horizontal text alignment.
     */
    enum class Alignment{
        Left,
        Center,
        Right
    };

    /**
     * @enum TextDirection
     * @brief Enumeration for text direction (rotation).
     */
    enum class TextDirection{
        Up,    ///< 0 degrees rotation
        Left,  ///< 90 degrees rotation
        Down,  ///< 180 degrees rotation
        Right  ///< 270 degrees rotation
    };

    //* CONSTRUCTORS
        /** @brief Constructs a ColoredTextBox with the specified bounds.
         *
         * @param bounds The bounding rectangle for the text box.
         */
        ColoredTextBox(const sf::FloatRect& bounds);

        /** @brief Constructs a ColoredTextBox with bounds, texts, direction, and background color.
         *
         * @param bounds The bounding rectangle for the text box.
         * @param texts A vector of pairs of sf::Text and Alignment to be displayed.
         * @param direction The direction from which the text is read (default is Up).
         * @param backgroundColor The background color of the text box (default is transparent).
         */
        ColoredTextBox(
            const sf::FloatRect& bounds,
            const std::vector<std::pair<sf::Text, Alignment>>& texts,
            TextDirection direction = TextDirection::Up,
            const sf::Color& backgroundColor = sf::Color::Transparent);

    //* NECCECERY

        /** @brief Sets the texts to be displayed in the text box, overwriting any existing texts.
         *
         * @param texts A vector of pairs of sf::Text and Alignment.
         */
        void setTexts(const std::vector<std::pair<sf::Text, Alignment>>& texts);

        /** @brief Adds a text with the specified alignment to the text box.
         *
         * @param text The sf::Text to add.
         * @param alignment The alignment for the text (default is Left).
         */
        void addText(const sf::Text& text, Alignment alignment = Alignment::Left);
    
        /**
         * @brief Sets the text direction (rotation) for the text box.
         *
         * @param direction The TextDirection to set.
         */
        void setTextDirection(TextDirection direction);
    
    //* NOT NECCECERY

        /**
         * @brief Sets the bounds of the text box.
         *
         * @param bounds The new bounding rectangle.
         */
        void setBounds(const sf::FloatRect& bounds);

        /**
         * @brief Sets the background fill color of the text box.
         *
         * @param color The sf::Color to set as the background fill color.
         */
        void setBackgroundColor(const sf::Color& color);

        /**
         * @brief Sets the outline color of the text box.
         *
         * @param color The sf::Color to set as the outline color.
         */
        void setOutlineColor(const sf::Color& color);

        /**
         * @brief Sets the outline thickness of the text box.
         *
         * @param thickness The thickness of the outline.
         */
        void setOutlineThickness(float thickness);

private:
    /** @brief Struct to hold a text and its alignment. */
    struct TextEntry{
        sf::Text text;
        Alignment alignment;
    };

    /** @brief Draws the ColoredTextBox to the render target.
     *
     * @param target The render target to draw to.
     * @param states The render states to use for drawing.
     */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /** @brief Updates the display texts based on the current state.*/
    void update() const;

    /** @brief Computes the maximum font size that will fit all texts within the bounds.
     *
     *  @return The maximum font size.
     */
    unsigned int computeMaxFontSize() const;

    /** @brief Gets the rotation angle in degrees based on the text direction.
     *
     * @return The rotation angle in degrees.
     */
    float getRotationAngle() const;

    /** @brief Adjusts the position and alignment of a text within the text box.
     *
     * @param text The text to adjust.
     * @param lb The local bounds of the text.
     * @param alignment The alignment of the text.
     * @param positionOffset The accumulated offset along the stacking direction.
     */
    void adjustTextPosition(
        sf::Text& text,
        const sf::FloatRect& lb,
        Alignment alignment,
        float positionOffset) const;

    
    //* MEMBERS

        /** @brief The bounds of the text box.*/
        sf::FloatRect m_bounds;

        /** @brief The direction from which the text is read.*/
        TextDirection m_textDirection;

        /** @brief The vector of text entries to be displayed.
         * 
         * the texts here aren't configured for display
         */
        std::vector<TextEntry> m_textEntries;

        /** @brief The vector of texts ready for display.
         *
         * This vector is mutable because it is updated in the const draw function.
         */
        mutable std::vector<sf::Text> m_displayTexts;

        /** @brief Flag indicating whether the display texts need to be updated before drawing.
         *
         *  needed to avoid udating the textbox when it's unnecessary
         */  
        mutable bool m_needsUpdate;

        /** @brief The background rectangle shape of the text box. */
        sf::RectangleShape m_background;
};


//* IMPLEMENTATION

ColoredTextBox::ColoredTextBox(const sf::FloatRect& bounds)
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

ColoredTextBox::ColoredTextBox(
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

void ColoredTextBox::setTextDirection(TextDirection direction)
{
    if (m_textDirection != direction)
    {
        m_textDirection = direction;
        m_needsUpdate = true;
    }
}

void ColoredTextBox::addText(const sf::Text& text, Alignment alignment)
{
    m_textEntries.push_back({ text, alignment });
    m_needsUpdate = true;
}

void ColoredTextBox::setBounds(const sf::FloatRect& bounds)
{
    m_bounds = bounds;
    m_background.setPosition(sf::Vector2f(m_bounds.left, m_bounds.top));
    m_background.setSize(sf::Vector2f(m_bounds.width, m_bounds.height));
    m_needsUpdate = true;
}

void ColoredTextBox::setTexts(const std::vector<std::pair<sf::Text, Alignment>>& texts){
    m_textEntries.clear();
    for (const auto& pair : texts)
    {
        m_textEntries.push_back({ pair.first, pair.second });
    }
    m_needsUpdate = true;
}

void ColoredTextBox::setBackgroundColor(const sf::Color& color)
{
    m_background.setFillColor(color);
}

void ColoredTextBox::setOutlineColor(const sf::Color& color)
{
    m_background.setOutlineColor(color);
}

void ColoredTextBox::setOutlineThickness(float thickness)
{
    m_background.setOutlineThickness(thickness);
}

void ColoredTextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
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

void ColoredTextBox::update() const
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

unsigned int ColoredTextBox::computeMaxFontSize() const
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

float ColoredTextBox::getRotationAngle() const
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

void ColoredTextBox::adjustTextPosition(
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
