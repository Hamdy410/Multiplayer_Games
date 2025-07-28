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
        std::vector<sf::Vector2f> m_cardPositions;  // Track card positions

        // Content
        std::vector<std::unique_ptr<GameCard>> m_cards;

        void calculateGridLayout();
        void updateScrollLimits();
        void updateCardPositions();

        // Enhanced visibility checking
        bool isCardVisible(size_t cardIndex) const;

    public:
        ScrollableContentArea(sf::RenderWindow* window, const sf::FloatRect& bounds);

        // Content management
        void addCard(std::unique_ptr<GameCard> card);
        void clearCards();
        void setCardSpacing(float spacing);

        // Event handling
        void handleEvent(const sf::Event& event);
        void update(float deltaTime, sf::RenderWindow& window);
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

