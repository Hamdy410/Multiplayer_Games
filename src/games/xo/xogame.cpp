#include <games/xo/xogame.hpp>
#include <constants/applicationconstants.hpp>
#include <constants/xogameconstants.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace AppConst = ApplicationConstants;
namespace XOConst = XOGameConstants;

XOGame::XOGame(sf::Font* font)
    : m_currentPlayer(CellState::X),
      m_gameOver(false),
      m_gameStatus("Player X's Turn"),
      m_font(font)
{
    initialize();
}

void XOGame::handleEvent(const sf::Event& event)
{
    if (m_gameOver) {
        // Allow reset when game is over
        if (event.type == sf::Event::KeyPressed &&
            event.key.code == sf::Keyboard::Enter) {
            reset();
        }
        return; // Ignore all other inputs while game over
    }

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left)
    {
        float margin = XOConst::GRID_MARGIN;
        float outerX = AppConst::UI::GAME_AREA_X;
        float outerY = AppConst::UI::GAME_AREA_Y;
        float outerW = AppConst::UI::GAME_AREA_WIDTH;
        float outerH = AppConst::UI::GAME_AREA_HEIGHT;

        float innerX = outerX + margin;
        float innerY = outerY + margin;
        float innerW = outerW - 2 * margin;
        float innerH = outerH - 2 * margin;
        float cellW = innerW / 3.0f;
        float cellH = innerH / 3.0f;

        sf::Vector2f mouse(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

        // Is mouse in the grid area?
        if (mouse.x >= innerX && mouse.x < innerX + innerW &&
            mouse.y >= innerY && mouse.y < innerY + innerH)
        {
            int col = static_cast<int>((mouse.x - innerX) / cellW);
            int row = static_cast<int>((mouse.y - innerY) / cellH);

            if (row >= 0 && row < 3 &&
                col >= 0 && col < 3 &&
                m_board[row][col] == CellState::EMPTY)
            {
                // 1) Place the mark
                m_board[row][col] = m_currentPlayer;

                // 2) Check result AFTER placing
                char winner = checkWin();
                if (winner != ' ') {
                    m_gameOver = true;
                    m_winner = winner; // 'X', 'O', or 'D'
                    m_gameStatus = (winner == 'D') ? "It's a Draw!"
                                 : (winner == 'X') ? "Player X Wins!" : "Player O Wins!";
                    if (winner == 'D') {
                        // Clear endpoints to avoid any accidental line draws
                        m_winStart = {};
                        m_winEnd = {};
                    }
                    return; // lock input while game over
                }

                // 3) Only switch turn if game continues
                m_currentPlayer = (m_currentPlayer == CellState::X) ? CellState::O : CellState::X;
                m_gameStatus = (m_currentPlayer == CellState::X)
                    ? "Player X's Turn" : "Player O's Turn";
            }
        }
    }

    // Debug log
    // std::cout << "XO Game handling event" << std::endl;
}

char XOGame::checkWin()
{
    // Check rows
    for (int row = 0; row < 3; row++) {
        if (m_board[row][0] != CellState::EMPTY &&
            m_board[row][0] == m_board[row][1] &&
            m_board[row][1] == m_board[row][2])
        {
            m_winStart = getCellCenter(row, 0);
            m_winEnd   = getCellCenter(row, 2);
            return (m_board[row][0] == CellState::X) ? 'X' : 'O';
        }
    }

    // Check columns
    for (int col = 0; col < 3; col++) {
        if (m_board[0][col] != CellState::EMPTY &&
            m_board[0][col] == m_board[1][col] &&
            m_board[1][col] == m_board[2][col])
        {
            m_winStart = getCellCenter(0, col);
            m_winEnd   = getCellCenter(2, col);
            return (m_board[0][col] == CellState::X) ? 'X' : 'O';
        }
    }

    // Check main diagonal (top-left to bottom-right)
    if (m_board[0][0] != CellState::EMPTY &&
        m_board[0][0] == m_board[1][1] &&
        m_board[1][1] == m_board[2][2])
    {
        m_winStart = getCellCenter(0, 0);
        m_winEnd   = getCellCenter(2, 2);
        return (m_board[0][0] == CellState::X) ? 'X' : 'O';
    }

    // Check anti-diagonal (top-right to bottom-left)
    if (m_board[0][2] != CellState::EMPTY &&
        m_board[0][2] == m_board[1][1] &&
        m_board[1][1] == m_board[2][0])
    {
        m_winStart = getCellCenter(0, 2);
        m_winEnd   = getCellCenter(2, 0);
        return (m_board[0][2] == CellState::X) ? 'X' : 'O';
    }

    // Check for draw
    bool boardFull = true;
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (m_board[row][col] == CellState::EMPTY) {
                boardFull = false;
                break;
            }
        }
        if (!boardFull) break;
    }

    if (boardFull) return 'D'; // Draw
    return ' ';                // Game ongoing
}

