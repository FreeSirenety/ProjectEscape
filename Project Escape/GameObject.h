#pragma once

#include "stdafx.h"

namespace esc
{
	class Corner;
	class DrawManager;

	class GameObject : public sf::Drawable, public sf::Transformable
	{
	public:
		GameObject(sf::Vector2f p_v2fPosition, sf::Vector2f p_v2fSize, bool p_bInteractable, int p_iObjectId, sf::Sprite *p_xSprite = nullptr);

		virtual void update(float p_fDeltaTime);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void setSprite(sf::Sprite *p_xSprite);
		sf::Sprite *getSprite();

		void setSize(sf::Vector2f p_v2fSize);
		sf::Vector2f getSize();

		void setInteractable(bool p_bInteractable);
		bool getInteractable();

		void setTransparent(bool p_bIsTransparent);
		bool getTransparent();

		void createCorners();
		std::vector<Corner*> getCorners();

		void setId(int p_iObjectId);
		int getId();

	protected:
		sf::Sprite *m_xSprite;

		std::vector<Corner*> m_vCorners;

		bool m_bInteractable;

		bool m_bIsTransparent;

		int m_iObjectId;

		sf::Vector2f m_v2fSize;
	};

}