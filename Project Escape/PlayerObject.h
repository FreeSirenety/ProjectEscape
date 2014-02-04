#pragma once

#include "stdafx.h"
#include "GameObject.h"

namespace esc
{

	class DrawManager;
	class GameObject;

	class PlayerObject : public GameObject
	{
	public:
		PlayerObject(sf::Sprite *sprite, sf::Vector2f position);

		virtual void update(float deltaTime);

		void setInteractionRange(float range);

		sf::Vector2f getRangeToObject(GameObject *obj);

	protected:
		float m_interactionRange;

		sf::Vector2f m_velocity;
	};

}