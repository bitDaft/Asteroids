/*
 * File: Bullet.cpp
 * Project: Project-TE
 * Created Date: Saturday July 13th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Thursday August 1st 2019 3:56:17 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include "Bullet.hpp"

Bullet::Bullet(float x, float y, float dx, float dy) : _d(false),
                                                       velocity({dx, dy})
{
  size = 2;
  sf::CircleShape::setFillColor(sf::Color::White);
  sf::CircleShape::setRadius(size);
  sf::CircleShape::setPosition({x, y});
  sf::CircleShape::setOrigin(size, size);
}
Bullet::~Bullet() {}

void Bullet::destroy()
{
  _d = true;
}
bool Bullet::isDestroyed()
{
  return _d;
}
void Bullet::update(const sf::Time &t)
{
  sf::CircleShape::move(velocity * t.asSeconds());
}
int Bullet::getSize() const
{
  return size;
}