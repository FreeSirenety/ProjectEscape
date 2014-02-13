#include "GameState.h"
#include "GameObjectManager.h"
#include "StateManager.h"

namespace esc
{

	GameState::GameState(GameObjectManager *p_xGameObjectManager, StateManager *p_xStateManager)
	{
		m_xGameObjectManager = p_xGameObjectManager;
		m_xStateManager = p_xStateManager;
	}

	void GameState::init()
	{

	}

	void GameState::update(float p_fDeltaTime)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
		{
			m_xStateManager->setCurrentState(StateManager::EStates::MENU);
		}
		//printf("GAME");
		for (auto vGameObjects : m_vGameObjects)
		{
			m_xGameObjectManager->updateObjects(&vGameObjects, p_fDeltaTime);
		}
	}

	void GameState::draw()
	{
		for (auto vGameObjects : m_vGameObjects)
		{
			m_xGameObjectManager->drawObjects(&vGameObjects);
		}
	}

	void GameState::exit()
	{
		for (auto vGameObjects : m_vGameObjects)
		{
			m_xGameObjectManager->cleanObjects(&vGameObjects);
		}
	}

	void GameState::pause()
	{

	}


}