#pragma once

#include "GuardObject.h"
#include "DrawManager.h"
#include <math.h>

namespace esc 
{
	GuardObject::GuardObject(sf::Sprite *sprite, sf::Vector2f position, LightSource light)
	:GameObject(position, sf::Vector2f(sprite->getGlobalBounds().width, sprite->getGlobalBounds().height), true, 20, sprite)
	{
		


	};

	void GuardObject::update(float deltaTime)
	{

	};

	void GuardObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(*m_xSprite, states);
	}

}