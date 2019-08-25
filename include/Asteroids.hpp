/*
 * File: asteroids.hpp
 * Project: Project-TE
 * Created Date: Friday July 12th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Sunday August 25th 2019 11:12:48 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#ifndef ASTEROIDS_GAME
#define ASTEROIDS_GAME

#include "Game.hpp"
#include "Spaceship.hpp"
#include "Bullet.hpp"
#include "Rocks.hpp"

// Basic (generic) input actions

class Asteroids : public Game
{
public:
  Asteroids();
  ~Asteroids();

private:
  Spaceship *player;
  std::vector<Bullet *> bullets;
  std::vector<Rocks *> rocks;
  std::vector<Rocks *> new_rocks;

  unsigned int asteroidTex;
  unsigned int playerTex;
  unsigned int jetFireTex;

  void init();
  void update(const sf::Time &);
  void draw(const sf::Time &);
  void end();
  void resetGame();
  void resetPlayerState();
  void makeRocks(int);

  int rockCount;
  float difficulty;
  int stage;
  int level;
};

#endif