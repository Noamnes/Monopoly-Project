#include "Board.hpp"

Board::Board(float edgeSize, float cornersRatio, sf::Font &font):
    m_font(font),
    m_edgeSize(edgeSize),
    m_cornersRatio(cornersRatio)
{
    createTiles();
    adjustAllComponents();
}

void Board::createTiles(){
    // create the corners
    // the corners that do nothing on landing
    m_BottomRightCorner = std::make_unique<StreetTile>("Go", 100, m_font, StreetTile::ReadingDirection::Up, sf::Color::White); //! UNCOMMENT
    m_BottomLeftCorner = std::make_unique<StreetTile>("Jail", 100, m_font, StreetTile::ReadingDirection::Up, sf::Color::White); //! UNCOMMENT
    m_TopLeftCorner = std::make_unique<StreetTile>("Free Parking", 100, m_font, StreetTile::ReadingDirection::Up, sf::Color::White); //! UNCOMMENT
    // the corner that does something: Go to jail
    m_TopRightCorner = std::make_unique<StreetTile>("Go to Jail", 100, m_font, StreetTile::ReadingDirection::Up, sf::Color::White); //! UNCOMMENT

    // create the edges
    // down edge
    m_downEdge.push_back(std::make_unique<StreetTile>("Ofakim", 100, m_font, StreetTile::ReadingDirection::Up, sf::Color(252, 152, 3))); // orange
    m_downEdge.push_back(std::make_unique<StreetTile>("Sderot", 80, m_font, StreetTile::ReadingDirection::Up, sf::Color(252, 152, 3))); // orange
    m_downEdge.push_back(std::make_unique<StreetTile>("Netivot", 60, m_font, StreetTile::ReadingDirection::Up, sf::Color(252, 152, 3))); // orange
    m_downEdge.push_back(std::make_unique<StreetTile>("Ashdod Port", 200, m_font, StreetTile::ReadingDirection::Up, sf::Color::Red));
    m_downEdge.push_back(std::make_unique<StreetTile>("Ashkelon", 50, m_font, StreetTile::ReadingDirection::Up, sf::Color::Red));
    m_downEdge.push_back(std::make_unique<StreetTile>("Nitzanim", 50, m_font, StreetTile::ReadingDirection::Up, sf::Color::Red));
    m_downEdge.push_back(std::make_unique<StreetTile>("Palmachim", 60, m_font, StreetTile::ReadingDirection::Up, sf::Color::Red));

    // left edge
    m_leftEdge.push_back(std::make_unique<StreetTile>("Eilat", 100, m_font, StreetTile::ReadingDirection::Left, sf::Color::Green));
    m_leftEdge.push_back(std::make_unique<StreetTile>("Yotvata", 60, m_font, StreetTile::ReadingDirection::Left, sf::Color::Green));
    m_leftEdge.push_back(std::make_unique<StreetTile>("Mitzpe Ramon", 60, m_font, StreetTile::ReadingDirection::Left, sf::Color::Green));
    m_leftEdge.push_back(std::make_unique<StreetTile>("Be'er Sheva University", 200, m_font, StreetTile::ReadingDirection::Left, sf::Color::Blue));
    m_leftEdge.push_back(std::make_unique<StreetTile>("Sde Boker", 50, m_font, StreetTile::ReadingDirection::Left, sf::Color::Blue));
    m_leftEdge.push_back(std::make_unique<StreetTile>("Dimona", 50, m_font, StreetTile::ReadingDirection::Left, sf::Color::Blue));
    m_leftEdge.push_back(std::make_unique<StreetTile>("Arad", 60, m_font, StreetTile::ReadingDirection::Left, sf::Color::Blue));
    m_leftEdge.push_back(std::make_unique<StreetTile>("Yeruham", 70, m_font, StreetTile::ReadingDirection::Left, sf::Color::Blue));

    // up edge
    m_upEdge.push_back(std::make_unique<StreetTile>("Haifa", 100, m_font, StreetTile::ReadingDirection::Down, sf::Color::Magenta));
    m_upEdge.push_back(std::make_unique<StreetTile>("Acre", 80, m_font, StreetTile::ReadingDirection::Down, sf::Color::Magenta));
    m_upEdge.push_back(std::make_unique<StreetTile>("Kiryat Ata", 60, m_font, StreetTile::ReadingDirection::Down, sf::Color::Magenta));
    m_upEdge.push_back(std::make_unique<StreetTile>("Kiryat Motzkin", 60, m_font, StreetTile::ReadingDirection::Down, sf::Color::Magenta));
    m_upEdge.push_back(std::make_unique<StreetTile>("Carmel Tunnels", 200, m_font, StreetTile::ReadingDirection::Down, sf::Color::Yellow));
    m_upEdge.push_back(std::make_unique<StreetTile>("Tiberias", 50, m_font, StreetTile::ReadingDirection::Down, sf::Color::Yellow));
    m_upEdge.push_back(std::make_unique<StreetTile>("Karmiel", 50, m_font, StreetTile::ReadingDirection::Down, sf::Color::Yellow));
    m_upEdge.push_back(std::make_unique<StreetTile>("Tzfat", 60, m_font, StreetTile::ReadingDirection::Down, sf::Color::Yellow));

    // right edge
    m_rightEdge.push_back(std::make_unique<StreetTile>("Tel Aviv", 100, m_font, StreetTile::ReadingDirection::Right, sf::Color::Cyan));
    m_rightEdge.push_back(std::make_unique<StreetTile>("Ramat Gan", 60, m_font, StreetTile::ReadingDirection::Right, sf::Color::Cyan));
    m_rightEdge.push_back(std::make_unique<StreetTile>("Bat Yam", 80, m_font, StreetTile::ReadingDirection::Right, sf::Color::Cyan));
    m_rightEdge.push_back(std::make_unique<StreetTile>("Holon", 60, m_font, StreetTile::ReadingDirection::Right, sf::Color::Cyan));
    m_rightEdge.push_back(std::make_unique<StreetTile>("Ayalon Highway", 200, m_font, StreetTile::ReadingDirection::Right));
    m_rightEdge.push_back(std::make_unique<StreetTile>("Rishon LeZion", 50, m_font, StreetTile::ReadingDirection::Right, sf::Color(173, 216, 230)));
    m_rightEdge.push_back(std::make_unique<StreetTile>("Petah Tikva", 70, m_font, StreetTile::ReadingDirection::Right, sf::Color(173, 216, 230)));
    m_rightEdge.push_back(std::make_unique<StreetTile>("Rehovot", 50, m_font, StreetTile::ReadingDirection::Right, sf::Color(173, 216, 230)));

    adjustAllComponents();
}

