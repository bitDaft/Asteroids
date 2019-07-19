/*
 * File: Rocks.hpp
 * Project: Project-TE
 * Created Date: Sunday July 14th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday July 19th 2019 1:24:42 pm
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
  Rocks(int size, float x, float y, float dx, float dy,sf::Texture &,sf::RenderWindow &);
  ~Rocks();

  int getSize();
  const sf::Vector2f getVelocity();
  void update(const sf::Time &t);

  std::size_t getPointCount() const;
  sf::Vector2f getPoint(std::size_t index) const;


  bool destroy;

private:
  sf::RenderWindow &rwin;
  float size;
  sf::Vector2f position;
  sf::Vector2f velocity;
  sf::Vector2f points[20];
};

#endif