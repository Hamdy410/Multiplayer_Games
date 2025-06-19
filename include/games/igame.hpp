#ifndef IGAME_HPP
#define IGAME_HPP

#include <SFML/Graphics.hpp>

class IGame
{
    public:
        virtual ~IGame() = default;

        // Core game interface methods
        virtual void handleEvent(const sf::Event& event) = 0;
        virtual void update(float deltaTime) = 0;
        virtual void draw(sf::RenderWindow& window) = 0;

        // Game lifecycle methods
        virtual void initialize() = 0;
        virtual void reset() = 0;
        virtual void cleanup() = 0;

        // Game information
        virtual std::string getGameName() const = 0;
        virtual bool isGameOver() const = 0;
        virtual std::string getGameStatus() const = 0;
};

#endif  // IGAME_HPP
