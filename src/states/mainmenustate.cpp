#include <states/mainmenustate.hpp>
#include <core/statemanager.hpp>
#include <iostream>

MainMenuState::MainMenuState(sf::RenderWindow* window, StateManager* stateManager, sf::Font* font)
    : BaseState(window, stateManager, font), m_currentPatternIndex(0) {
    
    // Setup the UI elements using the base class methods
    setupTitle("Multi-Player Games Collection");
    setupInstructionText("Game cards will appear here\nPress SPACE to change background pattern\nPress ESC to exit");
    setBackgroundPattern(PatternType::GRID_FADE, 0.3f);
}

void MainMenuState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            m_window->close();
        }
        if (event.key.code == sf::Keyboard::Space) {
            cycleBackgroundPattern();
        }
    }
}

void MainMenuState::update(float deltaTime) {
    // Currently no specific updates needed for main menu
    // The background pattern updates are handled in drawBackground()
}

void MainMenuState::draw() {
    // Draw background pattern
    drawBackground();
    
    // Draw UI elements
    m_window->draw(m_contentArea);
    m_window->draw(m_titleText);
    m_window->draw(m_instructionText);
}

void MainMenuState::onEnter() {
    std::cout << "Entered Main Menu State" << std::endl;
}

void MainMenuState::cycleBackgroundPattern() {
    PatternType patterns[] = {
        PatternType::GRID_FADE,
        PatternType::FLOATING_PIXELS,
        PatternType::WAVE_PATTERN,
        PatternType::MATRIX_RAIN
    };
    
    m_currentPatternIndex = (m_currentPatternIndex + 1) % 4;
    
    // Set different speeds for different patterns
    float speeds[] = {0.2f, 0.5f, 0.7f, 0.8f};
    setBackgroundPattern(patterns[m_currentPatternIndex], speeds[m_currentPatternIndex]);
    
    std::cout << "Switched to pattern: " << m_currentPatternIndex << std::endl;
}
