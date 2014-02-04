#pragma once

#include "SFML\Graphics.hpp"
#include "GameObject.h"

class DrawManager;
class GameObject;

class PlayerObject : public GameObject
{
public:
	PlayerObject(sf::Sprite *sprite, sf::Vector2f position);

	virtual void update(float deltaTime);

	virtual void draw(DrawManager *drawManager);

	void setInteractionRange(float range);

	sf::Vector2f getRangeToObject(GameObject *obj);

	bool hiding;

	float m_interactionRange;
	
protected:
	

	sf::Vector2f m_velocity;
};