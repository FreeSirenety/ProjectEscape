#include "Engine.h"
#include "AnimatedSprite.h"
#include "SpriteManager.h"
#include "GameObject.h"
#include "LightSource.h"

namespace esc
{

	Engine::Engine()
	{

	}

	Engine::~Engine()
	{

	}

	void Engine::initialize()
	{
		sf::ContextSettings settings;
		settings.antialiasingLevel = 16;
		m_window = new sf::RenderWindow(sf::VideoMode(1024, 640), "Plans of Futura", sf::Style::Default, settings);
	}

	void Engine::run()
	{
		sf::CircleShape circleShape(100.f);
		circleShape.setFillColor(sf::Color::Yellow);

		sf::Clock clock;

		SpriteManager spriteManager("../");

		

		AnimatedSprite *sprite = spriteManager.loadSprite("animation.txt");

		std::vector<GameObject*> objects;

		GameObject *obj = new GameObject(sf::Vector2f(100, 100), sf::Vector2f(32, 32), false, 1, sprite);

		objects.push_back(obj);

		obj = new GameObject(sf::Vector2f(132, 100), sf::Vector2f(32, 32), false, 2, sprite);

		objects.push_back(obj);

		obj = new GameObject(sf::Vector2f(164, 100), sf::Vector2f(32, 32), false, 3, sprite);

		objects.push_back(obj);

		obj = new GameObject(sf::Vector2f(100, 200), sf::Vector2f(32, 32), false, 4, sprite);

		objects.push_back(obj);

		obj = new GameObject(sf::Vector2f(300, 200), sf::Vector2f(32, 32), false, 5, sprite);

		objects.push_back(obj);
		
		LightSource light(sf::Vector2f(400, 400), 100, &objects, 360);

		while (m_window->isOpen())
		{
			sf::Event event;

			for (auto object : objects)
			{
				object->createCorners();
			}

			while (m_window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					m_window->close();
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					light.move(0, -1);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					light.move(0, 1);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					light.move(-1, 0);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					light.move(1, 0);
				}

				if (event.type == sf::Event::MouseMoved)
				{
					
				}
			}

			
			light.update(0);
			//light.setDirection(sf::Vector2f(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y));
			light.setPosition(sf::Vector2f(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y));

			sprite->update(clock.restart().asSeconds());

			m_window->clear();

			for (auto object : objects)
			{
				m_window->draw(*object);
			}
			
			m_window->draw(light);

			m_window->display();
		}
	}

	void Engine::cleanup()
	{

	}

}