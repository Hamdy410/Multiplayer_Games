#ifndef XOGAME_HPP
#define XOGAME_HPP

#include <games/igame.hpp>
#include <SFML/Graphics.hpp>
#include <array>
#include <string>

enum class CellState
{
    EMPTY,
    X,
    O
};

class XOGame : public IGame
{
private:
    std::array<std::array<CellState, 3>, 3> m_board{};
    CellState m_currentPlayer;
    bool m_gameOver;
    std::string m_gameStatus;

    // Store the start/end points for the winner line
    sf::Vector2f m_winStart{};
    sf::Vector2f m_winEnd{};

    // Winner character: 'X', 'O', 'D' (draw), or ' ' (none yet)
    char m_winner{' '};

    sf::Font* m_font;

public:
    XOGame(sf::Font* font);
    virtual ~XOGame() = default;

    // IGame interface
    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime, sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;

    // Game logic helpers
    char checkWin(); // returns 'X', 'O', 'D', or ' '
    void displayWinner(sf::RenderWindow& window, sf::Font& font, char winner);

    void initialize() override;
    void reset() override;
    void cleanup() override;

    std::string getGameName() const override { return "Tic-Tac-Toe"; }
    bool isGameOver() const override { return m_gameOver; }
    std::string getGameStatus() const override { return m_gameStatus; }

    // Utility to compute cell center
    sf::Vector2f getCellCenter(int row, int col);
};

#endif // XOGAME_HPP
