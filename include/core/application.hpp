#pragma once
#include <SFML/Graphics.hpp>
#include <core/statemanager.hpp>
#include <memory>

class Application {
private:
    sf::RenderWindow m_window;
    sf::Font m_font;
    sf::Clock m_deltaClock;
    
    std::unique_ptr<StateManager> m_stateManager;
    
    void loadAssets();
    void initializeStates();

public:
    Application();
    void run();
    void processEvents();
    void update(float deltaTime, sf::RenderWindow& window);
    void render();
};

