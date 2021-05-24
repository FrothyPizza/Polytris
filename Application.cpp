#include "Application.h"
#include "Globals.h"
#include "Render.h"

void Application::initVars() {
	m_window = nullptr;

}

void Application::initWindow() {
	m_videoMode.width = 1000;
	m_videoMode.height = 1000;

	m_window = new sf::RenderWindow(m_videoMode, "Polytris", sf::Style::Titlebar | sf::Style::Close);
}

Application::Application() : playerGame{} {
	initVars();
	initWindow();


}

Application::~Application() {
	delete m_window;
}

const bool Application::running() const {
	return m_window->isOpen();
}

void Application::pollEvents() {
	while (m_window->pollEvent(m_event)) {
		switch (m_event.type) {
		case sf::Event::Closed:
			m_window->close();
			break;

		case sf::Event::KeyPressed:
			playerGame.inputGeneral(m_event.key.code);
			switch (m_event.key.code) {
			case sf::Keyboard::Escape:
				m_window->close();
				break;
			case sf::Keyboard::Q:
				break;


			}

			break;
		}

	}
}

void Application::update() {
	pollEvents();

	playerGame.inputRight(sf::Keyboard::isKeyPressed(sf::Keyboard::Right));
	playerGame.inputLeft(sf::Keyboard::isKeyPressed(sf::Keyboard::Left));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		playerGame.inputDown();
	}
}

void Application::render() {
	// Clear
	m_window->clear(sf::Color::Black);


	playerGame.render(m_window, sf::Vector2f(250, 50), 20);

	



	// Display
	m_window->display();

}