#include <ui/scrollablecontentarea.hpp>
#include <constants/mainmenuconstants.hpp>
#include <constants/scrollablecontentareaconstants.hpp>
#include <algorithm>
#include <iostream>

namespace MenuConst = MainMenuConstants;
namespace ScrollConst = ScrollableContentAreaConstants;

ScrollableContentArea::ScrollableContentArea(
    sf::RenderWindow* window, const sf::FloatRect& bounds
) 
: m_window(window), m_bounds(bounds),
m_scrollOffset(ScrollConst::INITIAL_SCROLL_OFFSET),
m_maxScrollOffset(ScrollConst::INITIAL_MAX_SCROLL_OFFSET),
m_scrollSpeed(ScrollConst::DEFAULT_SCROLL_SPEED),
m_cardsPerRow(ScrollConst::INITIAL_CARDS_PER_ROW),
m_cardSpacing(ScrollConst::DEFAULT_CARD_SPACING),
m_totalContentHeight(ScrollConst::INITIAL_TOTAL_CONTENT_HEIGHT)
{
    // Setup clipping view
#if SFML_VERSION_MAJOR >= 3
    // SFML 3.0+ - Use Vector2f parameters for setCenter and setSize
    m_contentView.setCenter(sf::Vector2f(m_bounds.position.x + m_bounds.size.x / 2, 
                                        m_bounds.position.y + m_bounds.size.y / 2));
    m_contentView.setSize(sf::Vector2f(m_bounds.size.x, m_bounds.size.y));
    
    // SFML 3.0+ - FloatRect constructor with Vector2f
    m_contentView.setViewport(sf::FloatRect(
        sf::Vector2f(m_bounds.position.x / window->getSize().x, 
                     m_bounds.position.y / window->getSize().y),
        sf::Vector2f(m_bounds.size.x / window->getSize().x, 
                     m_bounds.size.y / window->getSize().y)
    ));
#else
    // SFML 2.x - Use reset method
    m_contentView.reset(m_bounds);
    
    // SFML 2.x - FloatRect constructor with four parameters
    m_contentView.setViewport(sf::FloatRect(
        m_bounds.left / window->getSize().x,
        m_bounds.top / window->getSize().y,
        m_bounds.width / window->getSize().x,
        m_bounds.height / window->getSize().y
    ));
#endif
}


void ScrollableContentArea::calculateGridLayout() {
    if (m_cards.empty()) {
        std::cout << "No cards to layout" << std::endl;
        return;
    }
    
    // Calculate cards per row based on available width
#if SFML_VERSION_MAJOR >= 3
    // SFML 3.0+ - Use .size.x
    float availableWidth = m_bounds.size.x - (m_cardSpacing * ScrollConst::SPACING_MULTIPLIER);
#else
    // SFML 2.x - Use .width
    float availableWidth = m_bounds.width - (m_cardSpacing * ScrollConst::SPACING_MULTIPLIER);
#endif
    
    float cardWidth = MenuConst::CARD_WIDTH;
    m_cardsPerRow = static_cast<int>((availableWidth + m_cardSpacing) / (cardWidth + m_cardSpacing));
    m_cardsPerRow = std::max(ScrollConst::MIN_CARDS_PER_ROW, m_cardsPerRow);
    
    // Calculate total content height
    int rows = (m_cards.size() + m_cardsPerRow - 1) / m_cardsPerRow;
    m_totalContentHeight = (rows * MenuConst::CARD_HEIGHT) + ((rows - 1) * m_cardSpacing) + (m_cardSpacing * ScrollConst::SPACING_MULTIPLIER);
    
    updateScrollLimits();
    updateCardPositions();
}

void ScrollableContentArea::updateScrollLimits()
{
#if SFML_VERSION_MAJOR >= 3
    // SFML 3.0+ - Use .size.y
    m_maxScrollOffset = std::max(0.0f, m_totalContentHeight - m_bounds.size.y);
#else
    // SFML 2.x - Use .height
    m_maxScrollOffset = std::max(0.0f, m_totalContentHeight - m_bounds.height);
#endif
    
    m_scrollOffset = std::max(0.0f, std::min(m_scrollOffset, m_maxScrollOffset));
}

