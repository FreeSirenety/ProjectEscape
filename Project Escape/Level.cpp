#include "Level.h"
#include "SpriteManager.h"
#include <fstream>

namespace esc
{

	Level::Level(std::string p_sDirectoryPath, SpriteManager *p_xSpriteManager)
	{
		m_sDirectoryPath = p_sDirectoryPath;
		m_xSpriteManager = p_xSpriteManager;
	}

	void Level::loadColorCodes(std::string p_sFilePath)
	{
		std::fstream stream(m_sDirectoryPath + p_sFilePath);

		while (!stream.eof())
		{
			int r, g, b, a;

			stream >> r >> g >> b >> a;

			std::string sObjectIdentifier;

			stream >> sObjectIdentifier;

			EObjectType eObjectIdentifier;

			if (sObjectIdentifier.compare("GUARD") == 0)
				eObjectIdentifier = EObjectType::GUARD;
			else if (sObjectIdentifier.compare("PLAYER") == 0)
				eObjectIdentifier = EObjectType::PLAYER;
			else if (sObjectIdentifier.compare("WALL") == 0)
				eObjectIdentifier = EObjectType::WALL;

			sf::Color *color = new sf::Color(r, g, b, a);

			m_vColorCodes.push_back(color);

			m_mColorCodes.insert(std::pair<sf::Color*, EObjectType>(color, eObjectIdentifier));
		}

	}

	void Level::create(std::string p_sFilePath)
	{
		sf::Image xImage;
		
		xImage.loadFromFile(m_sDirectoryPath + p_sFilePath);

		for (int y = 0; y < xImage.getSize().y; y++)
		{
			for (int x = 0; x < xImage.getSize().x; x++)
			{
				sf::Color currentColor = xImage.getPixel(x, y);

				sf::Color *colorPointer = nullptr;

				for (auto color : m_vColorCodes)
				{
					if (currentColor == *color)
					{
						colorPointer = color;
						break;
					}
						
				}

				auto iterCurrentObjectType = m_mColorCodes.find(colorPointer);

				if (iterCurrentObjectType == m_mColorCodes.end())
				{
					continue;
				}

				switch (iterCurrentObjectType->second)
				{
				case esc::WALL:
				{
								  GameObject *obj = new GameObject(sf::Vector2f(x * 64, y * 64), sf::Vector2f(64, 64), false, y * 1000 + x, m_xSpriteManager->loadSprite("bullet.png", 0, 0, 32, 32));
								  m_vLevelObjects.push_back(obj);
				}
				case esc::PLAYER:
				{

				}
				case esc::GUARD:
				{

				}
				}
				
			}
		}
	}

	void Level::destroy()
	{

	}

	void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (auto object : m_vLevelObjects)
		{
			//states.transform *= getTransform();
			target.draw(*object, states);
		}
	}

}