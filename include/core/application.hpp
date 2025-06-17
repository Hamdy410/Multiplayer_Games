#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics.hpp>

class Application
{
	public:
		Application();
		void run();
	protected:
		void processEvents();
		void update();
		void render();

		sf::RenderWindow m_window;
};

#endif	// APPLICATION_HPP
