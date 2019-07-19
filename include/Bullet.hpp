/*
 * File: Bullet.hpp
 * Project: Project-TE
 * Created Date: Saturday July 13th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday July 19th 2019 1:24:42 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#ifndef BULLET_HPP
#define BULLET_HPP

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Time.hpp>

class Bullet : public sf::CircleShape
{
public:
  Bullet(float x, float y, float dx, float dy);
  ~Bullet();

  void update(const sf::Time &t);
  bool destroy;

private:
  float angleOfRotation;
  sf::Vector2f position;
  sf::Vector2f velocity;
};

#endif