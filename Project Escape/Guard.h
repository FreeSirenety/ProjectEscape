#pragma once

#include "stdafx.h"

#include "GameObject.h"

#include "LightSource.h"

namespace esc
{
	
	class PlayerObject;

	class Guard : public GameObject
	{
	public:
		Guard(sf::Vector2f p_v2fPosition, sf::Vector2f p_v2fSize, bool p_bInteractable, int p_iObjectId, PlayerObject *p_xPlayer, sf::Sprite *p_xSprite = nullptr );

		virtual void update(float p_fDeltaTime);

		float searchForPlayer(sf::Vector2f p_position);

		void setDirection();

		void setWatchSize(float p_fAngle);

		float calcAngle(float x, float y);

	private:
		bool m_bIsChasing;
		
		float m_fWatchAngle;
		float m_fWatchArea;

		PlayerObject *m_xPlayerObject;
	};

}