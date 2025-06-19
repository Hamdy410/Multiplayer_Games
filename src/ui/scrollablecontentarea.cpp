#include <ui/scrollablecontentarea.hpp>
#include <constants/mainmenuconstants.hpp>
#include <algorithm>
#include <iostream>

namespace MenuConst = MainMenuConstants;

ScrollableContentArea::ScrollableContentArea(
    sf::RenderWindow* window, const sf::FloatRect& bounds
) 
: m_window(window), m_bounds(bounds), m_scrollOffset(0.0f),
m_maxScrollOffset(0.0f), m_scrollSpeed(30.0f), m_cardsPerRow(1),
m_cardSpacing(25.0f), m_totalContentHeight(0.0f)
{
    // Setup clipping view
    m_contentView.reset(m_bounds);
    m_contentView.setViewport(
        sf::FloatRect(
            m_bounds.left / window->getSize().x,
            m_bounds.top / window->getSize().y,
            m_bounds.width / window->getSize().x,
            m_bounds.height / window->getSize().y
        )
    );
}

void ScrollableContentArea::calculateGridLayout() {
    if (m_cards.empty()) {
        std::cout << "No cards to layout" << std::endl;
        return;
    }
    
    // Calculate cards per row based on available width
    float availableWidth = m_bounds.width - (m_cardSpacing * 2);
    float cardWidth = MenuConst::CARD_WIDTH;
    m_cardsPerRow = static_cast<int>((availableWidth + m_cardSpacing) / (cardWidth + m_cardSpacing));
    m_cardsPerRow = std::max(1, m_cardsPerRow);
    
    // Calculate total content height
    int rows = (m_cards.size() + m_cardsPerRow - 1) / m_cardsPerRow;
    m_totalContentHeight = (rows * MenuConst::CARD_HEIGHT) + ((rows - 1) * m_cardSpacing) + (m_cardSpacing * 2);
    
    // Debug output
    std::cout << "Grid Layout Debug:" << std::endl;
    std::cout << "  Available width: " << availableWidth << std::endl;
    std::cout << "  Card width: " << cardWidth << std::endl;
    std::cout << "  Cards per row: " << m_cardsPerRow << std::endl;
    std::cout << "  Total cards: " << m_cards.size() << std::endl;
    std::cout << "  Rows: " << rows << std::endl;
    std::cout << "  Total content height: " << m_totalContentHeight << std::endl;
    
    updateScrollLimits();
    updateCardPositions();
}

void ScrollableContentArea::updateScrollLimits()
{
    m_maxScrollOffset = std::max(0.0f, m_totalContentHeight - m_bounds.height);
    m_scrollOffset = std::max(0.0f, std::min(m_scrollOffset, m_maxScrollOffset));
}

void ScrollableContentArea::updateCardPositions() {
    if (m_cards.empty()) return;
    
    float actualGridWidth = (m_cardsPerRow * MenuConst::CARD_WIDTH) + ((m_cardsPerRow - 1) * m_cardSpacing);
    float startX = m_bounds.left + (m_bounds.width - actualGridWidth) / 2;
    float startY = m_bounds.top + m_cardSpacing - m_scrollOffset;
    
    std::cout << "Position Update Debug:" << std::endl;
    std::cout << "  Actual grid width: " << actualGridWidth << std::endl;
    std::cout << "  Start X: " << startX << std::endl;
    std::cout << "  Start Y: " << startY << std::endl;
    std::cout << "  Bounds: (" << m_bounds.left << ", " << m_bounds.top << ", " << m_bounds.width << ", " << m_bounds.height << ")" << std::endl;
    
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
    if (event.type == sf::Event::MouseWheelScrolled && m_maxScrollOffset > 0)
        scrollBy(-event.mouseWheelScroll.delta * m_scrollSpeed);
    
    // Forward events to visible cards only
    for (auto& card : m_cards)
        if (isCardVisible(*card))
            card->handleEvent(event, *m_window);
}

void ScrollableContentArea::update(float deltaTime)
{
    // Update only visible cards for performance
    for (auto& card : m_cards)
        if (isCardVisible(*card))
            card->update(deltaTime);
}

void ScrollableContentArea::draw() {
    // Temporarily disable view clipping to see if cards are positioned correctly
    // sf::View originalView = m_window->getView();
    // m_window->setView(m_contentView);
    
    std::cout << "Drawing " << m_cards.size() << " cards" << std::endl;
    
    for (size_t i = 0; i < m_cards.size(); ++i) {
        std::cout << "Drawing card " << i << std::endl;
        m_cards[i]->draw(*m_window);
    }
    
    // m_window->setView(originalView);
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

bool ScrollableContentArea::isCardVisible(const GameCard& card) const {
    // Simple visibility check - can be optimized further
    // For now, assume all cards are visible (the view clipping handles the rest)
    return true;
}
