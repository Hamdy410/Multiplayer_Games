#include <constants/applicationconstants.hpp>
#include <core/application.hpp>
#include <core/statemanager.hpp>
#include <iostream>
#include <states/mainmenustate.hpp>


namespace AppConst = ApplicationConstants;

Application::Application()
    :
#if SFML_VERSION_MAJOR >= 3
      // SFML 3.0+ API
      m_window(
          sf::VideoMode(sf::Vector2u(
              static_cast<unsigned int>(AppConst::Window::DEFAULT_WIDTH),
              static_cast<unsigned int>(AppConst::Window::DEFAULT_HEIGHT))),
          AppConst::Window::TITLE, sf::Style::Titlebar | sf::Style::Close)
#else
      // SFML 2.x API
      m_window(sf::VideoMode(AppConst::Window::DEFAULT_WIDTH,
                             AppConst::Window::DEFAULT_HEIGHT),
               AppConst::Window::TITLE, sf::Style::Titlebar | sf::Style::Close)
#endif
{
  m_window.setFramerateLimit(AppConst::Window::FRAMERATE_LIMIT);

  loadAssets();
  initializeStates();
}

void Application::loadAssets() {
#if SFML_VERSION_MAJOR >= 3
  // SFML 3.0+ API
  if (!m_font.openFromFile(AppConst::Paths::FONT_JERSEY15)) {
    std::cout << "Warning: Could not load Jersey 15 font, trying fallback..."
              << std::endl;
  } else {
    std::cout << "Successfully loaded Jersey 15 font!" << std::endl;
  }
#else
  // SFML 2.x API
  if (!m_font.loadFromFile(AppConst::Paths::FONT_JERSEY15)) {
    std::cout << "Warning: Could not load Jersey 15 font, trying fallback..."
              << std::endl;
  } else {
    std::cout << "Successfully loaded Jersey 15 font!" << std::endl;
  }
#endif
}

void Application::initializeStates() {
  // Create state manager
  m_stateManager = std::make_unique<StateManager>(&m_window, &m_font);

  // Push the initial main menu state
  m_stateManager->pushState(std::make_unique<MainMenuState>(
      &m_window, m_stateManager.get(), &m_font));
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
#if SFML_VERSION_MAJOR >= 3
  // SFML 3.0+ API
  while (auto event = m_window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      m_window.close();
    }

    // Delegate event handling to the state manager
    m_stateManager->handleEvent(*event);
  }
#else
  // SFML 2.x API
  sf::Event event;
  while (m_window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      m_window.close();
    }

    // Delegate event handling to the state manager
    m_stateManager->handleEvent(event);
  }
#endif
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
