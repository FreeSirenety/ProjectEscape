#pragma once

#include "stdafx.h"
#include "GameObject.h"

namespace esc
{

	class DrawManager;

	class PlayerObject : public GameObject
	{
	public:
		PlayerObject(sf::Sprite *p_sprite, sf::Vector2f p_position, sf::RenderWindow *p_window);

		virtual void update(float deltaTime);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void setInteractionRange(float range);

		sf::Vector2f getRangeToObject(GameObject *obj);
		
		
		float calcAngle(float x, float y);
		
		bool m_hiding;
		bool m_sneaking;

		float m_interactionRange;

	protected:
		
		float m_walkspeed = 0.4;
		float m_sneakspeed = 0.2f;
		sf::Vector2f m_velocity;
		sf::RenderWindow *p_window;
	};

}