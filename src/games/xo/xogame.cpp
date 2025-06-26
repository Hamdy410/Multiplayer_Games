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
//----- // horizontal lines
    sf::RectangleShape line1_h(sf::Vector2f(600.f, 5.f));
    line1_h.setPosition(100.f, 250.f);
    line1_h.setFillColor(sf::Color::White);

    sf::RectangleShape line2_h(sf::Vector2f(600.f, 5.f));
    line2_h.setPosition(100.f, 450.f);
    line2_h.setFillColor(sf::Color::White);

    //vertical lines
    sf::RectangleShape line1_v(sf::Vector2f(5.f, 600.f));
    line1_v.setPosition(300.f, 50.f);
    line1_v.setFillColor(sf::Color::White);

    sf::RectangleShape line2_v(sf::Vector2f(5.f, 600.f));
    line2_v.setPosition(500.f, 50.f);
    line2_v.setFillColor(sf::Color::White);
//------------//

  
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
