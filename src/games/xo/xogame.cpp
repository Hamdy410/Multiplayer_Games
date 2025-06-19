#include <games/xo/xogame.hpp>
#include <iostream>

XOGame::XOGame() : m_currentPlayer(CellState::X), m_gameOver(false),
                   m_gameStatus("PLayer X's turn")
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
    // TODO: We will need to implement:
    //      - Draw game board
    //      - Draw X and O pieces
    //      - Draw game specific UI
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
