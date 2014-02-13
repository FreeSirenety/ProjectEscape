#pragma once

#include "stdafx.h"
#include "GameObject.h"
#include "LightSource.h"

namespace esc
{

	class DrawManager;
	
	class GuardObject : public GameObject 
	{
	public:
		GuardObject(sf::Sprite *m_sprite, sf::Vector2f m_position, LightSource p_flashLight);

		virtual void update(float deltaTime);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		bool m_alert;
	};

}


