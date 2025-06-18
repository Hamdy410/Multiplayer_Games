#include <core/basestate.hpp>
#include <constants/applicationconstants.hpp>
#include <constants/backgroundconstants.hpp>

namespace AppConst = ApplicationConstants;
namespace BgConst = BackgroundConstants;

BaseState::BaseState(sf::RenderWindow* window, StateManager* stateManager,
        sf::Font* font)
        : m_window(window), m_stateManager(stateManager), m_sharedFont(font)
{
    setupBackground();
    setupUI();
}

void BaseState::setupBackground()
{
    m_backgroundPattern = std::make_unique<BackgroundPattern>(m_window, PatternType::GRID_FADE);
    m_backgroundPattern->setPixelSize(BgConst::PixelSize::DEFAULT_SIZE);
    m_backgroundPattern->setAnimationSpeed(BgConst::AnimationSpeed::SLOW);
}

void BaseState::setupUI()
{
    setupContentArea(
        sf::Vector2f(AppConst::UI::GAME_AREA_X, AppConst::UI::GAME_AREA_Y),
        sf::Vector2f(AppConst::UI::GAME_AREA_WIDTH, AppConst::UI::GAME_AREA_HEIGHT)
    );
}

void BaseState::setupTitle(const std::string& title)
{
    m_titleText.setFont(*m_sharedFont);
    m_titleText.setString(title);
    m_titleText.setCharacterSize(AppConst::UI::TITLE_FONT_SIZE);
    m_titleText.setFillColor(sf::Color(
        AppConst::Colors::WHITE_R,
        AppConst::Colors::WHITE_G,
        AppConst::Colors::WHITE_B,
        AppConst::Colors::WHITE_A
    ));
    m_titleText.setStyle(sf::Text::Bold);
    m_titleText.setOutlineThickness(AppConst::UI::TITLE_OUTLINE_THICKNESS);
    m_titleText.setOutlineColor(sf::Color(
        AppConst::Colors::BLACK_R,
        AppConst::Colors::BLACK_G,
        AppConst::Colors::BLACK_B,
        AppConst::Colors::BLACK_A
    ));

    centerText(m_titleText, sf::Vector2(AppConst::Window::DEFAULT_WIDTH / 2,
        AppConst::UI::TITLE_Y_POSITION));
}

void BaseState::setupContentArea(const sf::Vector2f& position, const sf::Vector2f& size)
{
    m_contentArea.setPosition(position);
    m_contentArea.setSize(size);
    m_contentArea.setFillColor(
        sf::Color(
            AppConst::Colors::BLACK_R,
            AppConst::Colors::BLACK_G,
            AppConst::Colors::BLACK_B,
            AppConst::UI::GAME_AREA_BACKGROUND_ALPHA
        )
    );
    m_contentArea.setOutlineThickness(AppConst::UI::GAME_AREA_OUTLINE_THICKNESS);
    m_contentArea.setOutlineColor(
        sf::Color(
            AppConst::Colors::GAME_AREA_OUTLINE_R,
            AppConst::Colors::GAME_AREA_OUTLINE_G,
            AppConst::Colors::GAME_AREA_OUTLINE_B,
            AppConst::UI::GAME_AREA_OUTLINE_ALPHA
        )
    );
}

void BaseState::setupInstructionText(const std::string& text)
{
    m_instructionText.setFont(*m_sharedFont);
    m_instructionText.setString(text);
    m_instructionText.setCharacterSize(AppConst::UI::INSTRUCTION_FONT_SIZE);
    m_instructionText.setFillColor(
        sf::Color(
            AppConst::Colors::INSTRUCTION_TEXT_R,
            AppConst::Colors::INSTRUCTION_TEXT_G,
            AppConst::Colors::INSTRUCTION_TEXT_B,
            AppConst::UI::INSTRUCTION_TEXT_ALPHA
        )
    );
    m_instructionText.setOutlineThickness(AppConst::UI::INSTRUCTION_OUTLINE_THICKNESS);
    m_instructionText.setOutlineColor(
        sf::Color(
            AppConst::Colors::BLACK_R,
            AppConst::Colors::BLACK_G,
            AppConst::Colors::BLACK_B,
            AppConst::Colors::BLACK_A
        )
    );
    centerText(m_instructionText, sf::Vector2f(
        AppConst::Window::DEFAULT_WIDTH / 2.0f,
        AppConst::Window::DEFAULT_HEIGHT / 2.0f
    ));
}

void BaseState::drawBackground()
{
    if(m_backgroundPattern)
    {
        m_backgroundPattern->update();
        m_backgroundPattern->draw();
    }
}

void BaseState::centerText(sf::Text& text, const sf::Vector2f& center)
{
    sf::FloatRect bounds = text.getLocalBounds();
    text.setPosition(center.x - bounds.width / 2, center.y - bounds.height / 2);
}

void BaseState::setBackgroundPattern(PatternType pattern, float speed)
{
    if (m_backgroundPattern)
    {
        m_backgroundPattern->setPattern(pattern);
        m_backgroundPattern->setAnimationSpeed(speed);
    }
}
