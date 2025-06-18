#include <core/application.hpp>
#include <constants/applicationconstants.hpp>
#include <constants/backgroundconstants.hpp>
#include <iostream>

using namespace sf;

// Namespace aliases for cleaner code
namespace AppConst = ApplicationConstants;
namespace BgConst = BackgroundConstants;

Application::Application() :
    m_window(VideoMode(AppConst::Window::DEFAULT_WIDTH, 
                      AppConst::Window::DEFAULT_HEIGHT), 
             AppConst::Window::TITLE)
{
    m_window.setFramerateLimit(AppConst::Window::FRAMERATE_LIMIT);
    
    m_backgroundPattern = std::make_unique<BackgroundPattern>(&m_window, PatternType::GRID_FADE);
    m_backgroundPattern->setPixelSize(BgConst::PixelSize::DEFAULT_SIZE);
    m_backgroundPattern->setAnimationSpeed(BgConst::AnimationSpeed::GRID_FADE_DEFAULT);
    
    loadAssets();
    setupUI();
}

void Application::loadAssets()
{
    if (!m_font.loadFromFile(AppConst::Paths::FONT_JERSEY15))
        std::cout << "Warning: Could not load Jersey 15 font, trying fallback..." << std::endl;
    else
        std::cout << "Successfully loaded Jersey 15 font!" << std::endl;
}

void Application::setupUI()
{
    // Setup title with namespace aliases
    m_titleText.setFont(m_font);
    m_titleText.setString(AppConst::Window::TITLE);
    m_titleText.setCharacterSize(AppConst::UI::TITLE_FONT_SIZE);
    m_titleText.setFillColor(Color(AppConst::Colors::WHITE_R, 
                                  AppConst::Colors::WHITE_G, 
                                  AppConst::Colors::WHITE_B, 
                                  AppConst::Colors::WHITE_A));
    m_titleText.setStyle(Text::Bold);
    m_titleText.setOutlineThickness(AppConst::UI::TITLE_OUTLINE_THICKNESS);
    m_titleText.setOutlineColor(Color(AppConst::Colors::BLACK_R, 
                                     AppConst::Colors::BLACK_G, 
                                     AppConst::Colors::BLACK_B, 
                                     AppConst::Colors::BLACK_A));
    
    FloatRect titleBounds = m_titleText.getLocalBounds();
    m_titleText.setPosition((AppConst::Window::DEFAULT_WIDTH - titleBounds.width) / 2, 
                           AppConst::UI::TITLE_Y_POSITION);
    
    // Setup game area with namespace aliases
    m_gameArea.setSize(Vector2f(AppConst::UI::GAME_AREA_WIDTH, 
                               AppConst::UI::GAME_AREA_HEIGHT));
    m_gameArea.setPosition(AppConst::UI::GAME_AREA_X, 
                          AppConst::UI::GAME_AREA_Y);
    m_gameArea.setFillColor(Color(AppConst::Colors::BLACK_R, 
                                 AppConst::Colors::BLACK_G, 
                                 AppConst::Colors::BLACK_B, 
                                 AppConst::UI::GAME_AREA_BACKGROUND_ALPHA));
    m_gameArea.setOutlineThickness(AppConst::UI::GAME_AREA_OUTLINE_THICKNESS);
    m_gameArea.setOutlineColor(Color(AppConst::Colors::GAME_AREA_OUTLINE_R, 
                                    AppConst::Colors::GAME_AREA_OUTLINE_G, 
                                    AppConst::Colors::GAME_AREA_OUTLINE_B, 
                                    AppConst::UI::GAME_AREA_OUTLINE_ALPHA));
    
    // Setup instruction text with namespace aliases
    m_instructionText.setFont(m_font);
    m_instructionText.setString(AppConst::UI::INSTRUCTION_TEXT);
    m_instructionText.setCharacterSize(AppConst::UI::INSTRUCTION_FONT_SIZE);
    m_instructionText.setFillColor(Color(AppConst::Colors::INSTRUCTION_TEXT_R, 
                                        AppConst::Colors::INSTRUCTION_TEXT_G, 
                                        AppConst::Colors::INSTRUCTION_TEXT_B, 
                                        AppConst::UI::INSTRUCTION_TEXT_ALPHA));
    m_instructionText.setOutlineThickness(AppConst::UI::INSTRUCTION_OUTLINE_THICKNESS);
    m_instructionText.setOutlineColor(Color(AppConst::Colors::BLACK_R, 
                                           AppConst::Colors::BLACK_G, 
                                           AppConst::Colors::BLACK_B, 
                                           AppConst::Colors::BLACK_A));
    
    FloatRect instrBounds = m_instructionText.getLocalBounds();
    m_instructionText.setPosition(
        AppConst::Window::DEFAULT_WIDTH / 2 - instrBounds.width / 2,
        AppConst::Window::DEFAULT_HEIGHT / 2 - instrBounds.height / 2
    );
}

void Application::run()
{
    while (m_window.isOpen())
	{
        processEvents();
        update();
        render();
    }
}

void Application::processEvents() {
    Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == Event::Closed)
            m_window.close();
        
        if (event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::Escape)
                m_window.close();
            if (event.key.code == Keyboard::Space)
                cycleBackgroundPattern();
        }
    }
}

void Application::update()
{
    m_backgroundPattern->update();
}

void Application::render()
{
    m_window.clear();
    
    // Draw animated background
    m_backgroundPattern->draw();
    
    // Draw UI elements
    m_window.draw(m_gameArea);
    m_window.draw(m_titleText);
    m_window.draw(m_instructionText);
    
    m_window.display();
}

void Application::cycleBackgroundPattern()
{
    static int currentPatternIndex = 0;
    PatternType patterns[] = {
        PatternType::GRID_FADE,
        PatternType::FLOATING_PIXELS,
        PatternType::WAVE_PATTERN,
        PatternType::MATRIX_RAIN
    };
    
    currentPatternIndex = (currentPatternIndex + 1) % 4;
    m_backgroundPattern->setPattern(patterns[currentPatternIndex]);
    
    // Use namespace aliases for cleaner code
    switch (patterns[currentPatternIndex])
	{
        case PatternType::GRID_FADE:
            m_backgroundPattern->setAnimationSpeed(BgConst::AnimationSpeed::GRID_FADE_DEFAULT);
            m_backgroundPattern->setColorScheme(
                BackgroundPattern::getCyberColorScheme(),
                BackgroundPattern::getNeonColorScheme()
            );
            break;
        case PatternType::FLOATING_PIXELS:
            m_backgroundPattern->setAnimationSpeed(BgConst::AnimationSpeed::FLOATING_PIXELS_DEFAULT);
            m_backgroundPattern->setColorScheme(
                BackgroundPattern::getRetroColorScheme(),
                BackgroundPattern::getNeonColorScheme()
            );
            break;
        case PatternType::WAVE_PATTERN:
            m_backgroundPattern->setAnimationSpeed(BgConst::AnimationSpeed::WAVE_PATTERN_DEFAULT);
            m_backgroundPattern->setColorScheme(
                BackgroundPattern::getCyberColorScheme(),
                BackgroundPattern::getRetroColorScheme()
            );
            break;
        case PatternType::MATRIX_RAIN:
            m_backgroundPattern->setAnimationSpeed(BgConst::AnimationSpeed::MATRIX_RAIN_DEFAULT);
            m_backgroundPattern->setColorScheme(
                BackgroundPattern::getCyberColorScheme(),
                BackgroundPattern::getNeonColorScheme()
            );
            break;
    }
}
