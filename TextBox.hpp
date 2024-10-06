#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

//* CLASS + DEFINITIONS
/**
 * @class TextBox
 * @brief A class that represents a text box with multiple colored texts.
 *
 * The TextBox class allows you to display multiple pieces of text with different alignments and directions within a specified bounding rectangle.
 */
class TextBox : public sf::Drawable, public sf::Transformable{
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
        /** @brief Constructs a TextBox with the specified bounds.
         *
         * @param bounds The bounding rectangle for the text box.
         */
        TextBox(const sf::FloatRect& bounds);

        /** @brief Constructs a TextBox with bounds, texts, direction, and background color.
         *
         * @param bounds The bounding rectangle for the text box.
         * @param texts A vector of pairs of sf::Text and Alignment to be displayed.
         * @param direction The direction from which the text is read (default is Up).
         * @param backgroundColor The background color of the text box (default is transparent).
         */
        TextBox(
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

    /** @brief Draws the TextBox to the render target.
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