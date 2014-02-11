#include "MenuState.h"
#include "GameObjectManager.h"

namespace esc
{

	MenuState::MenuState(GameObjectManager *p_xGameObjectManager)
	{
		m_xGameObjectManager = p_xGameObjectManager;
	}

	void MenuState::init()
	{

	}

	void MenuState::update(float p_fDeltaTime)
	{
		for (auto vGameObjects : m_vGameObjects)
		{
			m_xGameObjectManager->updateObjects(&vGameObjects, p_fDeltaTime);
		}
	}

	void MenuState::draw()
	{
		for (auto vGameObjects : m_vGameObjects)
		{
			m_xGameObjectManager->drawObjects(&vGameObjects);
		}
	}

	void MenuState::exit()
	{
		for (auto vGameObjects : m_vGameObjects)
		{
			m_xGameObjectManager->cleanObjects(&vGameObjects);
		}
	}

	void MenuState::pause()
	{

	}

}