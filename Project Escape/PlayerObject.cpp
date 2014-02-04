#include "PlayerObject.h"
#include "DrawManager.h"
#include <math.h>

namespace esc
{

	PlayerObject::PlayerObject(sf::Sprite *sprite, sf::Vector2f position) : GameObject(position, sf::Vector2f(32, 32), false, 0, sprite)
	{

		m_interactionRange = 0;
	}

	void PlayerObject::update(float deltaTime)
	{

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