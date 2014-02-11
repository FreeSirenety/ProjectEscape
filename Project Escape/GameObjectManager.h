#pragma once

#include "stdafx.h"

namespace esc
{
	class GameObject;

	class GameObjectManager
	{
	public:
		GameObjectManager(sf::RenderWindow *p_xWindow);

		void updateObjects(std::vector<GameObject*> *p_vObjects, float p_fDeltaTime);

		void drawObjects(std::vector<GameObject*> *p_vObjects);

		void removeObject(std::vector<GameObject*> *p_vObjects, GameObject *p_xObject);

		void cleanObjects(std::vector<GameObject*> *p_vObjects);

		GameObject *createObject(sf::Vector2f p_v2fPosition, sf::Vector2f p_v2fSize, bool p_bInteractable, sf::Sprite *p_xSprite);

	private:
		sf::RenderWindow *m_xWindow;

		int m_iCurrentObjectId;
	};

}