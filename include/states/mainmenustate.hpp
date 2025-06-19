#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include <core/basestate.hpp>
#include <ui/gamecard.hpp>
#include <vector>
#include <memory>

class MainMenuState : public BaseState
{
    private:
        int m_currentPatternIndex;
        std::vector<std::unique_ptr<GameCard>> m_gameCards;
        std::vector<std::unique_ptr<sf::Texture>> m_cardTextures;

        void cycleBackgroundPattern();
        void setupGameCards();

    public:
        MainMenuState(sf::RenderWindow* window, StateManager* StateManager,
            sf::Font* font);
        
        void handleEvent(const sf::Event& event) override;
        void update(float deltaTime) override;
        void draw() override;
        void onEnter() override;
};

#endif  // MAINMENUSTATE_HPP
