#include <states/mainmenustate.hpp>
#include <core/statemanager.hpp>
#include <constants/mainmenuconstants.hpp>
#include <constants/gamecardconstants.hpp>
#include <iostream>

namespace MenuConst = MainMenuConstants;
namespace CardConst = GameCardConstants;

MainMenuState::MainMenuState(sf::RenderWindow* window, StateManager* stateManager, sf::Font* font)
    : BaseState(window, stateManager, font), m_currentPatternIndex(0) {
    
    // Setup the UI elements using the base class methods
    setupTitle(MenuConst::MAIN_TITLE);
    setBackgroundPattern(PatternType::GRID_FADE, MenuConst::PATTERN_SPEEDS[0]);

    setupInstructionText(MenuConst::INSTRUCTION_TEXT);

    // Position instruction text below the content area
    sf::FloatRect instrBounds = m_instructionText.getLocalBounds();
    m_instructionText.setPosition(
        (MenuConst::INSTRUCTION_TEXT_POSITION_X - instrBounds.width) / 2,
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

    for (auto& card : m_gameCards)
        card->handleEvent(event, *m_window);
}

void MainMenuState::update(float deltaTime) {
    for (auto& card : m_gameCards)
        card->update(deltaTime);
}

void MainMenuState::draw() {
    // Draw background pattern
    drawBackground();
    
    // Draw UI elements
    m_window->draw(m_contentArea);
    m_window->draw(m_titleText);
    m_window->draw(m_instructionText);

    for (auto& card : m_gameCards)
        card->draw(*m_window);
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

void MainMenuState::setupGameCards()
{
    // Example for Tic-Tac-Toe
    // Requires further modulation for scalability
    auto texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile(MenuConst::XO_CARD_IMAGE_PATH))
    {
        sf::Image placeholder;
        placeholder.create(
            CardConst::PLACEHOLDER_SIZE,
            CardConst::PLACEHOLDER_SIZE,
            sf::Color(
                CardConst::PLACEHOLDER_COLOR_R,
                CardConst::PLACEHOLDER_COLOR_G,
                CardConst::PLACEHOLDER_COLOR_B
            )
        );
        texture->loadFromImage(placeholder);
        std::cout << "Warning: Could not load xo_card.png, using placeholder\n";
    }
    m_cardTextures.push_back(std::move(texture));

    auto card = std::make_unique<GameCard>(
        sf::Vector2f(
            MenuConst::CARD_POSITION_X, MenuConst::CARD_POSITION_Y
        ),
        sf::Vector2f(
            MenuConst::CARD_WIDTH, MenuConst::CARD_HEIGHT
        ),
        m_sharedFont
    );
    card->setTexture(m_cardTextures.back().get());
    card->setTitle(MenuConst::XO_CARD_TITLE);
    card->setDescription(MenuConst::XO_CARD_DESCRIPTION);
    card->setOnClick([this] () {
        std::cout << "XO Game Clicked!" << std::endl;
        // Push XO game state here
    });
    m_gameCards.push_back(std::move(card));

    // Add more cards for other games as needed...
}
