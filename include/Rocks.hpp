/*
 * File: Rocks.hpp
 * Project: Project-TE
 * Created Date: Sunday July 14th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Tuesday July 30th 2019 10:24:54 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#ifndef ROCKS_HPP
#define ROCKS_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Time.hpp>

class Rocks : public sf::Shape
{
public:
  Rocks(int size, float x, float y, float dx, float dy, sf::Texture &, sf::RenderWindow &);
  ~Rocks();

  const sf::Vector2f getVelocity();

  std::size_t getPointCount() const;
  int getSize() const;
  sf::Vector2f getPoint(std::size_t index) const;

  void update(const sf::Time &t);
  void destroy();
  bool isDestroyed();

private:
  bool _d;
  sf::RenderWindow &rwin;
  int size;
  sf::Vector2f position;
  sf::Vector2f velocity;
  sf::Vector2f points[20];
};

#endif