#ifndef STATEMANAGER_HPP
#define STATEMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <core/basestate.hpp>
#include <memory>
#include <stack>

class StateManager
{
    private:
        std::stack<std::unique_ptr<BaseState>> m_states;
        sf::RenderWindow* m_window;
        sf::Font* m_defaultFont;
    
    public:
        StateManager(sf::RenderWindow* m_window, sf::Font* font);

        void pushState(std::unique_ptr<BaseState> state);
        void popState();
        void changeState(std::unique_ptr<BaseState> state);

        void handleEvent(const sf::Event& event);
        void update(float deltaTime);
        void draw();

        bool isEmpty() const { return m_states.empty(); }
        sf::RenderWindow* getWindow() const { return m_window; }
        sf::Font* getDefaultFont() const { return m_defaultFont; }
};

#endif  // STATEMANAGER_HPP
