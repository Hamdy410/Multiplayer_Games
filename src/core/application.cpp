#include <core/application.hpp>
using namespace sf;

Application::Application() :
	m_window(VideoMode(800, 600), "Multi-Player Games")
{
	// Left empty on purpose
}

void Application::run()
{
	while (m_window.isOpen())
	{
		processEvents();
		update();
		render();
	}
}

void Application::processEvents()
{
	Event event;
	while (m_window.pollEvent(event))
		if (event.type == Event::Closed)
			m_window.close();
}

void Application::update()
{
	// Empty for now
}

void Application::render()
{
	m_window.clear(Color::White);
	m_window.display();
}

