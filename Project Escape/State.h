#pragma once

#include "stdafx.h"

namespace esc
{
	class GameObject;
	class GameObjectManager;
	class StateManager;

	enum EStateLayers
	{
		BACKGROUND,
		MAIN,
		FOREGROUND,
		COUNT
	};

	class State
	{
	public:
		
		virtual void init() = 0;

		virtual void update(float p_fDeltaTime) = 0;

		virtual void draw() = 0;

		virtual void exit() = 0;

		virtual void pause() = 0;

	protected:
		std::vector<GameObject*> m_vGameObjects[COUNT];

		GameObjectManager *m_xGameObjectManager;
		StateManager *m_xStateManager;
	};

}

