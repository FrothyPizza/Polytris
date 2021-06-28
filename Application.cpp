#include "Application.h"
#include "Globals.h"
#include "Render.h"

void Application::initVars() {
	m_window = nullptr;

}

void Application::initWindow() {
	m_videoMode.width = 600;
	m_videoMode.height = 800;

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
			if (m_event.key.code == Globals::CONTROLS["close"]) {
				m_window->close();
			}
			if (m_event.key.code == Globals::CONTROLS["restart"]) {
				for (auto& i : playerGame.gameState.matrix)
					for (auto& j : i)
						j = -1;
			}
			break;
		}

	}
}

void Application::update() {
	pollEvents();

	playerGame.inputRight(sf::Keyboard::isKeyPressed(Globals::CONTROLS["right"]), sf::Keyboard::isKeyPressed(Globals::CONTROLS["left"]));
	playerGame.inputLeft(sf::Keyboard::isKeyPressed(Globals::CONTROLS["left"]), sf::Keyboard::isKeyPressed(Globals::CONTROLS["right"]));

	if (sf::Keyboard::isKeyPressed(Globals::CONTROLS["soft_drop"])) {
		playerGame.inputDown();
	}
}

void Application::render() {
	// Clear
	m_window->clear(sf::Color::Black);


	//playerGame.render(m_window, sf::Vector2f(250, 150), 1);
	

	float size = m_window->getSize().x / (Globals::WIDTH) / 2 + 1;
	if (Globals::HEIGHT > Globals::WIDTH) size = m_window->getSize().y / Globals::HEIGHT * 1.2f + 1;

	int width = size * Globals::WIDTH;
	int height = size * (Globals::HEIGHT - Globals::YMARGIN);

	float center = m_window->getSize().x / 2;
	float x = center - width / 2;

	float centerY = m_window->getSize().y / 2;
	float y = centerY - height / 2;
	playerGame.render(m_window, { x, y }, size);



	// Display
	m_window->display();

}