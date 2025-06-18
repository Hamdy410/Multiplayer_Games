#ifndef BASESTATE_HPP
#define BASESTATE_HPP

#include <SFML/Graphics.hpp>
#include <ui/backgroundpattern.hpp>
#include <memory>

class StateManager; // Forward declaration to prevent declaration loops

class BaseState
{
    protected:
        sf::RenderWindow* m_window;
        StateManager* m_stateManager;
        sf::Font* m_sharedFont;
        std::unique_ptr<BackgroundPattern> m_backgroundPattern;

        // Common UI elements that most states will need
        sf::Text m_titleText;
        sf::RectangleShape m_contentArea;
        sf::Text m_instructionText;

        // Virtual methods for customization
        virtual void setupBackground();
        virtual void setupUI();
        virtual void setupTitle(const std::string& title);
        virtual void setupContentArea(const sf::Vector2f& position,
                const sf::Vector2f& size);
        virtual void setupInstructionText(const std::string& text);
    
    public:
            BaseState(sf::RenderWindow* window, StateManager* StateManager,
                            sf::Font* font);
            virtual ~BaseState() = default;

            // Pure virtual methods that each state must implement
            virtual void handleEvent(const sf::Event& event) = 0;
            virtual void update(float deltaTime) = 0;
            virtual void draw() = 0;

            // Optional virtual methods with default implementations
            virtual void onEnter() {}
            virtual void onExit() {}
            virtual void onPause() {}
            virtual void onResume() {}

            // Common utility methods
            void drawBackground();
            void centerText(sf::Text& text, const sf::Vector2f& center);
            void setBackgroundPattern(PatternType patter, float speed = 0.5f);
};

#endif  // BASESTATE_HPP
