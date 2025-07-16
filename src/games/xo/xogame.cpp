#include <games/xo/xogame.hpp>
#include <constants/applicationconstants.hpp>
#include <constants/xogameconstants.hpp>
#include <iostream>

namespace AppConst = ApplicationConstants;
namespace XOConst = XOGameConstants;

XOGame::XOGame() : m_currentPlayer(CellState::X), m_gameOver(false),
                   m_gameStatus("Player X's Turn")
{
    initialize();
}

void XOGame::handleEvent(const sf::Event& event)
{
    // TODO: We will need to implement:
    //      - Mourse click handling for board cells
    //      - Keyboard shortcuts (if required)
    std::cout << "XO Game handling event (TODO: implement)" << std::endl;
}

void XOGame::update(float deltaTime)
{
    // TODO: we will need to implement:
    //      - Game status updates
    //      - Animation updates
    std::cout << "XO Game updating (TODO: implement)" << std::endl;
}

void XOGame::draw(sf::RenderWindow& window)
{
    const float margin = XOConst::GRID_MARGIN;
    const float outerX = AppConst::UI::GAME_AREA_X;
    const float outerY = AppConst::UI::GAME_AREA_Y;
    const float outerW = AppConst::UI::GAME_AREA_WIDTH;
    const float outerH = AppConst::UI::GAME_AREA_HEIGHT;

    const float innerX = outerX + margin;
    const float innerY = outerY + margin;
    const float innerW = outerW - 2 * margin;
    const float innerH = outerH - 2 * margin;

    const float gridThickness = 8.0f;

    // Now calculate cell sizes inside the *inner* area
    float cellW = innerW / 3.0f;
    float cellH = innerH / 3.0f;

    // Vertical grid lines
    for (int i = 1; i < 3; ++i) {
        sf::RectangleShape vLine(sf::Vector2f(gridThickness, innerH));
        vLine.setPosition(innerX + i * cellW - gridThickness/2, innerY);
        vLine.setFillColor(sf::Color::White);
        vLine.setOutlineColor(sf::Color::Black);
        vLine.setOutlineThickness(3.f);
        window.draw(vLine);
    }
    // Horizontal grid lines
    for (int i = 1; i < 3; ++i) {
        sf::RectangleShape hLine(sf::Vector2f(innerW, gridThickness));
        hLine.setPosition(innerX, innerY + i * cellH - gridThickness/2);
        hLine.setFillColor(sf::Color::White);
        hLine.setOutlineColor(sf::Color::Black);
        hLine.setOutlineThickness(3.f);
        window.draw(hLine);
    }

    std::cout << "XO Game drawing (TODO: implement)" << std::endl;
}

void XOGame::initialize()
{
    // Reset board
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            m_board[i][j] = CellState::EMPTY;
        }
    }
    m_currentPlayer = CellState::X;
    m_gameStatus = "Player X's Turn";
    m_gameOver = false;
    std::cout << "XO Game initialized" << std::endl;
}

void XOGame::reset()
{
    initialize();
    std::cout << "XO Game reset" << std::endl;
}

void XOGame::cleanup()
{
    // TODO: We will need to implement cleaning up if required
    std::cout << "XO Game cleanup" << std::endl;
}
