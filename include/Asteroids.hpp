/*
 * File: asteroids.hpp
 * Project: Project-TE
 * Created Date: Friday July 12th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday July 12th 2019 5:23:18 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#ifndef ASTEROIDS_GAME
#define ASTEROIDS_GAME

#include "Game.hpp"
#include "Spaceship.hpp"

// Basic (generic) input actions
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
	UP_RELEASE,
	DOWN_RELEASE,
	LEFT_RELEASE,
	RIGHT_RELEASE,
	QUIT
};

class Asteroids : public Game
{
public:
  Asteroids();
  ~Asteroids();

private:

Spaceship player;

void init();
void update(const sf::Time dt);
void draw(sf::RenderWindow &rwin);
};

#endif