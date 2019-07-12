/*
 * File: Spaceship.hpp
 * Project: Project-TE
 * Created Date: Friday July 12th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday July 12th 2019 5:23:18 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "InputHandler.hpp"

class Spaceship : public InputHandler
{
public:
Spaceship();
~Spaceship();

sf::Sprite& getSprite();
void setTexture(sf::Texture &);

private:
sf::Sprite player;
float angleOfRotation;
sf::Vector2f velocity;
sf::Vector2f position;
};

#endif