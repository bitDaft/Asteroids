/*
 * File: Spaceship.cpp
 * Project: Project-TE
 * Created Date: Friday July 12th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday July 19th 2019 1:24:42 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include "Spaceship.hpp"
#include <iostream>
#include <cmath>

#define MAX_MOVE_SPEED 150
#define ROTATE_DEG 5
#define BULLET_SPEED 300

Spaceship::Spaceship(sf::RenderWindow &win) : InputHandler(this),
                                              rwin(win),
                                              angleOfRotation(270.f * 3.14159 / 180),
                                              velocity(0.f, 0.f),
                                              position(100.f, 100.f),
                                              rotate(0.f),
                                              thrustF(false),
                                              b(NULL)
{
  _reactionMapper->bindActionToReaction<rotateLeft>(Actions::LEFT);
  _reactionMapper->bindActionToReaction<rotateRight>(Actions::RIGHT);
  _reactionMapper->bindActionToReaction<clearRotation>(Actions::LEFT_RELEASE);
  _reactionMapper->bindActionToReaction<clearRotation>(Actions::RIGHT_RELEASE);
  _reactionMapper->bindActionToReaction<thrust>(Actions::UP);
  _reactionMapper->bindActionToReaction<clearThrust>(Actions::UP_RELEASE);
  _reactionMapper->bindActionToReaction<fire>(Actions::SPACE);
  ship.setPosition(200.f, 200.f);
  ship.setOrigin(6.5, 8);
  ship.setRotation(angleOfRotation * 180 / 3.14159);
  ship.setScale(1.5f, 1.5f);
}

Spaceship::~Spaceship() {}

const sf::Sprite &Spaceship::getSprite()
{
  return ship;
}
Bullet *Spaceship::getBullet()
{
  Bullet *n = NULL;
  n = b;
  b = NULL;
  return n;
}
void Spaceship::setTexture(sf::Texture &tex)
{
  ship.setTexture(tex);
}
bool Spaceship::rotateLeft(sf::Event &)
{
  rotate = -ROTATE_DEG;
  return false;
}
bool Spaceship::rotateRight(sf::Event &)
{
  rotate = ROTATE_DEG;
  return false;
}
bool Spaceship::clearRotation(sf::Event &)
{
  rotate = 0.f;
  return false;
}
bool Spaceship::thrust(sf::Event &)
{
  thrustF = true;
  return false;
}
bool Spaceship::clearThrust(sf::Event &)
{
  thrustF = false;
  return false;
}
bool Spaceship::fire(sf::Event &)
{
  b = new Bullet(position.x, position.y, std::cos(angleOfRotation) * BULLET_SPEED, std::sin(angleOfRotation) * BULLET_SPEED);
  return false;
}

void Spaceship::update(sf::Time t)
{
  if (rotate)
  {
    angleOfRotation += rotate * t.asSeconds();
    ship.setRotation(angleOfRotation * 180 / 3.14159);
  }
  if (thrustF)
  {
    velocity.x += std::cos(angleOfRotation);
    velocity.y += std::sin(angleOfRotation);
    if (velocity.x > MAX_MOVE_SPEED)
    {
      velocity.x = MAX_MOVE_SPEED;
    }
    if (velocity.y > MAX_MOVE_SPEED)
    {
      velocity.y = MAX_MOVE_SPEED;
    }
    if (velocity.x < -MAX_MOVE_SPEED)
    {
      velocity.x = -MAX_MOVE_SPEED;
    }
    if (velocity.y < -MAX_MOVE_SPEED)
    {
      velocity.y = -MAX_MOVE_SPEED;
    }
  }
  position += (velocity * t.asSeconds());
  if (position.x < 0)
    position.x = rwin.getSize().x;
  if (position.x > rwin.getSize().x)
    position.x = 0;
  if (position.y < 0)
    position.y = rwin.getSize().y;
  if (position.y > rwin.getSize().y)
    position.y = 0;
  ship.setPosition(position);
}