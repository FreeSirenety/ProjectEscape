#include "PlayerObject.h"
#include "DrawManager.h"
#include <math.h>

PlayerObject::PlayerObject(sf::Sprite *sprite, sf::Vector2f position) : GameObject(sprite, position, false)
{
	hiding = false;
	m_interactionRange = 10.0f;
}

void PlayerObject::update(float deltaTime)
{
	m_position += m_velocity * deltaTime;

	//if sats för att kolla om musen trycks ner
	{
		int mouseX, mouseY; //Get the mouse position

		//sf::IntRect rect(mouseX, mouseY, 1, 1);
	}
}

void PlayerObject::draw(DrawManager *drawManager)
{
	drawManager->draw(this);
}

void PlayerObject::setInteractionRange(float range)
{
	m_interactionRange = range;
}

sf::Vector2f PlayerObject::getRangeToObject(GameObject *obj)
{
	sf::Vector2f length;

	length.x = fabs(obj->getPosition().x - m_position.x);
	length.y = fabs(obj->getPosition().y - m_position.y);

	return sf::Vector2f();
}