#include <ui/gamecard.hpp>

GameCard::GameCard(const sf::Vector2f& position, const sf::Vector2f& size,
    sf::Font* font)
    : m_position(position), m_size(size), m_font(font), m_texture(nullptr)
{
    m_background.setPosition(m_position);
    m_background.setSize(m_size);
    m_background.setFillColor(sf::Color(40, 40, 60, 200));
    m_background.setOutlineThickness(2.0f);
    m_background.setOutlineColor(sf::Color(100, 150, 255, 200));

    m_title.setFont(*m_font);
    m_title.setCharacterSize(22);
    m_title.setFillColor(sf::Color(180, 180, 180));

    m_description.setFont(*m_font);
    m_description.setCharacterSize(16);
    m_description.setFillColor(sf::Color(180, 180, 180));
}

void GameCard::setTexture(sf::Texture* texture)
{
    m_texture = texture;
    if (m_texture)
    {
        m_icon.setTexture(*m_texture);
        // Scale icon to fit card (leaving some space for text)
        float scale = std::min(
            m_size.x * 0.85f / m_texture->getSize().x,
            m_size.y * 0.6f / m_texture->getSize().y
        );
        m_icon.setScale(scale, scale);
        m_icon.setPosition(
            m_position.x + (m_size.x - m_texture->getSize().x * scale) / 2,
            m_position.y + 10
        );
    }
}

void GameCard::setTitle(const std::string& title)
{
    m_title.setString(title);
    auto bounds = m_title.getLocalBounds();
    m_title.setPosition(
        m_position.x + (m_size.x - bounds.width) / 2,
        m_position.y + m_size.y * 0.65f
    );
}

void GameCard::setDescription(const std::string& desc)
{
    m_description.setString(desc);
    auto bounds = m_description.getLocalBounds();
    m_description.setPosition(
        m_position.x + (m_size.x - bounds.width) / 2,
        m_position.y + m_size.y * 0.85f
    );
}

void GameCard::setOnClick(std::function<void()> callback)
{
    m_onClick = callback;
}

void GameCard::handleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    bool hovered = contains(mousePos);
    m_isHovered = hovered;

    if (hovered &&
        event.type == sf::Event::MouseButtonReleased &&
        event.mouseButton.button == sf::Mouse::Left
    )
    {
        if (m_onClick) m_onClick();
    }
}

void GameCard::update(float)
{
    m_background.setFillColor(
        m_isHovered ? sf::Color(60, 60, 90, 230) : sf::Color(40, 40, 60, 200)
    );

    updateVisuals();
}

void GameCard::draw(sf::RenderWindow& window)
{
    window.draw(m_background);
    if (m_texture) window.draw(m_icon);
    window.draw(m_title);
    window.draw(m_description);
}

bool GameCard::contains(const sf::Vector2f& point) const
{
    return m_background.getGlobalBounds().contains(point);
}

void GameCard::updateVisuals()
{
    if (m_isHovered)
    {
        m_background.setOutlineColor(sf::Color(150, 200, 255, 255));
        m_background.setOutlineThickness(3.0f);
    }
    else
    {
        m_background.setOutlineColor(sf::Color(100, 150, 255, 200));
        m_background.setOutlineThickness(2.0f);
    }
}

