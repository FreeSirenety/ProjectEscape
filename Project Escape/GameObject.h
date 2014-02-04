#pragma once

#include "SFML\Graphics.hpp"

class DrawManager;

class GameObject : public sf::Drawable, public sf::Transformable
{
public:
	GameObject(sf::Sprite *sprite, sf::Vector2f position, bool interactable);

	virtual void update(float deltaTime);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setSprite(sf::Sprite *sprite);
	sf::Sprite *getSprite();

	void setInteractable(bool interactable);
	bool getIsInteractable();

protected:
	sf::Sprite *m_sprite;

	sf::Vector2f m_position;
	sf::Vector2f m_size;

	bool m_interactable;
};