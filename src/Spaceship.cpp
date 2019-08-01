/*
 * File: Spaceship.cpp
 * Project: Project-TE
 * Created Date: Friday July 12th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Thursday August 1st 2019 3:56:17 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include "Spaceship.hpp"
#include <cmath>
#include <SFML/Graphics/CircleShape.hpp>

#define ACCELERATION 1.5f
#define SPEED_DECAY_RATIO 0.002f
#define SPEED_REMAIN_RATIO (1 - SPEED_DECAY_RATIO)
#define ROTATE_DEG 8
#define BULLET_SPEED 70000
#define SHOOT_TIMEOUT 0.5

Spaceship::Spaceship(sf::RenderWindow &win) : InputHandler(this),
                                              rwin(win),
                                              angleOfRotation(-90.f * 3.14159 / 180),
                                              velocity(0.f, 0.f),
                                              position(rwin.getSize().x / 2, rwin.getSize().y / 2),
                                              rotate(0.f),
                                              thrustF(false),
                                              fireF(NULL),
                                              b(NULL),
                                              fireTimeout(),
                                              _d(false),
                                              size(10),
                                              rotCount(0)
{
  _reactionMapper->bindActionToReaction<rotateLeft>(Actions::LEFT);
  _reactionMapper->bindActionToReaction<rotateRight>(Actions::RIGHT);
  _reactionMapper->bindActionToReaction<clearRotationLeft>(Actions::LEFT_RELEASE);
  _reactionMapper->bindActionToReaction<clearRotationRight>(Actions::RIGHT_RELEASE);
  _reactionMapper->bindActionToReaction<thrust>(Actions::UP);
  _reactionMapper->bindActionToReaction<clearThrust>(Actions::UP_RELEASE);
  _reactionMapper->bindActionToReaction<fire>(Actions::SPACE);
  _reactionMapper->bindActionToReaction<clearFire>(Actions::SPACE_RELEASE);

  ship.setPosition(position);
  ship.setOrigin(6.5, 8);
  ship.setRotation(angleOfRotation * 180 / 3.14159);
  ship.setScale(1.5f, 1.5f);
  jet.setPosition(ship.getPosition());
  jet.setOrigin(8, -7);
  jet.setRotation((angleOfRotation * 180 / 3.14159) + 90);
  jet.setScale(1.5f, 1.5f);
}

Spaceship::~Spaceship() {}

const sf::Vector2f &Spaceship::getPosition()
{
  return ship.getPosition();
}
// const sf::Sprite &Spaceship::getSprite()
// {
//   return ship;
// }
// const sf::FloatRect Spaceship::getGlobalBounds()
// {
//   return ship.getGlobalBounds();
// }
 Bullet *Spaceship::getBullet()
{
  Bullet *n = b;
  b = NULL;
  return n;
}
void Spaceship::destroy()
{
  _d = true;
}
bool Spaceship::isDestroyed()
{
  return _d;
}
void Spaceship::setTexture(sf::Texture &ptex, sf::Texture &firetex)
{
  ship.setTexture(ptex);
  jet.setTexture(firetex);
}
bool Spaceship::rotateLeft(sf::Event &)
{
  rotate -= ROTATE_DEG;
  rotCount++;
  return false;
}
bool Spaceship::rotateRight(sf::Event &)
{
  rotate += ROTATE_DEG;
  rotCount++;
  return false;
}
bool Spaceship::clearRotationLeft(sf::Event &)
{
  if (rotCount)
  {
    rotCount--;
    rotate += ROTATE_DEG;
  }
  return false;
}
bool Spaceship::clearRotationRight(sf::Event &)
{
  if (rotCount)
  {
    rotCount--;
    rotate -= ROTATE_DEG;
  }
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
  fireF = true;
  return false;
}
bool Spaceship::clearFire(sf::Event &)
{
  fireF = false;
  return false;
}
void Spaceship::resetState()
{
  rotCount = 0;
  fireF = false;
  thrustF = false;
  fireTimeout = sf::seconds(0);
}
void Spaceship::update(const sf::Time &t)
{
  if (fireTimeout.asMilliseconds() <= 0.05f && fireF)
  {
    b = new Bullet(position.x,
                   position.y,
                   cos(angleOfRotation) * BULLET_SPEED * t.asSeconds(),
                   sin(angleOfRotation) * BULLET_SPEED * t.asSeconds());
    fireTimeout = sf::seconds(SHOOT_TIMEOUT);
  }
  if (fireTimeout.asMilliseconds() > 0.f)
  {
    fireTimeout -= t;
  }
  if (rotate)
  {
    angleOfRotation += rotate * t.asSeconds();
    if (angleOfRotation > 3.14159)
      angleOfRotation -= 3.14159 * 2;
    if (angleOfRotation < -3.14159)
      angleOfRotation += 3.14159 * 2;
    float tempRot = angleOfRotation * 180 / 3.14159;
    ship.setRotation(tempRot);
    jet.setRotation(tempRot + 90);
  }
  if (thrustF)
  {
    velocity.x += cos(angleOfRotation) * ACCELERATION;
    velocity.y += sin(angleOfRotation) * ACCELERATION;
  }
  velocity *= (thrustF ? 1 : SPEED_REMAIN_RATIO);
  position += velocity * t.asSeconds();
  if (position.x < 0)
    position.x = rwin.getSize().x;
  else if (position.x > rwin.getSize().x)
    position.x = 0;
  if (position.y < 0)
    position.y = rwin.getSize().y;
  else if (position.y > rwin.getSize().y)
    position.y = 0;
  ship.setPosition(position);
  jet.setPosition(position);
}
void Spaceship::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  target.draw(ship, states);
  if (thrustF)
  {
    target.draw(jet, states);
  }
}
int Spaceship::getSize() const
{
  return size;
}
bool Spaceship::checkCollisionWithRock(Rocks &r)
{
  const int rockRad = r.getSize();
  const sf::Vector2f line = r.getPosition() - position;
  const float dist = line.x * line.x + line.y * line.y;
  const float checkDist = (rockRad + size) * (rockRad + size);
  return dist < checkDist;
}