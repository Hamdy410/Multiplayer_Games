#include <ui/gamecard.hpp>
#include <constants/gamecardconstants.hpp>

namespace CardConst = GameCardConstants;

GameCard::GameCard(const sf::Vector2f& position, const sf::Vector2f& size,
    sf::Font* font)
    : m_position(position), m_size(size), m_font(font), m_texture(nullptr)
#if SFML_VERSION_MAJOR >= 3
    // SFML 3.0+ - Initialize sf::Text with font
    , m_title(*font, "", CardConst::TITLE_CHARACTER_SIZE)
    , m_description(*font, "", CardConst::DESCRIPTION_CHARACTER_SIZE)
    // m_icon will be initialized when texture is set
#endif
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

#if SFML_VERSION_MAJOR >= 3
    // SFML 3.0+ - Font already set in constructor
    m_title.setCharacterSize(CardConst::TITLE_CHARACTER_SIZE);
    m_title.setFillColor(
        sf::Color(
            CardConst::TITLE_FILL_COLOR_R,
            CardConst::TITLE_FILL_COLOR_G,
            CardConst::TITLE_FILL_COLOR_B,
            CardConst::TITLE_FILL_COLOR_A
        )
    );

    m_description.setCharacterSize(CardConst::DESCRIPTION_CHARACTER_SIZE);
    m_description.setFillColor(
        sf::Color(
            CardConst::DESCRIPTION_FILL_COLOR_R,
            CardConst::DESCRIPTION_FILL_COLOR_G,
            CardConst::DESCRIPTION_FILL_COLOR_B,
            CardConst::DESCRIPTION_FILL_COLOR_A
        )
    );
#else
    // SFML 2.x - Set font and other properties
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
#endif
}

void GameCard::setTexture(sf::Texture* texture)
{
    m_texture = texture;
    if (m_texture)
    {
#if SFML_VERSION_MAJOR >= 3
        // SFML 3.0+ - Create sprite with texture and store in optional
        m_icon = sf::Sprite(*m_texture);
#else
        // SFML 2.x - Set texture on existing sprite
        m_icon.setTexture(*m_texture);
#endif
        
        // Scale icon to fit card (leaving some space for text)
        float scale = std::min(
            m_size.x * CardConst::ICON_SCALE_WIDTH_FACTOR / m_texture->getSize().x,
            m_size.y * CardConst::ICON_SCALE_HEIGHT_FACTOR / m_texture->getSize().y
        );
        
#if SFML_VERSION_MAJOR >= 3
        // SFML 3.0+ - Use -> for optional access
        m_icon->setScale(sf::Vector2f(scale, scale));
        m_icon->setPosition(sf::Vector2f(
            m_position.x + (m_size.x - m_texture->getSize().x * scale) / 2,
            m_position.y + CardConst::ICON_POSITION_Y_OFFSET
        ));
#else
        // SFML 2.x - Use . for direct access
        m_icon.setScale(scale, scale);
        m_icon.setPosition(
            m_position.x + (m_size.x - m_texture->getSize().x * scale) / 2,
            m_position.y + CardConst::ICON_POSITION_Y_OFFSET
        );
#endif
    }
}

void GameCard::setTitle(const std::string& title)
{
    m_title.setString(title);
    auto bounds = m_title.getLocalBounds();
    
#if SFML_VERSION_MAJOR >= 3
    // SFML 3.0+ - use .size.x and Vector2f for setPosition
    m_title.setPosition(sf::Vector2f(
        m_position.x + (m_size.x - bounds.size.x) / 2,
        m_position.y + m_size.y * CardConst::TITLE_POSITION_Y_FACTOR
    ));
#else
    // SFML 2.x - use .width and separate parameters for setPosition
    m_title.setPosition(
        m_position.x + (m_size.x - bounds.width) / 2,
        m_position.y + m_size.y * CardConst::TITLE_POSITION_Y_FACTOR
    );
#endif
}

