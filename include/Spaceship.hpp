/*
 * File: Spaceship.hpp
 * Project: Project-TE
 * Created Date: Friday July 12th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday July 19th 2019 1:50:59 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "InputHandler.hpp"
#include "Bullet.hpp"

#include <iostream>

enum Actions
{
  MOUSE_LEFT,
  MOUSE_LEFT_RELEASE,
  MOUSE_RIGHT,
  MOUSE_RIGHT_RELEASE,
  MOUSE_MIDDLE,
  MOUSE_MIDDLE_RELEASE,
  MOUSE_X1,
  MOUSE_X1_RELEASE,
  MOUSE_X2,
  MOUSE_X2_RELEASE,
  MOUSE_MOVED,
  MOUSE_SCROLL,
  UP,
  DOWN,
  LEFT,
  RIGHT,
  SPACE,
  UP_RELEASE,
  DOWN_RELEASE,
  LEFT_RELEASE,
  RIGHT_RELEASE,
  SPACE_RELEASE,
  QUIT
};

class Spaceship : public InputHandler
{
public:
  Spaceship(sf::RenderWindow &);
  ~Spaceship();

  const sf::Sprite &getSprite();
  Bullet *getBullet();
  void setTexture(sf::Texture &);

  void update(const sf::Time &t);

private:
  sf::RenderWindow &rwin;
  sf::Sprite ship;
  float angleOfRotation;
  sf::Vector2f velocity;
  sf::Vector2f position;
  float rotate;
  bool thrustF;
  Bullet *b;

  sf::Time moveTimeout;

private:
  bool rotateLeft(sf::Event &ev);
  bool rotateRight(sf::Event &ev);
  bool thrust(sf::Event &ev);
  bool fire(sf::Event &ev);

  bool clearRotation(sf::Event &ev);
  bool clearThrust(sf::Event &ev);
};

#endif