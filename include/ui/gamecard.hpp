#ifndef GAMECARD_HPP
#define GAMECARD_HPP

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

class GameCard
{
    private:
        sf::RectangleShape m_background;
        sf::Sprite m_icon;
        sf::Text m_title;
        sf::Text m_description;
        sf::Font* m_font;
        sf::Texture* m_texture;
        sf::Vector2f m_position;
        sf::Vector2f m_size;
        bool m_isHovered = false;
        std::function<void()> m_onClick;

        void updateVisuals();
    
    public:
        GameCard(const sf::Vector2f& position, const sf::Vector2f& size,
            sf::Font* font);
        
        void setTexture(sf::Texture* texture);
        void setTitle(const std::string& title);
        void setDescription(const std::string& desc);
        void setOnClick(std::function<void()> callback);
        void setPosition(const sf::Vector2f& position);

        void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
        void update(float dt, sf::RenderWindow& window);
        void draw(sf::RenderWindow& window);

        bool contains(const sf::Vector2f& point) const;
};

#endif  // GAMECARD_HPP
