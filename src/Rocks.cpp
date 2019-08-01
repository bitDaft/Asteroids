/*
 * File: Rocks.cpp
 * Project: Project-TE
 * Created Date: Sunday July 14th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Thursday August 1st 2019 3:56:17 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include "Rocks.hpp"
#include <cstdlib>
#include <cmath>

#define ROCK_RANGE 7

Rocks::Rocks(int size, float x, float y, float dx, float dy, sf::Texture &tex, sf::RenderWindow &ww) : _d(false),
                                                                                                       rwin(ww),
                                                                                                       size(size),
                                                                                                       position(x, y),
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
  if (position.x < 0)
    position.x = rwin.getSize().x;
  if (position.x > rwin.getSize().x)
    position.x = 0;
  if (position.y < 0)
    position.y = rwin.getSize().y;
  if (position.y > rwin.getSize().y)
    position.y = 0;
  sf::Shape::setPosition(position);
}
int Rocks::getSize() const
{
  return size;
}