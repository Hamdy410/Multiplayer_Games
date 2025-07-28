#include <states/gamestate.hpp>
#include <core/statemanager.hpp>
#include <constants/gamestateconstants.hpp>
#include <iostream>

namespace GameConst = GameStateConstants;

GameState::GameState(sf::RenderWindow* window, StateManager* stateManager,
sf::Font* font, std::unique_ptr<IGame> gameObject)
    : BaseState(window, stateManager, font), m_gameObject(std::move(gameObject))
{
    // Setup basic page structure
    setupTitle(m_gameObject->getGameName());
    setBackgroundPattern(PatternType::WAVE_PATTERN, 0.5f);
    setupGameUI();
}

void GameState::setupGameUI()
{
    // Setup game status text
    m_gameStatusText.setFont(*m_sharedFont);
    m_gameStatusText.setCharacterSize(GameConst::STATUS_FONT_SIZE);
    m_gameStatusText.setFillColor(sf::Color::White);
    m_gameStatusText.setPosition(GameConst::STATUS_TEXT_X, GameConst::STATUS_TEXT_Y);

    // Setup back button
    m_backButton.setFont(*m_sharedFont);
    m_backButton.setCharacterSize(GameConst::BACK_BUTTON_FONT_SIZE);
    m_backButton.setFillColor(sf::Color::White);
    m_backButton.setString(GameConst::BACK_BUTTON_TEXT);
    m_backButton.setPosition(GameConst::BACK_BUTTON_X, GameConst::BACK_BUTTON_Y);
}

void GameState::handleEvent(const sf::Event& event)
{
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

    m_gameObject->handleEvent(event);
}

void GameState::update(float deltaTime, sf::RenderWindow& window)
{
    m_gameObject->update(deltaTime, window);
    updateGameStatus();
}

void GameState::updateGameStatus()
{
    m_gameStatusText.setString(m_gameObject->getGameStatus());

    // Center status text
    sf::FloatRect bounds = m_gameStatusText.getLocalBounds();
    m_gameStatusText.setPosition(
        (800 - bounds.width) / 2,
        GameConst::STATUS_TEXT_Y
    );
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

