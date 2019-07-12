/*
 * File: Spaceship.cpp
 * Project: Project-TE
 * Created Date: Friday July 12th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday July 12th 2019 5:23:18 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include "Spaceship.hpp"

Spaceship::Spaceship() : InputHandler(this)
{
}

Spaceship::~Spaceship() {}

sf::Sprite &Spaceship::getSprite()
{
  return player;
}
void Spaceship::setTexture(sf::Texture &tex)
{
  player.setTexture(tex);
}