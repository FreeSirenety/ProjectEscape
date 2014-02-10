#pragma once

#include "GameObject.h"

#include "stdafx.h"

namespace esc
{

	class SpriteManager;

	class Level : public sf::Drawable
	{
	public:
		Level(std::string p_sDirectoryPath, SpriteManager *p_xSpriteManager);

		void loadColorCodes(std::string p_sFilePath);

		void create(std::string p_sFilePath);

		void destroy();

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		std::map<sf::Color*, EObjectType> m_mColorCodes;

		std::vector<sf::Color*> m_vColorCodes;

		std::vector<GameObject*> m_vLevelObjects;

		std::string m_sDirectoryPath;

		SpriteManager *m_xSpriteManager;
	};

}