void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    // draw the corners
    target.draw(*m_BottomRightCorner, states);
    target.draw(*m_BottomLeftCorner, states);
    target.draw(*m_TopLeftCorner, states);
    target.draw(*m_TopRightCorner, states);

    // draw the edges
    for (const auto& tile : m_downEdge){
        target.draw(*tile, states);
    }
    for (const auto& tile : m_leftEdge){
        target.draw(*tile, states);
    }
    for (const auto& tile : m_upEdge){
        target.draw(*tile, states);
    }
    for (const auto& tile : m_rightEdge){
        target.draw(*tile, states);
    }
}

void Board::adjustAllComponents(){
    // set the bounds of the corners
    // m_BottomRightCorner->getBounds(); //DEBUG
    m_BottomRightCorner->setBounds(sf::FloatRect(m_edgeSize * (1 - m_cornersRatio), m_edgeSize * (1 - m_cornersRatio), m_edgeSize * m_cornersRatio, m_edgeSize * m_cornersRatio));
    m_BottomLeftCorner->setBounds(sf::FloatRect(0, m_edgeSize * (1 - m_cornersRatio), m_edgeSize * m_cornersRatio, m_edgeSize * m_cornersRatio));
    m_TopLeftCorner->setBounds(sf::FloatRect(0, 0, m_edgeSize * m_cornersRatio, m_edgeSize * m_cornersRatio));
    m_TopRightCorner->setBounds(sf::FloatRect(m_edgeSize * (1 - m_cornersRatio), 0, m_edgeSize * m_cornersRatio, m_edgeSize * m_cornersRatio));

    // set the bounds of the edges
    setHorizontalEdgeBounds(m_downEdge, sf::FloatRect(m_edgeSize * m_cornersRatio, m_edgeSize * (1 - m_cornersRatio), m_edgeSize * (1 - 2 * m_cornersRatio), m_edgeSize * m_cornersRatio));
    setVerticalEdgeBounds(m_leftEdge, sf::FloatRect(0, m_edgeSize * m_cornersRatio, m_edgeSize * m_cornersRatio, m_edgeSize * (1 - 2 * m_cornersRatio)));
    setHorizontalEdgeBounds(m_upEdge, sf::FloatRect(m_edgeSize * m_cornersRatio, 0, m_edgeSize * (1 - 2 * m_cornersRatio), m_edgeSize * m_cornersRatio));
    setVerticalEdgeBounds(m_rightEdge, sf::FloatRect(m_edgeSize * (1 - m_cornersRatio), m_edgeSize * m_cornersRatio, m_edgeSize * m_cornersRatio, m_edgeSize * (1 - 2 * m_cornersRatio)));
}

void Board::setHorizontalEdgeBounds(std::vector<std::unique_ptr<StreetTile>>& edge, sf::FloatRect bounds){
    float edgeSize = bounds.width / edge.size();
    for (unsigned int i = 0; i < edge.size(); i++){
        edge[i]->setBounds(sf::FloatRect(bounds.left + i * edgeSize, bounds.top, edgeSize, bounds.height));
    }
}

void Board::setVerticalEdgeBounds(std::vector<std::unique_ptr<StreetTile>>& edge, sf::FloatRect bounds){
    float edgeSize = bounds.height / edge.size();
    for (unsigned int i = 0; i < edge.size(); i++){
        edge[i]->setBounds(sf::FloatRect(bounds.left, bounds.top + i * edgeSize, bounds.width, edgeSize));
    }
}