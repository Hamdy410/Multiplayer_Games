#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include <core/basestate.hpp>

class MainMenuState : public BaseState
{
    private:
        int m_currentPatternIndex;

        void cycleBackgroundPattern();

    public:
        MainMenuState(sf::RenderWindow* window, StateManager* StateManager,
            sf::Font* font);
        
        void handleEvent(const sf::Event& event) override;
        void update(float deltaTime) override;
        void draw() override;
        void onEnter() override;
};

#endif  // MAINMENUSTATE_HPP
