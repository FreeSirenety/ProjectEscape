#include "PlayerObject.h"
#include "DrawManager.h"
#include <math.h>

namespace esc
{

	PlayerObject::PlayerObject(sf::Sprite *sprite, sf::Vector2f position, sf::RenderWindow *window) 
			: GameObject(position, sf::Vector2f(sprite->getGlobalBounds().width, sprite->getGlobalBounds().height), false, 10, sprite)
	{
		m_hiding = false;
		m_interactionRange = 30.0f;
		setOrigin(20, 17);
		p_window = window;
	}

	void PlayerObject::update(float deltaTime, std::vector<GameObject*> Hideableobjects)
	{
		//setPosition(getPosition() + m_velocity * deltaTime);
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			if (m_hiding == false)
				{
					int i = 0;
					while( i < Hideableobjects.size())
					{
						if ( fabs(getPosition().x - Hideableobjects[i]->getPosition().x) < m_interactionRange &&
							 fabs(getPosition().y - Hideableobjects[i]->getPosition().y) < m_interactionRange)
						{
					
							m_hiding = true;
							setPosition(Hideableobjects[i]->getPosition());
							setRotation(0.0f);
						}
					}
					i++;
				}
		}
		
		if (m_hiding == false)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				m_sneaking = true;
			}
			else
				m_sneaking = false;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && getPosition().y > 0)
			{
				if (m_sneaking)
					move(0, -m_sneakspeed);
				else
					move(0, -m_walkspeed);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && getPosition().y < 640)
			{
				if (m_sneaking)
					move(0, m_sneakspeed);
				else
					move(0, m_walkspeed);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && getPosition().x > 0)
			{
				if (m_sneaking)
					move(-m_sneakspeed, 0);
				else
					move(-m_walkspeed, 0);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && getPosition().x < 1024)
			{
				if (m_sneaking)
					move(m_sneakspeed, 0);
				else
					move(m_walkspeed, 0);
			}

			setRotation(calcAngle(sf::Mouse::getPosition(*p_window).x, sf::Mouse::getPosition(*p_window).y));
		}

		if (m_hiding == true)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			{
				m_hiding = false;
			}
		}
		
	}

	float PlayerObject::calcAngle(float mouse_x, float mouse_y)
	{
		sf::Vector2f direction(getPosition().x - mouse_x, getPosition().y - mouse_y);

		float angle = (float)(atan2f(direction.y, direction.x) / 0.017453292519943) + 180;

		printf("Angle: %f\n", angle);

		return angle;
		
		
		/*float x = mouse_x - getPosition().x;
		float y = mouse_y - getPosition().y;

		float hyp = sqrt((x*x) + (y*y));*/

		
	}

	void PlayerObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(*m_xSprite, states);
	}

	void PlayerObject::setInteractionRange(float range)
	{
		m_interactionRange = range;
	}

	sf::Vector2f PlayerObject::getRangeToObject(GameObject *obj)
	{
		sf::Vector2f length;

		length.x = fabs(obj->getPosition().x - getPosition().x);
		length.y = fabs(obj->getPosition().y - getPosition().y);

		return sf::Vector2f();
	}


}