void GameCard::setDescription(const std::string& desc)
{
    m_description.setString(desc);
    auto bounds = m_description.getLocalBounds();
    
#if SFML_VERSION_MAJOR >= 3
    // SFML 3.0+ - use .size.x and Vector2f for setPosition
    m_description.setPosition(sf::Vector2f(
        m_position.x + (m_size.x - bounds.size.x) / 2,
        m_position.y + m_size.y * CardConst::DESCRIPTION_POSITION_Y_FACTOR
    ));
#else
    // SFML 2.x - use .width and separate parameters for setPosition
    m_description.setPosition(
        m_position.x + (m_size.x - bounds.width) / 2,
        m_position.y + m_size.y * CardConst::DESCRIPTION_POSITION_Y_FACTOR
    );
#endif
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
        
#if SFML_VERSION_MAJOR >= 3
        // SFML 3.0+ - Use -> for optional access
        if (m_icon) {
            m_icon->setPosition(sf::Vector2f(
                m_position.x + (m_size.x - m_texture->getSize().x * scale) / 2,
                m_position.y + CardConst::ICON_POSITION_Y_OFFSET
            ));
        }
#else
        // SFML 2.x - Use . for direct access
        m_icon.setPosition(
            m_position.x + (m_size.x - m_texture->getSize().x * scale) / 2,
            m_position.y + CardConst::ICON_POSITION_Y_OFFSET
        );
#endif
    }
    
    // Recalculate title position
    auto titleBounds = m_title.getLocalBounds();
    
#if SFML_VERSION_MAJOR >= 3
    // SFML 3.0+ - use .size.x and Vector2f for setPosition
    m_title.setPosition(sf::Vector2f(
        m_position.x + (m_size.x - titleBounds.size.x) / 2,
        m_position.y + m_size.y * CardConst::TITLE_POSITION_Y_FACTOR
    ));
#else
    // SFML 2.x - use .width and separate parameters for setPosition
    m_title.setPosition(
        m_position.x + (m_size.x - titleBounds.width) / 2,
        m_position.y + m_size.y * CardConst::TITLE_POSITION_Y_FACTOR
    );
#endif
    
    // Recalculate description position
    auto descBounds = m_description.getLocalBounds();
    
#if SFML_VERSION_MAJOR >= 3
    // SFML 3.0+ - use .size.x and Vector2f for setPosition
    m_description.setPosition(sf::Vector2f(
        m_position.x + (m_size.x - descBounds.size.x) / 2,
        m_position.y + m_size.y * CardConst::DESCRIPTION_POSITION_Y_FACTOR
    ));
#else
    // SFML 2.x - use .width and separate parameters for setPosition
    m_description.setPosition(
        m_position.x + (m_size.x - descBounds.width) / 2,
        m_position.y + m_size.y * CardConst::DESCRIPTION_POSITION_Y_FACTOR
    );
#endif
}

void GameCard::handleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    bool hovered = contains(mousePos);
    m_isHovered = hovered;

#if SFML_VERSION_MAJOR >= 3
    // SFML 3.0+ API
    if (hovered && event.is<sf::Event::MouseButtonReleased>()) {
        const auto& mouseEvent = event.getIf<sf::Event::MouseButtonReleased>();
        if (mouseEvent->button == sf::Mouse::Button::Left) {
            if (m_onClick) m_onClick();
        }
    }
#else
    // SFML 2.x API
    if (hovered &&
        event.type == sf::Event::MouseButtonReleased &&
        event.mouseButton.button == sf::Mouse::Left
    ) {
        if (m_onClick) m_onClick();
    }
#endif
}

void GameCard::update(float)
{
    updateVisuals();
}

void GameCard::draw(sf::RenderWindow& window)
{
    window.draw(m_background);
    
#if SFML_VERSION_MAJOR >= 3
    // SFML 3.0+ - Use * to dereference optional before drawing
    if (m_texture && m_icon) {
        window.draw(*m_icon);
    }
#else
    // SFML 2.x - Direct access to sprite
    if (m_texture) {
        window.draw(m_icon);
    }
#endif
    
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
