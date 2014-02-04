#include <SFML/Graphics.hpp>
#include "SpriteManager.h"
#include "DrawManager.h"
#include "GameObject.h"
#include "PlayerObject.h"
#include <SFML/Audio.hpp>
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 600), "SFML works!");

	sf::Font font;

	sf::SoundBuffer mySound;
	mySound.loadFromFile("Can.wav");

	  
		std::cout << "sound playing";
		sf::Sound sound;
		sound.setBuffer(mySound);
		sound.play();

	SpriteManager SpriteManager("../");
	DrawManager DrawManager(&window);

	sf::Sprite *sprite = SpriteManager.loadSprite("player.png", 0, 0, 32, 32);
	sf::Sprite *sprite2 = SpriteManager.loadSprite("box.png", 0, 0, 32, 32);

	font.loadFromFile("../armalite.ttf");

	//sf::Text text("HUEHUEHUEHUEHUE \nHUEHUEHUEHUEHUEHUE", font, 20);

	int position = 50;

	//text.setColor(sf::Color::Red);
	sf::Vector2f playerPos = sf::Vector2f(position,50);
	PlayerObject Player = PlayerObject(sprite, playerPos);

	sf::Vector2f boxPos = sf::Vector2f(100,100);
	GameObject Box = GameObject(sprite2, boxPos, true);

    while (window.isOpen())
    {
        sf::Event event;
        //while (window.pollEvent(event))
        //{
			if(Player.hiding == false)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					{							
						Player.move(0.1f,0);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					{
						Player.move(-0.1f,0);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
					{
						Player.move(0,-0.1f);
					}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					{
						Player.move(0,0.1f);
					}
					/*if (event.type == sf::Event::Closed)
					{
						window.close();
					}*/

					if((Player.getPosition().x - Box.getPosition().x) < Player.m_interactionRange &&
						(Player.getPosition().y - Box.getPosition().y) < Player.m_interactionRange){
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
						{
							Player.setPosition(Box.getPosition());
							Player.hiding = true;
						}
					}
			}
			if(Player.hiding == true)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
				{
					Player.hiding = false;
				}
			}
        //}

        window.clear();
		//window.draw(text);
		window.draw(Player);
		window.draw(Box);
		//window.draw(*sprite);
        window.display();
    }

    return 0;
}