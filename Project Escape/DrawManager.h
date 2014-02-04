#pragma once

#include "stdafx.h"

namespace esc
{

	class GameObject;

	class DrawManager
	{
	public:
		DrawManager(sf::RenderWindow *window);

		void draw(std::vector<GameObject*> *objects);

	private:
		sf::RenderWindow *m_window;
	};

}