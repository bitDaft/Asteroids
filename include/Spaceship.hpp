/*
 * File: Spaceship.hpp
 * Project: Project-TE
 * Created Date: Friday July 12th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Sunday August 25th 2019 11:31:23 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include "InputHandler.hpp"
#include "Bullet.hpp"
#include "Rocks.hpp"


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

class Spaceship : public InputHandler, public sf::Drawable
{
public:
  Spaceship(sf::RenderWindow &);
  ~Spaceship();

  // const sf::Sprite &getSprite();
  const sf::Vector2f &getPosition();
  // const sf::FloatRect getGlobalBounds();
  Bullet *getBullet();
  int getSize() const;
  void setTexture(sf::Texture &, sf::Texture &);

  void update(const sf::Time &t);
  void destroy();
  bool isDestroyed();

  bool checkCollisionWithRock(Rocks &r);
  void resetState();

private:
  sf::RenderWindow &rwin;
  sf::Sprite ship;
  sf::Sprite jet;

  float angleOfRotation;
  sf::Vector2f velocity;
  sf::Vector2f position;

  float rotate;
  bool thrustF;
  bool fireF;

  Bullet *b;
  sf::Time fireTimeout;
  bool _d;

  int size;
  int rotCount;

private:
  bool rotateLeft(sf::Event &);
  bool rotateRight(sf::Event &);
  bool thrust(sf::Event &);
  bool fire(sf::Event &);

  bool clearRotationLeft(sf::Event &);
  bool clearRotationRight(sf::Event &);
  bool clearThrust(sf::Event &);
  bool clearFire(sf::Event &);

  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif