#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <core/basestate.hpp>
#include <games/igame.hpp>
#include <memory>

class GameState : public BaseState
{
    private:
        std::unique_ptr<IGame> m_gameObject;
        sf::Text m_gameStatusText;
        sf::Text m_backButton;

        void setupGameUI();
        void updateGameStatus();

    public:
        GameState(sf::RenderWindow* window, StateManager* stateManager,
            sf::Font* font, std::unique_ptr<IGame> gameObject);
        
        void handleEvent(const sf::Event& event) override; 
        void update(float deltaTime, sf::RenderWindow& window) override;

        void draw() override;
        void onEnter() override;
        void onExit() override;
};

#endif  // GAMESTATE_HPP
