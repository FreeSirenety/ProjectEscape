#include "Guard.h"
#include "PlayerObject.h"
#include <math.h>

namespace esc
{

	Guard::Guard(sf::Vector2f p_v2fPosition, sf::Vector2f p_v2fSize, bool p_bInteractable, int p_iObjectId, PlayerObject *p_xPlayer, sf::Sprite *p_xSprite ) : GameObject(p_v2fPosition, p_v2fSize, p_bInteractable, p_iObjectId, p_xSprite)
	{
		m_fWatchAngle = 0;
		m_fWatchArea = 0;
		setOrigin(sf::Vector2f(24, 13));
		m_bIsChasing = false;

		m_xPlayerObject = p_xPlayer;
		//light->setPosition(sf::Vector2f(getPosition().x + p_xSprite->getGlobalBounds().width/2 , getPosition().y + p_xSprite->getGlobalBounds().height/2));
	}

	void Guard::update(float p_fDeltaTime)
	{
		//m_bIsChasing = true;

		setRotation(searchForPlayer(m_xPlayerObject->getPosition()));



		if (m_bIsChasing && m_xPlayerObject != nullptr)
		{
			float xDiff = m_xPlayerObject->getPosition().x - getPosition().x;
			float yDiff = m_xPlayerObject->getPosition().y - getPosition().y;

			float fDistance = sqrtf(xDiff * xDiff + yDiff * yDiff);

			move(m_xPlayerObject->getPosition() - getPosition() / fDistance * 1.0f);
		}
	}

	float Guard::searchForPlayer(sf::Vector2f p_position)
	{
		//m_xPlayerObject->getPosition();

		sf::Vector2f direction(getPosition().x - p_position.x, getPosition().y - p_position.y);

		float angle = (float)(atan2f(direction.y, direction.x) / 0.017453292519943) + 180;

		printf("Angle: %f\n", angle);

		return angle + 90;
	}

	void Guard::setDirection()
	{

	}

	void Guard::setWatchSize(float p_fAngle)
	{

	}

}