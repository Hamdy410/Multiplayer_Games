#include <core/application.hpp>
#include <core/statemanager.hpp>
#include <states/mainmenustate.hpp>
#include <constants/applicationconstants.hpp>
#include <iostream>

namespace AppConst = ApplicationConstants;

Application::Application() :
    m_window(sf::VideoMode(AppConst::Window::DEFAULT_WIDTH, 
                          AppConst::Window::DEFAULT_HEIGHT), 
             AppConst::Window::TITLE,
             sf::Style::Titlebar | sf::Style::Close
            )
{
    m_window.setFramerateLimit(AppConst::Window::FRAMERATE_LIMIT);
    
    loadAssets();
    initializeStates();
}

void Application::loadAssets() {
    if (!m_font.loadFromFile(AppConst::Paths::FONT_JERSEY15)) {
        std::cout << "Warning: Could not load Jersey 15 font, trying fallback..." << std::endl;
    } else {
        std::cout << "Successfully loaded Jersey 15 font!" << std::endl;
    }
}

void Application::initializeStates() {
    // Create state manager
    m_stateManager = std::make_unique<StateManager>(&m_window, &m_font);
    
    // Push the initial main menu state
    m_stateManager->pushState(std::make_unique<MainMenuState>(&m_window, m_stateManager.get(), &m_font));
}

void Application::run() {
    while (m_window.isOpen() && !m_stateManager->isEmpty()) {
        float deltaTime = m_deltaClock.restart().asSeconds();
        
        processEvents();
        update(deltaTime);
        render();
    }
}

void Application::processEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
        }
        
        // Delegate event handling to the state manager
        m_stateManager->handleEvent(event);
    }
}

void Application::update(float deltaTime) {
    // Delegate updates to the state manager
    m_stateManager->update(deltaTime);
}

void Application::render() {
    m_window.clear();
    
    // Delegate rendering to the state manager
    m_stateManager->draw();
    
    m_window.display();
}
