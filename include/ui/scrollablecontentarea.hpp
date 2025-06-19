#ifndef SCROLLABLECONTENTAREA_HPP
#define SCROLLABLECONTENTAREA_HPP

#include <SFML/Graphics.hpp>
#include <ui/gamecard.hpp>
#include <vector>
#include <memory>
#include <functional>

class ScrollableContentArea
{
    private:
        sf::RenderWindow* m_window;
        sf::FloatRect m_bounds;
        sf::View m_contentView;

        // Scrolling
        float m_scrollOffset;
        float m_maxScrollOffset;
        float m_scrollSpeed;

        // Grid Layout
        int m_cardsPerRow;
        float m_cardSpacing;
        float m_totalContentHeight;

        // Content
        std::vector<std::unique_ptr<GameCard>> m_cards;

        void calculateGridLayout();
        void updateScrollLimits();
        void updateCardPositions();

        // Enhanced visibility checking
        bool isCardVisible(const GameCard& card) const;
        sf::FloatRect

    public:
        ScrollableContentArea(sf::RenderWindow* window, const sf::FloatRect& bounds);

        // Content management
        void addCard(std::unique_ptr<GameCard> card);
        void clearCards();
        void setCardSpacing(float spacing);

        // Event handling
        void handleEvent(const sf::Event& event);
        void update(float deltaTime);
        void draw();

        // Scrolling control
        void scrollTo(float offset);
        void scrollBy(float delta);
        float getScrollOffset() const { return m_scrollOffset; }
        float getMaxScrollOffset() const { return m_maxScrollOffset; }

        // Layout info
        int getCardPerRow() const { return m_cardsPerRow; }
        bool hasVerticalScroll() const { return m_maxScrollOffset > 0; }
};

#endif  // SCROLLABLECONTENTAREA_HPP
