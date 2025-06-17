#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    void processEvents();
    void update();
    void render();
};

#endif // GAME_HPP

