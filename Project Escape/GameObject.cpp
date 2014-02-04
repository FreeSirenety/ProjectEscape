#pragma once

#include "GameObject.h"


GameObject::GameObject(sf::Sprite *sprite, sf::Vector2f position, bool interactable)
{
	m_sprite = sprite;

	m_interactable = interactable;

	setPosition(position);
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(*m_sprite, states);
}

void GameObject::update(float deltaTime)
{

}

sf::Sprite *GameObject::getSprite()
{
	return m_sprite;
}