#pragma once

#include "stdafx.h"
#include "GameObject.h"

namespace esc
{

	class DrawManager;

	class PlayerObject : public GameObject
	{
	public:
		PlayerObject(sf::Sprite *sprite, sf::Vector2f position);

		virtual void update(float deltaTime);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void setInteractionRange(float range);

		sf::Vector2f getRangeToObject(GameObject *obj);

		bool hiding;

		float m_interactionRange;

	protected:


		sf::Vector2f m_velocity;
	};

}