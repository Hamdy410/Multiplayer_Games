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
    // Create only the Tic-Tac-Toe card
    auto texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile(MenuConst::XO_CARD_IMAGE_PATH)) {
        // Create placeholder if image doesn't exist
        sf::Image placeholder;
        placeholder.create(CardConst::PLACEHOLDER_SIZE, CardConst::PLACEHOLDER_SIZE, sf::Color::Blue);
        texture->loadFromImage(placeholder);
        std::cout << "Warning: Could not load xo_card.png, using placeholder" << std::endl;
    }
    m_cardTextures.push_back(std::move(texture));

    auto card = std::make_unique<GameCard>(
        sf::Vector2f(0, 0), // Position will be managed by ScrollableContentArea
        sf::Vector2f(MenuConst::CARD_WIDTH, MenuConst::CARD_HEIGHT),
        m_sharedFont
    );
    
    card->setTexture(m_cardTextures.back().get());
    card->setTitle(MenuConst::XO_CARD_TITLE);
    card->setDescription(MenuConst::XO_CARD_DESCRIPTION);
    card->setOnClick([this]() {
        std::cout << "Tic-Tac-Toe game selected!" << std::endl;
        // Future: Transition to XO game state
        // m_stateManager->pushState(std::make_unique<XOGameState>(m_window, m_stateManager, m_sharedFont));
    });
    
    m_ScrollableArea->addCard(std::move(card));
    
    std::cout << "Created single Tic-Tac-Toe game card" << std::endl;
}
