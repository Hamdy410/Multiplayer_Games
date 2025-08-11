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

        sf::Vector2f m_winStart;
        sf::Vector2f m_winEnd;
        
       
        /*
        *   TODO: We will need to implement these:
        *       - UI elements for the game board
        *       - Game Logic methods
        *       - Win/lose detection
        */

        sf::Font* m_font;

    public:
        XOGame(sf::Font* font);
        virtual ~XOGame() = default;

        // IGame interface implementation
        void handleEvent(const sf::Event& event) override;
        void update(float deltaTime, sf::RenderWindow& window) override;

        void draw(sf::RenderWindow& window) override;

        char checkWin();
        void displayWinner(sf::RenderWindow& window, sf::Font& font, char winner);

        void initialize() override;
        void reset() override;
        void cleanup() override;

        std::string getGameName() const override { return "Tic-Tac-Toe"; }
        bool isGameOver() const override { return m_gameOver; }
        std::string getGameStatus() const override { return m_gameStatus; }

        sf::Vector2f getCellCenter(int row, int col);




};

#endif  // XOGAME_HPP

