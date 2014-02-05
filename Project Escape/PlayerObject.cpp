#include "PlayerObject.h"
#include "DrawManager.h"
#include <math.h>

namespace esc
{

	PlayerObject::PlayerObject(sf::Sprite *sprite, sf::Vector2f position) : GameObject(position, sf::Vector2f(m_xSprite->getGlobalBounds().width, m_xSprite->getGlobalBounds().height), false, 10, m_xSprite)
	{
		hiding = false;
		m_interactionRange = 10.0f;
	}

	void PlayerObject::update(float deltaTime)
	{
		setPosition(getPosition() + m_velocity * deltaTime);

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