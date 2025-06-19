#include <ui/gamecard.hpp>
#include <constants/gamecardconstants.hpp>

namespace CardConst = GameCardConstants;

GameCard::GameCard(const sf::Vector2f& position, const sf::Vector2f& size,
    sf::Font* font)
    : m_position(position), m_size(size), m_font(font), m_texture(nullptr)
{
    m_background.setPosition(m_position);
    m_background.setSize(m_size);
    m_background.setFillColor(
        sf::Color(
            CardConst::BACKGROUND_FILL_COLOR_R,
            CardConst::BACKGROUND_FILL_COLOR_G,
            CardConst::BACKGROUND_FILL_COLOR_B,
            CardConst::BACKGROUND_FILL_COLOR_A
        )
    );
    m_background.setOutlineThickness(CardConst::BACKGROUND_OUTLINE_THICKNESS);
    m_background.setOutlineColor(
        sf::Color(
            CardConst::BACKGROUND_OUTLINE_COLOR_R,
            CardConst::BACKGROUND_OUTLINE_COLOR_G,
            CardConst::BACKGROUND_OUTLINE_COLOR_B,
            CardConst::BACKGROUND_OUTLINE_COLOR_A
        )
    );

    m_title.setFont(*m_font);
    m_title.setCharacterSize(CardConst::TITLE_CHARACTER_SIZE);
    m_title.setFillColor(
        sf::Color(
            CardConst::TITLE_FILL_COLOR_R,
            CardConst::TITLE_FILL_COLOR_G,
            CardConst::TITLE_FILL_COLOR_B,
            CardConst::TITLE_FILL_COLOR_A
        )
    );

    m_description.setFont(*m_font);
    m_description.setCharacterSize(CardConst::DESCRIPTION_CHARACTER_SIZE);
    m_description.setFillColor(
        sf::Color(
            CardConst::DESCRIPTION_FILL_COLOR_R,
            CardConst::DESCRIPTION_FILL_COLOR_G,
            CardConst::DESCRIPTION_FILL_COLOR_B,
            CardConst::DESCRIPTION_FILL_COLOR_A
        )
    );
}

void GameCard::setTexture(sf::Texture* texture)
{
    m_texture = texture;
    if (m_texture)
    {
        m_icon.setTexture(*m_texture);
        // Scale icon to fit card (leaving some space for text)
        float scale = std::min(
            m_size.x * CardConst::ICON_SCALE_WIDTH_FACTOR / m_texture->getSize().x,
            m_size.y * CardConst::ICON_SCALE_HEIGHT_FACTOR / m_texture->getSize().y
        );
        m_icon.setScale(scale, scale);
        m_icon.setPosition(
            m_position.x + (m_size.x - m_texture->getSize().x * scale) / 2,
            m_position.y + CardConst::ICON_POSITION_Y_OFFSET
        );
    }
}

void GameCard::setTitle(const std::string& title)
{
    m_title.setString(title);
    auto bounds = m_title.getLocalBounds();
    m_title.setPosition(
        m_position.x + (m_size.x - bounds.width) / 2,
        m_position.y + m_size.y * CardConst::TITLE_POSITION_Y_FACTOR
    );
}

void GameCard::setDescription(const std::string& desc)
{
    m_description.setString(desc);
    auto bounds = m_description.getLocalBounds();
    m_description.setPosition(
        m_position.x + (m_size.x - bounds.width) / 2,
        m_position.y + m_size.y * CardConst::DESCRIPTION_POSITION_Y_FACTOR
    );
}

void GameCard::setOnClick(std::function<void()> callback)
{
    m_onClick = callback;
}

void GameCard::setPosition(const sf::Vector2f& position) {
    m_position = position;
    
    // Update background
    m_background.setPosition(m_position);
    
    // Recalculate and update icon position
    if (m_texture) {
        float scale = std::min(
            m_size.x * CardConst::ICON_SCALE_WIDTH_FACTOR / m_texture->getSize().x,
            m_size.y * CardConst::ICON_SCALE_HEIGHT_FACTOR / m_texture->getSize().y
        );
        m_icon.setPosition(
            m_position.x + (m_size.x - m_texture->getSize().x * scale) / 2,
            m_position.y + CardConst::ICON_POSITION_Y_OFFSET
        );
    }
    
    // Recalculate title position
    auto titleBounds = m_title.getLocalBounds();
    m_title.setPosition(
        m_position.x + (m_size.x - titleBounds.width) / 2,
        m_position.y + m_size.y * CardConst::TITLE_POSITION_Y_FACTOR
    );
    
    // Recalculate description position
    auto descBounds = m_description.getLocalBounds();
    m_description.setPosition(
        m_position.x + (m_size.x - descBounds.width) / 2,
        m_position.y + m_size.y * CardConst::DESCRIPTION_POSITION_Y_FACTOR
    );
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
        m_background.setOutlineColor(
            sf::Color(
                CardConst::HOVERED_OUTLINE_COLOR_R,
                CardConst::HOVERED_BACKGROUND_FILL_COLOR_G,
                CardConst::HOVERED_BACKGROUND_FILL_COLOR_B,
                CardConst::BACKGROUND_FILL_COLOR_A
            )
        );
        m_background.setOutlineThickness(CardConst::HOVERED_OUTLINE_THICKNESS);
    }
    else
    {
        m_background.setOutlineColor(
            sf::Color(
                CardConst::NORMAL_OUTLINE_COLOR_G,
                CardConst::NORMAL_OUTLINE_COLOR_G,
                CardConst::BACKGROUND_OUTLINE_COLOR_B,
                CardConst::BACKGROUND_OUTLINE_COLOR_A
            )
        );
        m_background.setOutlineThickness(CardConst::NORMAL_OUTLINE_THICKNESS);
    }
}

