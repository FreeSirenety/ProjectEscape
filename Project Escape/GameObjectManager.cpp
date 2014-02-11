#include "GameObjectManager.h"
#include "GameObject.h"

namespace esc
{

	GameObjectManager::GameObjectManager(sf::RenderWindow *p_xWindow)
	{
		m_xWindow = p_xWindow;
		m_iCurrentObjectId = 0;
	}

	void GameObjectManager::updateObjects(std::vector<GameObject*> *p_vObjects, float p_fDeltaTime)
	{
		for (auto object : *p_vObjects)
		{
			object->update(p_fDeltaTime);
		}
	}

	void GameObjectManager::drawObjects(std::vector<GameObject*> *p_vObjects)
	{
		for (auto object : *p_vObjects)
		{
			m_xWindow->draw(*object);
		}
	}

	void GameObjectManager::removeObject(std::vector<GameObject*> *p_vObjects, GameObject *p_xObject)
	{
		for (auto iter = p_vObjects->begin(); iter != p_vObjects->end(); ++iter)
		{
			if (*iter == p_xObject)
			{
				delete *iter;
				*iter = nullptr;
				p_vObjects->erase(iter);
				return;
			}
		}
	}

	void GameObjectManager::cleanObjects(std::vector<GameObject*> *p_vObjects)
	{
		for (auto object : *p_vObjects)
		{
			delete object;
			object = nullptr;
		}

		p_vObjects->clear();
	}

	GameObject *GameObjectManager::createObject(sf::Vector2f p_v2fPosition, sf::Vector2f p_v2fSize, bool p_bInteractable, sf::Sprite *p_xSprite)
	{
		return new GameObject(p_v2fPosition, p_v2fSize, p_bInteractable, m_iCurrentObjectId++, p_xSprite);
	}

}