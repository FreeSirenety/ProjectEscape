#include "LightSource.h"
#include "GameObject.h"
#include "Corner.h"

namespace esc
{

	LightSource::LightSource(sf::Vector2f p_v2fPosition, float p_fRadious, std::vector<GameObject*> *p_vObjects, float p_fAngleWidth)
	{
		setPosition(p_v2fPosition);
		m_fRadious = p_fRadious;
		m_vObjects = p_vObjects;

		m_fLightWidthAngle = p_fAngleWidth;
	}

	LightSource::LightSource(sf::Vector2f p_v2fPosition, sf::Vector2f p_v2fSize, float p_fRadious, std::vector<GameObject*> *p_vObjects, float p_fAngleWidth)
	{
		setPosition(p_v2fPosition);
		m_fRadious = p_fRadious;
		m_vObjects = p_vObjects;
		m_v2fSize = p_v2fSize;

		m_fLightWidthAngle = p_fAngleWidth;
		m_fMiddleAngle = 0;
		m_fStartAngle = m_fMiddleAngle - m_fLightWidthAngle / 2;
	}
	
	void LightSource::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (auto corner : m_vCorners)
		{
			sf::VertexArray line(sf::PrimitiveType::Lines, 2);
			line[0] = *corner;
			line[1] = *corner;

			line[1].position = getPosition();
			target.draw(line, states);
		}
	}

	void LightSource::setRadious(float p_fRadious)
	{
		m_fRadious = p_fRadious;
	}

	float LightSource::getRadious()
	{
		return m_fRadious;
	}

	void LightSource::setDirection(sf::Vector2f p_v2fDirection)
	{
		sf::Vector2f direction(getPosition().x - p_v2fDirection.x, getPosition().y - p_v2fDirection.y);

		m_fMiddleAngle = (float)(atan2f(direction.y, direction.x) / 0.017453292519943) + 180;
		m_fStartAngle = m_fMiddleAngle - m_fLightWidthAngle / 2;

		if (m_fStartAngle < 0)
		{
			m_fStartAngle += 360;
		}
		else if (m_fStartAngle > 360)
		{
			m_fStartAngle -= 360;
		}
	}

	float LightSource::getDirectionAngle()
	{
		return m_fMiddleAngle;
	}

	void LightSource::update(float p_fDeltaTime)
	{
		createLight();
	}

	void LightSource::createLight()
	{
		std::vector<Corner*> relevantCorners;

		std::map<Corner*, float> cornerAngles;

		getRelevantCorners(&relevantCorners, &cornerAngles);
	}

	void LightSource::getRelevantCorners(std::vector<Corner*> *p_vCorners, std::map<Corner*, float> *p_mCornerAngles)
	{
		m_vCorners.clear();

		for (auto object : *m_vObjects)
		{
			for (auto corner : object->getCorners())
			{
				corner->color = sf::Color::Red;
				corner->setDistanceToSource(getPosition());
				m_vCorners.push_back(corner);

				float fCornerAngle = getCornerAngle(corner);

				p_mCornerAngles->insert(std::pair<Corner*, float>(corner, fCornerAngle));
			}
		}

		for (auto corner : m_vCorners)
		{
			if (m_fRadious >= corner->getDistanceToSource())
			{
				float fEndAngle = m_fStartAngle + m_fLightWidthAngle;

				if (fEndAngle > 360)
					fEndAngle -= 360;

				float cornerAngle = p_mCornerAngles->find(corner)->second;

				if (m_fStartAngle > fEndAngle)
				{
					if (cornerAngle > m_fStartAngle || cornerAngle < fEndAngle)
					{
						p_vCorners->push_back(corner);
					}
				}
				else
				{
					if (cornerAngle > m_fStartAngle && cornerAngle < fEndAngle)
					{
						p_vCorners->push_back(corner);
					}
				}
				
			}
		}

		std::vector<SDeadSector> vDeadSectors;

		float shortest = m_fRadious;

		std::vector<Corner*> vClosestObjCorners;

		Corner *closestCorner = nullptr;

		for (auto corner : *p_vCorners)
		{
			float currentDistance = corner->getDistanceToSource();

			if (shortest > currentDistance)
			{
				shortest = currentDistance;
				closestCorner = corner;
			}
				
		}

		if (closestCorner != nullptr)
		{
			for (auto corner : *p_vCorners)
			{
				if (corner->getId() == closestCorner->getId())
				{
					corner->color = sf::Color::Green;
					vClosestObjCorners.push_back(corner);
				}
			}

			std::vector<float> vCornerAngles;
			for (auto corner : vClosestObjCorners)
			{
				vCornerAngles.push_back(p_mCornerAngles->find(corner)->second);
			}

			SDeadSector firstDead;

			//float minAngle = std::min_element(vCornerAngles.begin(), vCornerAngles.begin())
		}

		m_vCorners = *p_vCorners;
	}

	float LightSource::getCornerAngle(Corner* p_xCorner)
	{
		sf::Vector2f difference(getPosition().x - p_xCorner->position.x, getPosition().y - p_xCorner->position.y);

		return (float)(atan2f(difference.y, difference.x) / 0.017453292519943) + 180;
	}

}