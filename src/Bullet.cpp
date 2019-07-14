/*
 * File: Bullet.cpp
 * Project: Project-TE
 * Created Date: Saturday July 13th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Sunday July 14th 2019 3:54:05 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include "Bullet.hpp"

Bullet::Bullet(float x, float y, float dx, float dy) : angleOfRotation(0.f), position({x, y}), velocity({dx, dy})
{
  circle.setFillColor(sf::Color::Yellow);
  circle.setRadius(2.f);
  circle.setPosition(position);
  circle.setOrigin(1.f, 1.f);
}
Bullet::~Bullet() {}

// sf::Sprite &Bullet::getSprite() { return bullet; }
sf::CircleShape &Bullet::getSprite() { return circle; }
sf::Vector2f Bullet::getPos()
{
  return circle.getPosition();
}
void Bullet::setTexture(sf::Texture &tex) { bullet.setTexture(tex); }

void Bullet::update(sf::Time t)
{
  // bullet.move(velocity * t.asSeconds());
  circle.move(velocity * t.asSeconds());
}