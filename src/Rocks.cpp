/*
 * File: Rocks.cpp
 * Project: Project-TE
 * Created Date: Sunday July 14th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Sunday August 25th 2019 11:31:23 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include "Rocks.hpp"
#include <cstdlib>
#include <cmath>

#define ROCK_RANGE 7

Rocks::Rocks(int size, float x, float y, float dx, float dy, sf::Texture &tex, sf::RenderWindow &ww) : _d(false),
                                                                                                       testBound(false),
                                                                                                       rwin(ww),
                                                                                                       size(size),
                                                                                                       position(x, y),
                                                                                                       position2(x, y),
                                                                                                       velocity(dx, dy)
{
  static const float pi = 3.141592654f;
  for (std::size_t i = 0; i < getPointCount(); i++)
  {
    float angle = i * 2 * pi / getPointCount() - pi / 2;
    float x = cos(angle) * size;
    float y = sin(angle) * size;
    auto temp = sf::Vector2f(size + x, size + y);
    points[i] = {temp.x + ((rand() % ROCK_RANGE) - ROCK_RANGE / 2), temp.y + ((rand() % ROCK_RANGE) - ROCK_RANGE / 2)};
  }
  sf::Shape::update();
  sf::Shape::setOrigin(size, size);
  sf::Shape::setFillColor(sf::Color::White);
  sf::Shape::setOutlineColor(sf::Color::Black);
  sf::Shape::setOutlineThickness(1);
  sf::Shape::setTexture(&tex);
  sf::Shape::setPosition(position);
}
Rocks::~Rocks() {}

const sf::Vector2f Rocks::getVelocity() { return velocity; }
std::size_t Rocks::getPointCount() const
{
  return 20;
}
sf::Vector2f Rocks::getPoint(std::size_t index) const
{
  return points[index];
}
void Rocks::destroy()
{
  _d = true;
}
bool Rocks::isDestroyed()
{
  return _d;
}
void Rocks::update(const sf::Time &t)
{
  position += (velocity * t.asSeconds());
  position2 = position;
  if (position.x < 0)
    position.x = rwin.getSize().x;
  else if (position.x > rwin.getSize().x)
    position.x = 0;
  if (position.y < 0)
    position.y = rwin.getSize().y;
  else if (position.y > rwin.getSize().y)
    position.y = 0;

  if (position.x - size < 0)
    position2.x = rwin.getSize().x + position.x;
  else if (position.x + size > rwin.getSize().x)
    position2.x = position.x - rwin.getSize().x;
  if (position.y - size < 0)
    position2.y = rwin.getSize().y + position.y;
  else if (position.y + size > rwin.getSize().y)
    position2.y = position.y - rwin.getSize().y;
}
int Rocks::getSize() const
{
  return size;
}
void Rocks::setPosition1()
{
  sf::Shape::setPosition(position);
}
void Rocks::setPosition2()
{
  sf::Shape::setPosition(position2);
}
bool Rocks::getBoundTest()
{
  return testBound;
}
