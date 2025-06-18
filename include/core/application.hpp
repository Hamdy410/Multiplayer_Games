#pragma once
#include <SFML/Graphics.hpp>
#include <ui/backgroundpattern.hpp>
#include <memory>

class Application {
private:
    sf::RenderWindow m_window;
    sf::Font m_font;
    sf::Text m_titleText;
    sf::Text m_instructionText;
    sf::RectangleShape m_gameArea;
    
    std::unique_ptr<BackgroundPattern> m_backgroundPattern;
    
    void loadAssets();
    void setupUI();
    void cycleBackgroundPattern();

public:
    Application();
    void run();
    void processEvents();
    void update();
    void render();
};