void XOGame::displayWinner(sf::RenderWindow& window, sf::Font& font, char winner)
{
    float boxWidth  = window.getSize().x * 0.6f;
    float boxHeight = window.getSize().y * 0.3f;

    sf::RectangleShape resultBox;
    resultBox.setSize(sf::Vector2f(boxWidth, boxHeight));
    resultBox.setFillColor(sf::Color(0, 0, 0, 200));
    resultBox.setPosition(
        (window.getSize().x - boxWidth) / 2.f,
        (window.getSize().y - boxHeight) / 2.f
    );

    sf::Text resultText;
    resultText.setFont(font);
    resultText.setCharacterSize(36);
    resultText.setFillColor(sf::Color::White);

    if (winner == 'X')
        resultText.setString("Player X Wins!");
    else if (winner == 'O')
        resultText.setString("Player O Wins!");
    else
        resultText.setString("It's a Draw!");

    // Center the text horizontally relative to the box
    auto r1 = resultText.getLocalBounds();
    resultText.setOrigin(r1.left + r1.width / 2.f, r1.top + r1.height / 2.f);
    resultText.setPosition(window.getSize().x / 2.f,
                           resultBox.getPosition().y + 0.2f * boxHeight);

    sf::Text playAgainText;
    playAgainText.setFont(font);
    playAgainText.setCharacterSize(24);
    playAgainText.setFillColor(sf::Color::White);
    playAgainText.setString("Press Enter to play again");

    auto r2 = playAgainText.getLocalBounds();
    playAgainText.setOrigin(r2.left + r2.width / 2.f, r2.top + r2.height / 2.f);
    playAgainText.setPosition(window.getSize().x / 2.f,
                              resultBox.getPosition().y + 0.7f * boxHeight);

    window.draw(resultBox);
    window.draw(resultText);
    window.draw(playAgainText);
}

void XOGame::update(float /*deltaTime*/, sf::RenderWindow& /*window*/)
{
    if (!m_gameOver) {
        m_gameStatus = (m_currentPlayer == CellState::X)
            ? "Player X's Turn"
            : "Player O's Turn";
    }
    // Debug:
    // std::cout << "XO Game updating" << std::endl;
}

sf::Vector2f XOGame::getCellCenter(int row, int col)
{
    float margin = XOConst::GRID_MARGIN;
    float innerX = ApplicationConstants::UI::GAME_AREA_X + margin;
    float innerY = ApplicationConstants::UI::GAME_AREA_Y + margin;
    float innerW = ApplicationConstants::UI::GAME_AREA_WIDTH - 2 * margin;
    float innerH = ApplicationConstants::UI::GAME_AREA_HEIGHT - 2 * margin;
    float cellW = innerW / 3.0f;
    float cellH = innerH / 3.0f;

    return sf::Vector2f(
        innerX + col * cellW + cellW / 2.f,
        innerY + row * cellH + cellH / 2.f
    );
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

    // Cell sizes in the inner area
    float cellW = innerW / 3.0f;
    float cellH = innerH / 3.0f;

    // Vertical grid lines
    for (int i = 1; i < 3; ++i) {
        sf::RectangleShape vLine(sf::Vector2f(gridThickness, innerH));
        vLine.setPosition(innerX + i * cellW - gridThickness / 2.f, innerY);
        vLine.setFillColor(sf::Color::White);
        vLine.setOutlineColor(sf::Color::Black);
        vLine.setOutlineThickness(3.f);
        window.draw(vLine);
    }

    // Horizontal grid lines
    for (int i = 1; i < 3; ++i) {
        sf::RectangleShape hLine(sf::Vector2f(innerW, gridThickness));
        hLine.setPosition(innerX, innerY + i * cellH - gridThickness / 2.f);
        hLine.setFillColor(sf::Color::White);
        hLine.setOutlineColor(sf::Color::Black);
        hLine.setOutlineThickness(3.f);
        window.draw(hLine);
    }

    // Draw X/O marks
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (m_board[row][col] != CellState::EMPTY) {
                sf::Text text;
                text.setFont(*m_font);
                text.setCharacterSize(static_cast<unsigned int>(cellH * 0.7f));
                text.setFillColor(sf::Color::White);
                text.setStyle(sf::Text::Bold);
                text.setString(m_board[row][col] == CellState::X ? "X" : "O");

                sf::FloatRect textRect = text.getLocalBounds();
                float cx = innerX + col * cellW + cellW / 2.f - textRect.width / 2.f;
                float cy = innerY + row * cellH + cellH / 2.f - textRect.height;
                text.setPosition(cx, cy);
                window.draw(text);
            }
        }
    }

    // If game over, draw winner line (only if X or O) and overlay
    if (m_gameOver) {
        if (m_winner == 'X' || m_winner == 'O') {
            sf::Vector2f direction = m_winEnd - m_winStart;
            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            if (length > 0.f) {
                const float thickness = 8.0f;
                const float outlineThickness = 5.0f;
                float angle = std::atan2(direction.y, direction.x) * 180.0f / M_PI;

                sf::RectangleShape winLine;
                winLine.setSize(sf::Vector2f(length, thickness));
                winLine.setPosition(m_winStart);
                winLine.setOrigin(0.f, thickness / 2.f);
                winLine.setRotation(angle);
                winLine.setFillColor(sf::Color::White);
                winLine.setOutlineColor(sf::Color::Black);
                winLine.setOutlineThickness(outlineThickness);
                window.draw(winLine);
            }
        }

        displayWinner(window, *m_font, m_winner);
    }

    // Debug:
    // std::cout << "XO Game drawing" << std::endl;
}

void XOGame::initialize()
{
    // Reset board
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            m_board[i][j] = CellState::EMPTY;

    m_currentPlayer = CellState::X;
    m_gameStatus = "Player X's Turn";
    m_gameOver = false;
    m_winner = ' ';
    m_winStart = {};
    m_winEnd = {};

    // std::cout << "XO Game initialized" << std::endl;
}

void XOGame::reset()
{
    initialize();
    // std::cout << "XO Game reset" << std::endl;
}

void XOGame::cleanup()
{
    // Placeholder for any resource cleanup if needed later
    // std::cout << "XO Game cleanup" << std::endl;
}
