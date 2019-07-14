/*
 * File: Bullet.hpp
 * Project: Project-TE
 * Created Date: Saturday July 13th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Sunday July 14th 2019 3:37:10 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#ifndef BULLET_HPP
#define BULLET_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Time.hpp>

class Bullet
{
public:
  Bullet(float x, float y, float dx, float dy);
  ~Bullet();
  // sf::Sprite &getSprite();
  sf::CircleShape &getSprite();
  sf::Vector2f getPos();
  void setTexture(sf::Texture &);

  void update(sf::Time t);

private:
  sf::Sprite bullet;
  sf::CircleShape circle;
  float angleOfRotation;
  sf::Vector2f position;
  sf::Vector2f velocity;
};

#endif