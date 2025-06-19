#ifndef XOGAME_HPP
#define XOGAME_HPP

#include <games/igame.hpp>
#include <array>

enum class CellState
{
    EMPTY,
    X,
    O
};

class XOGame : public IGame
{
    private:
        std::array<std::array<CellState, 3>, 3> m_board;
        CellState m_currentPlayer;
        bool m_gameOver;
        std::string m_gameStatus;

        /*
        *   TODO: We will need to implement these:
        *       - UI elements for the game board
        *       - Game Logic methods
        *       - Win/lose detection
        */

    public:
        XOGame();
        virtual ~XOGame() = default;

        // IGame interface implementation
        void handleEvent(const sf::Event& event) override;
        void update(float deltaTime) override;
        void draw(sf::RenderWindow& window) override;

        void initialize() override;
        void reset() override;
        void cleanup() override;

        std::string getGameName() const override { return "Tic-Tac-Toe"; }
        bool isGameOver() const override { return m_gameOver; }
        std::string getGameStatus() const override { return m_gameStatus; }
};

#endif  // XOGAME_HPP
