#include "game.hpp"

Game::Game() : window(sf::VideoMode(800, 600), "SFML Project")
{
    window.setFramerateLimit(60);
}

void Game::run()
{
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update()
{
    // Logic updates
}

void Game::render()
{
    window.clear();
    // Draw stuff here
    window.display();
}

