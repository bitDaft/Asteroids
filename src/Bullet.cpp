/*
 * File: Bullet.cpp
 * Project: Project-TE
 * Created Date: Saturday July 13th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday July 19th 2019 1:24:42 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include "Bullet.hpp"

Bullet::Bullet(float x, float y, float dx, float dy) : destroy(false),
                                                       angleOfRotation(0.f),
                                                       position({x, y}),
                                                       velocity({dx, dy})
{
  sf::CircleShape::setFillColor(sf::Color::White);
  sf::CircleShape::setRadius(2.f);
  sf::CircleShape::setPosition(position);
  sf::CircleShape::setOrigin(1.f, 1.f);
}
Bullet::~Bullet() {}

void Bullet::update(const sf::Time &t)
{
  sf::CircleShape::move(velocity * t.asSeconds());
}