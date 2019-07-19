/*
 * File: Rocks.cpp
 * Project: Project-TE
 * Created Date: Sunday July 14th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday July 19th 2019 1:32:26 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include "Rocks.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

Rocks::Rocks(int size, float x, float y, float dx, float dy, sf::Texture &tex, sf::RenderWindow &ww) : destroy(false),
                                                                                                       rwin(ww),
                                                                                                       size(size),
                                                                                                       position(x, y),
                                                                                                       velocity(dx, dy)
{
  static const float pi = 3.141592654f;
  for (std::size_t i = 0; i < getPointCount(); i++)
  {
    float angle = i * 2 * pi / getPointCount() - pi / 2;
    float x = std::cos(angle) * size;
    float y = std::sin(angle) * size;
    auto temp = sf::Vector2f(size + x, size + y);
    points[i] = {temp.x + (rand() % 10) + 1, temp.y + (rand() % 10) + 1};
  }
  sf::Shape::update();
  sf::Shape::setOrigin(size / 2, size / 2);
  sf::Shape::setFillColor(sf::Color::White);
  sf::Shape::setOutlineColor(sf::Color::Black);
  sf::Shape::setOutlineThickness(2);
  sf::Shape::setTexture(&tex);
  sf::Shape::setPosition(position);
}
Rocks::~Rocks() {}

int Rocks::getSize() { return size; }
const sf::Vector2f Rocks::getVelocity() { return velocity; }
std::size_t Rocks::getPointCount() const
{
  return 20;
}
sf::Vector2f Rocks::getPoint(std::size_t index) const
{
  return points[index];
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