void ScrollableContentArea::updateCardPositions() {
    if (m_cards.empty()) return;

    m_cardPositions.resize(m_cards.size());
    
    float actualGridWidth = (m_cardsPerRow * MenuConst::CARD_WIDTH) + ((m_cardsPerRow - 1) * m_cardSpacing);
    
#if SFML_VERSION_MAJOR >= 3
    // SFML 3.0+ - Use .position.x/.position.y and .size.x
    float startX = m_bounds.position.x + (m_bounds.size.x - actualGridWidth) / 2;
    float startY = m_bounds.position.y + m_cardSpacing - m_scrollOffset;
#else
    // SFML 2.x - Use .left/.top and .width
    float startX = m_bounds.left + (m_bounds.width - actualGridWidth) / 2;
    float startY = m_bounds.top + m_cardSpacing - m_scrollOffset;
#endif
    
    for (size_t i = 0; i < m_cards.size(); ++i) {
        int row = i / m_cardsPerRow;
        int col = i % m_cardsPerRow;
        
        float cardX = startX + (col * (MenuConst::CARD_WIDTH + m_cardSpacing));
        float cardY = startY + (row * (MenuConst::CARD_HEIGHT + m_cardSpacing));
        
        std::cout << "  Card " << i << ": row=" << row << ", col=" << col << ", pos=(" << cardX << ", " << cardY << ")" << std::endl;
        
        m_cards[i]->setPosition(sf::Vector2f(cardX, cardY));
    }
}

void ScrollableContentArea::addCard(std::unique_ptr<GameCard> card)
{
    m_cards.push_back(std::move(card));
    calculateGridLayout();
}

void ScrollableContentArea::clearCards()
{
    m_cards.clear();
    m_scrollOffset = 0.0f;
    m_maxScrollOffset = 0.0f;
    m_totalContentHeight = 0.0f;
}

void ScrollableContentArea::setCardSpacing(float spacing)
{
    m_cardSpacing = spacing;
    calculateGridLayout();
}

void ScrollableContentArea::handleEvent(const sf::Event& event)
{
    // Handle scrolling
#if SFML_VERSION_MAJOR >= 3
    // SFML 3.0+ API
    if (event.is<sf::Event::MouseWheelScrolled>() && m_maxScrollOffset > 0) {
        const auto& wheelEvent = event.getIf<sf::Event::MouseWheelScrolled>();
        scrollBy(-wheelEvent->delta * m_scrollSpeed);
    }
#else
    // SFML 2.x API
    if (event.type == sf::Event::MouseWheelScrolled && m_maxScrollOffset > 0) {
        scrollBy(-event.mouseWheelScroll.delta * m_scrollSpeed);
    }
#endif
    
    // Forward events to visible cards only
    for (size_t i = 0; i < m_cards.size(); i++)
        if (isCardVisible(i))
            m_cards[i]->handleEvent(event, *m_window);
}

void ScrollableContentArea::update(float deltaTime)
{
    // Update only visible cards for performance
    for (size_t i = 0; i < m_cards.size(); ++i)
        if (isCardVisible(i))
            m_cards[i]->update(deltaTime);
}

void ScrollableContentArea::draw() {
    sf::View originalView = m_window->getView();
    m_window->setView(m_contentView);

    int visibleCards = 0;

    for (size_t i = 0; i < m_cards.size(); i++)
        if (isCardVisible(i))
        {
            m_cards[i]->draw(*m_window);
            visibleCards++;
        }

    if (visibleCards != static_cast<int>(m_cards.size()))
        std::cout << "Rendering " << visibleCards << " out of " << m_cards.size() << " cards" << std::endl;

    m_window->setView(originalView);
}

void ScrollableContentArea::scrollTo(float offset)
{
    m_scrollOffset = std::max(0.0f, std::min(offset, m_maxScrollOffset));
    updateCardPositions();
}

void ScrollableContentArea::scrollBy(float delta)
{
    scrollTo(m_scrollOffset + delta);
}

bool ScrollableContentArea::isCardVisible(size_t cardIndex) const
{
    if (cardIndex >= m_cardPositions.size() || cardIndex < 0) return false;

    sf::Vector2f cardPos = m_cardPositions[cardIndex];

    // Card bounds
    float cardLeft = cardPos.x;
    float cardTop = cardPos.y;
    float cardRight = cardPos.x + MenuConst::CARD_WIDTH;
    float cardBottom = cardPos.y + MenuConst::CARD_HEIGHT;

    // Content Area bounds
#if SFML_VERSION_MAJOR >= 3
    // SFML 3.0+ - Use .position.x/.position.y and .size.x/.size.y
    float contentLeft = m_bounds.position.x;
    float contentTop = m_bounds.position.y;
    float contentRight = m_bounds.position.x + m_bounds.size.x;
    float contentBottom = m_bounds.position.y + m_bounds.size.y;
#else
    // SFML 2.x - Use .left/.top/.width/.height
    float contentLeft = m_bounds.left;
    float contentTop = m_bounds.top;
    float contentRight = m_bounds.left + m_bounds.width;
    float contentBottom = m_bounds.top + m_bounds.height;
#endif

    // Check the intersection using algorithm provided by perplexity
    bool horizontalOverlap = (cardLeft < contentRight) && (cardRight > contentLeft);
    bool verticalOverlap = (cardTop < contentBottom) && (cardBottom > contentTop);
    
    return horizontalOverlap && verticalOverlap;
}
