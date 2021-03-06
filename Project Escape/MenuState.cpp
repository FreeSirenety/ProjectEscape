#include "MenuState.h"
#include "GameObjectManager.h"
#include "StateManager.h"

namespace esc
{

	MenuState::MenuState(GameObjectManager *p_xGameObjectManager, StateManager *p_xStateManager)
	{
		m_xGameObjectManager = p_xGameObjectManager;
		m_xStateManager = p_xStateManager;
	}

	void MenuState::init()
	{

	}

	void MenuState::update(float p_fDeltaTime)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
		{
			m_xStateManager->setCurrentState(StateManager::EStates::GAME);
		}
		//printf("MENU");
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