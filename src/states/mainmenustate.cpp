#include <states/mainmenustate.hpp>
#include <core/statemanager.hpp>
#include <iostream>

MainMenuState::MainMenuState(sf::RenderWindow* window, StateManager* stateManager, sf::Font* font)
    : BaseState(window, stateManager, font), m_currentPatternIndex(0) {
    
    // Setup the UI elements using the base class methods
    setupTitle("Multi-Player Games Collection");
    setBackgroundPattern(PatternType::GRID_FADE, 0.3f);

    setupInstructionText("SPACE: Change Background • ESC: Exit");

    // Position instruction text below the content area
    sf::FloatRect instrBounds = m_instructionText.getLocalBounds();
    m_instructionText.setPosition(
        (800 - instrBounds.width) / 2,
        530
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
    
    m_currentPatternIndex = (m_currentPatternIndex + 1) % 4;
    
    // Set different speeds for different patterns
    float speeds[] = {0.2f, 0.5f, 0.7f, 0.8f};
    setBackgroundPattern(patterns[m_currentPatternIndex], speeds[m_currentPatternIndex]);
    
    std::cout << "Switched to pattern: " << m_currentPatternIndex << std::endl;
}

void MainMenuState::setupGameCards()
{
    // Example for Tic-Tac-Toe
    // Requires further modulation for scalability
    auto texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile("assets/images/xo_card.png"))
    {
        sf::Image placeholder;
        placeholder.create(64, 64, sf::Color::Blue);
        texture->loadFromImage(placeholder);
        std::cout << "Warning: Could not load xo_card.png, using placeholder\n";
    }
    m_cardTextures.push_back(std::move(texture));

    auto card = std::make_unique<GameCard>(
        sf::Vector2f(120, 200),
        sf::Vector2f(180, 230),
        m_sharedFont
    );
    card->setTexture(m_cardTextures.back().get());
    card->setTitle("Tic-Tac-Toe");
    card->setDescription("Classic XO game");
    card->setOnClick([this] () {
        std::cout << "XO Game Clicked!" << std::endl;
        // Push XO game state here
    });
    m_gameCards.push_back(std::move(card));

    // Add more cards for other games as needed...
}
