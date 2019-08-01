/*
 * File: Bullet.hpp
 * Project: Project-TE
 * Created Date: Saturday July 13th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Thursday August 1st 2019 3:56:17 pm
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
  void destroy();
  bool isDestroyed();
  int getSize() const;

private:
  bool _d;
  const sf::Vector2f velocity;
  int size;
};

#endif