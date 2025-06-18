#include <core/statemanager.hpp>
#include <core/basestate.hpp>

StateManager::StateManager(sf::RenderWindow* window, sf::Font* font)
    : m_window(window), m_defaultFont(font)
    {
        // Left empty on purpose
    }

void StateManager::pushState(std::unique_ptr<BaseState> state)
{
    if (!m_states.empty())
        m_states.top()->onExit();
    
    m_states.push(std::move(state));
    m_states.top()->onEnter();
}

void StateManager::popState()
{
    if (!m_states.empty())
    {
        m_states.top()->onExit();
        m_states.pop();
        if (!m_states.empty())
            m_states.top()->onEnter();
    }
}

void StateManager::changeState(std::unique_ptr<BaseState> state)
{
    if (!m_states.empty())
    {
        m_states.top()->onExit();
        m_states.pop();
    }

    m_states.push(std::move(state));
    m_states.top()->onEnter();
}

void StateManager::handleEvent(const sf::Event& event)
{
    if (!m_states.empty())
        m_states.top()->handleEvent(event);
}

void StateManager::update(float deltaTime)
{
    if (!m_states.empty())
        m_states.top()->update(deltaTime);
}

void StateManager::draw()
{
    if (!m_states.empty())
        m_states.top()->draw();
}
