#include <states/mainmenustate.hpp>
#include <core/statemanager.hpp>
#include <constants/mainmenuconstants.hpp>
#include <constants/applicationconstants.hpp>
#include <constants/gamecardconstants.hpp>
#include <iostream>

namespace MenuConst = MainMenuConstants;
namespace CardConst = GameCardConstants;
namespace AppConst = ApplicationConstants;

MainMenuState::MainMenuState(sf::RenderWindow* window, StateManager* stateManager, sf::Font* font)
    : BaseState(window, stateManager, font), m_currentPatternIndex(0) {
    
    // Setup the UI elements using the base class methods
    setupTitle(MenuConst::MAIN_TITLE);
    setBackgroundPattern(PatternType::GRID_FADE, MenuConst::PATTERN_SPEEDS[0]);

    // Create the Scrollable Content Area
    sf::FloatRect contentBounds(
        AppConst::UI::GAME_AREA_X, 
        AppConst::UI::GAME_AREA_Y,
        AppConst::UI::GAME_AREA_WIDTH,
        AppConst::UI::GAME_AREA_HEIGHT
    );
    m_ScrollableArea = std::make_unique<ScrollableContentArea> (m_window, contentBounds);

    setupInstructionText(MenuConst::INSTRUCTION_TEXT);

    // Position instruction text below the content area
    sf::FloatRect instrBounds = m_instructionText.getLocalBounds();
    m_instructionText.setPosition(
        (AppConst::Window::DEFAULT_WIDTH - instrBounds.width) / 2,
        MenuConst::INSTRUCTION_TEXT_POSITION_Y
    );

    setupGameCards();
}

void MainMenuState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
            m_window->close();
        if (event.key.code == sf::Keyboard::Space)
            cycleBackgroundPattern();
    }

    m_ScrollableArea->handleEvent(event);
}

void MainMenuState::update(float deltaTime) {
    m_ScrollableArea->update(deltaTime);
}

void MainMenuState::draw() {
    // Draw background pattern
    drawBackground();
    
    // Draw UI elements
    m_window->draw(m_contentArea);
    m_window->draw(m_titleText);
    m_window->draw(m_instructionText);

    m_ScrollableArea->draw();
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
    
    m_currentPatternIndex = (m_currentPatternIndex + 1) % MenuConst::PATTERN_COUNT;
    
    setBackgroundPattern(
        patterns[m_currentPatternIndex],
        MenuConst::PATTERN_SPEEDS[m_currentPatternIndex]
    );
    
    std::cout << "Switched to pattern: " << m_currentPatternIndex << std::endl;
}

void MainMenuState::setupGameCards() {
    const int numberOfCards = 12;
    
    std::vector<std::string> gameNames = {
        "Tic-Tac-Toe", "Chess", "Checkers", "Connect Four", "Battleship", 
        "Reversi", "Sudoku", "Minesweeper", "Tetris", "Snake", "Pong", "Breakout"
    };
    
    std::vector<sf::Color> colors = {
        sf::Color::Blue, sf::Color::Red, sf::Color::Green, sf::Color::Yellow,
        sf::Color::Cyan, sf::Color::Magenta, sf::Color(255, 165, 0),
        sf::Color(128, 0, 128), sf::Color(255, 192, 203),
        sf::Color(0, 128, 0), sf::Color(128, 128, 128), sf::Color(255, 20, 147)
    };

    for (int i = 0; i < numberOfCards; ++i) {
        auto texture = std::make_unique<sf::Texture>();
        sf::Image placeholder;
        placeholder.create(CardConst::PLACEHOLDER_SIZE, CardConst::PLACEHOLDER_SIZE, 
                          colors[i % colors.size()]);
        texture->loadFromImage(placeholder);
        m_cardTextures.push_back(std::move(texture));

        auto card = std::make_unique<GameCard>(
            sf::Vector2f(0, 0), // Initial position - will be set by ScrollableContentArea
            sf::Vector2f(MenuConst::CARD_WIDTH, MenuConst::CARD_HEIGHT),
            m_sharedFont
        );
        
        card->setTexture(m_cardTextures.back().get());
        card->setTitle(gameNames[i % gameNames.size()]);
        card->setDescription("Game #" + std::to_string(i + 1)); // This should show 1, 2, 3, etc.
        card->setOnClick([this, i]() { // Capture i directly
            std::cout << "Game #" << (i + 1) << " clicked!" << std::endl;
        });
        
        m_ScrollableArea->addCard(std::move(card));
    }
}
