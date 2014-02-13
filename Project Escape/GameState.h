#pragma once

#include "stdafx.h"
#include "State.h"

namespace esc
{

	class GameObjectManager;
	class StateManager;

	class GameState : public State
	{
	public:
		GameState(GameObjectManager *p_xGameObjectManager, StateManager *p_xStateManager);

		virtual void init();

		virtual void update(float p_fDeltaTime);

		virtual void draw();

		virtual void exit();

		virtual void pause();
	};

}