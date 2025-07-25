#include <games/xo/xogame.hpp>
#include <constants/applicationconstants.hpp>
#include <constants/xogameconstants.hpp>
#include <iostream>

namespace AppConst = ApplicationConstants;
namespace XOConst = XOGameConstants;

XOGame::XOGame(sf::Font* font) : m_currentPlayer(CellState::X), m_gameOver(false),
                   m_gameStatus("Player X's Turn"), m_font(font)
{
    initialize();
}

void XOGame::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
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
        if (
            mouse.x >= innerX && mouse.x < innerX + innerW &&
            mouse.y >= innerY && mouse.y < innerY + innerH
        ) {
            int col = (mouse.x - innerX) / cellW;
            int row = (mouse.y - innerY) / cellH;
            if (row >= 0 && row < 3 && col >= 0 && col < 3 && m_board[row][col] == CellState::EMPTY) {
                m_board[row][col] = m_currentPlayer;
                m_currentPlayer = (m_currentPlayer == CellState::X) ? CellState::O : CellState::X;
                m_gameStatus = (m_currentPlayer == CellState::X) ? "Player X's Turn" : "Player O's Turn";
            }
        }
    }
    std::cout << "XO Game handling event (TODO: implement)" << std::endl;
}

char checkWin()
{
  
}

void displayWinner(sf::RenderWindow& window, sf::Font& font, char winner)
{
    float boxWidth = window.getSize().x * 0.6f;
    float boxHeight = window.getSize().y * 0.3f;

    sf::RectangleShape resultBox;
    resultBox.setSize(sf::Vector2f(boxWidth, boxHeight));
    resultBox.setFillColor(sf::Color(0, 0, 0, 200)); 
    resultBox.setPosition(
        (window.getSize().x - boxWidth) / 2,
        (window.getSize().y - boxHeight) / 2
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

    resultText.setPosition(
        window.getSize().x / 2 - resultText.getGlobalBounds().width / 2,
        resultBox.getPosition().y + 0.1*boxHeight
    );


    sf::Text playAgainText;
    playAgainText.setFont(font);
    playAgainText.setCharacterSize(24);
    playAgainText.setFillColor(sf::Color::White);
    playAgainText.setString("Press Enter to play again");

    playAgainText.setPosition(
        window.getSize().x / 2 - playAgainText.getGlobalBounds().width / 2,
        resultText.getPosition().y + 0.5*boxHeight
    );


    window.draw(resultBox);
    window.draw(resultText);
    window.draw(playAgainText);
}

void XOGame::update(float deltaTime)
{
    // TODO: we will need to implement:
    //      - Game status updates
    //      - Animation updates
    if (!m_gameOver) {
        m_gameStatus = (m_currentPlayer == CellState::X)
            ? "Player X's Turn"
            : "Player O's Turn";
    }
    std::cout << "XO Game updating (TODO: implement)" << std::endl;

  char winner = checkWin();
    if (winner != ' ' && !gameOver)
    {
        gameOver = true;
        displayWinner(*window, font, winner);
    }
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

    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (m_board[row][col] != CellState::EMPTY) {
                sf::Text text;
                text.setFont(*m_font);
                text.setCharacterSize(cellH * 0.7f);
                text.setFillColor(sf::Color::White);
                text.setStyle(sf::Text::Bold);

                text.setString(m_board[row][col] == CellState::X? "X" : "O");

                sf::FloatRect textRect = text.getLocalBounds();
                float cx = innerX + col * cellW + cellW / 2 - textRect.width / 2;
                float cy = innerY + row * cellH + cellH / 2 - textRect.height;
                text.setPosition(cx, cy);
                window.draw(text);
            }
        }
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
