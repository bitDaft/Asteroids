/*
 * File: asteroids.hpp
 * Project: Project-TE
 * Created Date: Friday July 12th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Sunday July 14th 2019 12:50:41 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#ifndef ASTEROIDS_GAME
#define ASTEROIDS_GAME

#include "Game.hpp"
#include "Spaceship.hpp"
#include "Bullet.hpp"

// Basic (generic) input actions


class Asteroids : public Game
{
public:
  Asteroids();
  ~Asteroids();

private:

Spaceship player;
std::vector<Bullet *> bullets;

void init();
void update(const sf::Time dt);
void draw(sf::RenderWindow &rwin);
};

#endif