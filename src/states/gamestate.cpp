#include <states/gamestate.hpp>
#include <core/statemanager.hpp>
#include <constants/gamestateconstants.hpp>
#include <iostream>

namespace GameConst = GameStateConstants;

GameState::GameState(sf::RenderWindow* window, StateManager* stateManager,
sf::Font* font, std::unique_ptr<IGame> gameObject)
    : BaseState(window, stateManager, font), m_gameObject(std::move(gameObject))
#if SFML_VERSION_MAJOR >= 3
    // SFML 3.0+ - Initialize sf::Text members with font
    , m_gameStatusText(*font, "", GameConst::STATUS_FONT_SIZE)
    , m_backButton(*font, GameConst::BACK_BUTTON_TEXT, GameConst::BACK_BUTTON_FONT_SIZE)
#endif
{
    // Setup basic page structure
    setupTitle(m_gameObject->getGameName());
    setBackgroundPattern(PatternType::WAVE_PATTERN, 0.5f);
    setupGameUI();
}

void GameState::setupGameUI()
{
    // Setup game status text
#if SFML_VERSION_MAJOR >= 3
    // SFML 3.0+ - Font already set in constructor
    m_gameStatusText.setCharacterSize(GameConst::STATUS_FONT_SIZE);
    m_gameStatusText.setFillColor(sf::Color::White);
    m_gameStatusText.setPosition(sf::Vector2f(GameConst::STATUS_TEXT_X, GameConst::STATUS_TEXT_Y));
#else
    // SFML 2.x - Set font and other properties
    m_gameStatusText.setFont(*m_sharedFont);
    m_gameStatusText.setCharacterSize(GameConst::STATUS_FONT_SIZE);
    m_gameStatusText.setFillColor(sf::Color::White);
    m_gameStatusText.setPosition(GameConst::STATUS_TEXT_X, GameConst::STATUS_TEXT_Y);
#endif

    // Setup back button
#if SFML_VERSION_MAJOR >= 3
    // SFML 3.0+ - Font and text already set in constructor
    m_backButton.setCharacterSize(GameConst::BACK_BUTTON_FONT_SIZE);
    m_backButton.setFillColor(sf::Color::White);
    m_backButton.setPosition(sf::Vector2f(GameConst::BACK_BUTTON_X, GameConst::BACK_BUTTON_Y));
#else
    // SFML 2.x - Set font and other properties
    m_backButton.setFont(*m_sharedFont);
    m_backButton.setCharacterSize(GameConst::BACK_BUTTON_FONT_SIZE);
    m_backButton.setFillColor(sf::Color::White);
    m_backButton.setString(GameConst::BACK_BUTTON_TEXT);
    m_backButton.setPosition(GameConst::BACK_BUTTON_X, GameConst::BACK_BUTTON_Y);
#endif
}

void GameState::handleEvent(const sf::Event& event)
{
#if SFML_VERSION_MAJOR >= 3
    // SFML 3.0+ API
    // Handle common events
    if (event.is<sf::Event::KeyPressed>())
    {
        const auto& keyEvent = event.getIf<sf::Event::KeyPressed>();
        if (keyEvent->code == sf::Keyboard::Key::Escape)
        {
            m_stateManager->popState();
            return;
        }
        if (keyEvent->code == sf::Keyboard::Key::R && m_gameObject->isGameOver())
        {
            m_gameObject->reset();
            return;
        }
    }

    // Handle the button click
    if (event.is<sf::Event::MouseButtonPressed>())
    {
        const auto& mouseEvent = event.getIf<sf::Event::MouseButtonPressed>();
        if (mouseEvent->button == sf::Mouse::Button::Left)
        {
            sf::Vector2f mousePos(mouseEvent->position.x, mouseEvent->position.y);
            if (m_backButton.getGlobalBounds().contains(mousePos))
            {
                m_stateManager->popState();
                return;
            }
        }
    }
#else
    // SFML 2.x API
    // Handle common events
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            m_stateManager->popState();
            return;
        }
        if (event.key.code == sf::Keyboard::R && m_gameObject->isGameOver())
        {
            m_gameObject->reset();
            return;
        }
    }

    // Handle the button click
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (m_backButton.getGlobalBounds().contains(mousePos))
        {
            m_stateManager->popState();
            return;
        }
    }
#endif

    m_gameObject->handleEvent(event);
}

void GameState::update(float deltaTime)
{
    m_gameObject->update(deltaTime);
    updateGameStatus();
}

void GameState::updateGameStatus()
{
    m_gameStatusText.setString(m_gameObject->getGameStatus());

    // Center status text
    sf::FloatRect bounds = m_gameStatusText.getLocalBounds();
    
#if SFML_VERSION_MAJOR >= 3
    // SFML 3.0+ - use .size.x and Vector2f for setPosition
    m_gameStatusText.setPosition(sf::Vector2f(
        (800 - bounds.size.x) / 2,
        GameConst::STATUS_TEXT_Y
    ));
#else
    // SFML 2.x - use .width and separate parameters for setPosition
    m_gameStatusText.setPosition(
        (800 - bounds.width) / 2,
        GameConst::STATUS_TEXT_Y
    );
#endif
}

void GameState::draw()
{
    // Draw base elements
    drawBackground();
    m_window->draw(m_contentArea);
    m_window->draw(m_titleText);
    m_window->draw(m_gameStatusText);
    m_window->draw(m_backButton);

    m_gameObject->draw(*m_window);
}

void GameState::onEnter()
{
    std::cout << GameConst::DEBUG_ENTERED_GAME << m_gameObject->getGameName() << std::endl;
    m_gameObject->initialize();
}

void GameState::onExit()
{
    m_gameObject->cleanup();
}
