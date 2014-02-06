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

		m_vCorners = relevantCorners;
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

		std::vector<Corner*> vCleanedCorners;
		std::vector<float> vDistanceToObject;

		std::vector<GameObject*> vSortedObjects;

		std::vector<GameObject*> vUnsortedObjects = *m_vObjects;

		std::vector<SDeadSector> vDeadSectors;

		float fShortest = m_fRadious;

		for (auto object : *m_vObjects)
		{
			vDistanceToObject.push_back(sqrtf((object->getPosition().x + object->getSize().x / 2 - getPosition().x) * (object->getPosition().x + object->getSize().x / 2 - getPosition().x) + (object->getPosition().y + object->getSize().y / 2 - getPosition().y) * (object->getPosition().y + object->getSize().y / 2 - getPosition().y)));
		}

		int size = vUnsortedObjects.size();

		for (int i = 0; i < size; i++)
		{
			auto iter = std::min_element(vDistanceToObject.begin(), vDistanceToObject.end());
			int index = iter - vDistanceToObject.begin();

			vSortedObjects.push_back(vUnsortedObjects[index]);

			auto removeIter = vUnsortedObjects.begin() + index;

			vDistanceToObject.erase(iter);
			vUnsortedObjects.erase(removeIter);
		}

		for (auto object : vSortedObjects)
		{
			float fDistToObject = sqrtf((object->getPosition().x + object->getSize().x / 2 - getPosition().x) * (object->getPosition().x + object->getSize().x / 2 - getPosition().x) + (object->getPosition().y + object->getSize().y / 2 - getPosition().y) * (object->getPosition().y + object->getSize().y / 2 - getPosition().y));
			std::vector<Corner*> vObjCorners = object->getCorners();

			SDeadSector DeadAddition;

			std::vector<float> vCornerAngles;

			for (auto corner : vObjCorners)
			{
				vCornerAngles.push_back(p_mCornerAngles->find(corner)->second);
			}

			auto itMinAngle = std::min_element(vCornerAngles.begin(), vCornerAngles.end());
			float fMinAngle = *itMinAngle;

			auto itMaxAngle = std::max_element(vCornerAngles.begin(), vCornerAngles.end());
			float fMaxAngle = *itMaxAngle;

			if (fMaxAngle - fMinAngle > 180)
			{
				std::vector<float> vCorrMinMax;
				for (auto angle : vCornerAngles)
				{
					if (!fabs(angle - fMinAngle) < 0.00001 && !fabs(angle - fMaxAngle) < 0.00001)
					{
						if (angle < fMaxAngle && angle > fMinAngle)
						{
							vCorrMinMax.push_back(angle);
						}
					}
				}

				fMaxAngle = *std::min_element(vCorrMinMax.begin(), vCorrMinMax.end());
				fMinAngle = *std::max_element(vCorrMinMax.begin(), vCorrMinMax.end());
			}
			float fDistToMinCorner = 0;
			float fDistToMaxCorner = 0;


			for (auto corner : vObjCorners)
			{
				float cornerAngle = p_mCornerAngles->find(corner)->second;
				float fDistToCorner = sqrtf((corner->position.x - getPosition().x) * (corner->position.x - getPosition().x) + (corner->position.y - getPosition().y) * (corner->position.y - getPosition().y));
				if (fabs(cornerAngle - fMinAngle) < 0.00001 && fabs(cornerAngle - fMinAngle) < 0.00001)
				{
					fDistToMinCorner = fDistToCorner;
				}
				else if (fabs(cornerAngle - fMaxAngle) < 0.00001 && fabs(cornerAngle - fMaxAngle) < 0.00001)
				{
					fDistToMaxCorner = fDistToCorner;
				}
			}

			DeadAddition.m_fFinishAngle = fMaxAngle;
			DeadAddition.m_fStartingAngle = fMinAngle;

			

			if (vDeadSectors.size() > 0)
			{
				for (auto corner : vObjCorners)
				{
					float fDistToCorner = sqrtf((corner->position.x - getPosition().x) * (corner->position.x - getPosition().x) + (corner->position.y - getPosition().y) * (corner->position.y - getPosition().y));
					if (m_fRadious < fDistToCorner)
					{
						continue;
					}
					bool bInSector = false;
					float cornerAngle = p_mCornerAngles->find(corner)->second;

					if (fabs(cornerAngle - fMinAngle) < 0.00001 && fabs(cornerAngle - fMinAngle) < 0.00001)
					{
						fDistToMinCorner = fDistToCorner;
						for (auto sector : vDeadSectors)
						{
							if (sector.m_fStartingAngle > sector.m_fFinishAngle)
							{
								if (cornerAngle > sector.m_fStartingAngle || cornerAngle < sector.m_fFinishAngle)
								{
									bInSector = true;
								}
							}
							else
							{
								if (cornerAngle > sector.m_fStartingAngle && cornerAngle < sector.m_fFinishAngle)
								{
									bInSector = true;
								}
							}
						}

						if (!bInSector)
						{
							vCleanedCorners.push_back(corner);
						}
					}
					else if (fabs(cornerAngle - fMaxAngle) < 0.00001 && fabs(cornerAngle - fMaxAngle) < 0.00001)
					{
						fDistToMaxCorner = fDistToCorner;
						for (auto sector : vDeadSectors)
						{
							if (sector.m_fStartingAngle > sector.m_fFinishAngle)
							{
								if (cornerAngle > sector.m_fStartingAngle || cornerAngle < sector.m_fFinishAngle)
								{
									bInSector = true;
								}
							}
							else
							{
								if (cornerAngle > sector.m_fStartingAngle && cornerAngle < sector.m_fFinishAngle)
								{
									bInSector = true;
								}
							}
						}

						if (!bInSector)
						{
							vCleanedCorners.push_back(corner);
						}
					}
					else if (fabs(fDistToCorner) < fabs(fDistToMaxCorner) && fabs(fDistToCorner) < fabs(fDistToMinCorner))
					{
						for (auto sector : vDeadSectors)
						{
							if (sector.m_fStartingAngle > sector.m_fFinishAngle)
							{
								if (cornerAngle > sector.m_fStartingAngle || cornerAngle < sector.m_fFinishAngle)
								{
									bInSector = true;
								}
							}
							else
							{
								if (cornerAngle > sector.m_fStartingAngle && cornerAngle < sector.m_fFinishAngle)
								{
									bInSector = true;
								}
							}
						}

						if (!bInSector)
						{
							vCleanedCorners.push_back(corner);
						}
					}

				}

				vDeadSectors.push_back(DeadAddition);
			}
			else
			{
				for (auto corner : vObjCorners)
				{
					float fDistToCorner = sqrtf((corner->position.x - getPosition().x) * (corner->position.x - getPosition().x) + (corner->position.y - getPosition().y) * (corner->position.y - getPosition().y));
					if (m_fRadious < fDistToCorner)
					{
						continue;
					}

					float cornerAngle = p_mCornerAngles->find(corner)->second;
					
					if (fabs(cornerAngle - fMinAngle) < 0.00001 && fabs(cornerAngle - fMinAngle) < 0.00001)
					{
						vCleanedCorners.push_back(corner);
					}
					else if (fabs(cornerAngle - fMaxAngle) < 0.00001 && fabs(cornerAngle - fMaxAngle) < 0.00001)
					{
						vCleanedCorners.push_back(corner);
					}
					else if (fabs(fDistToCorner) < fabs(fDistToMaxCorner) && fabs(fDistToCorner) < fabs(fDistToMinCorner))
					{
						vCleanedCorners.push_back(corner);
					}
				}

				vDeadSectors.push_back(DeadAddition);
			}

			*p_vCorners = vCleanedCorners;

		}
	
	}

	void createFan(std::vector<Corner*> *p_vCorners, std::map<Corner*, float> *p_mCornerAngles)
	{

	}

	float LightSource::getCornerAngle(Corner* p_xCorner)
	{
		sf::Vector2f difference(getPosition().x - p_xCorner->position.x, getPosition().y - p_xCorner->position.y);

		return (float)(atan2f(difference.y, difference.x) / 0.017453292519943) + 180;
	}

}