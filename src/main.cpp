/*
 * File: main.cpp
 * Project: Project-TE
 * Created Date: Sunday June 9th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Sunday July 21st 2019 5:20:48 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include <iostream>
#include "Asteroids.hpp"

// ^There are 3 main entities
// ^1. The Spaceship
// ^2. The Asteroids
// ^3. The Bullets

// ^The player controls spaceship, so it is input reacting
// ^It rotates to the orientation of the mouse, moves to the WASD keys and fires upon click
// ^Bullets produced from player travel in straight line and gets destroyed outside the screen
// ^Bullets can collide with asteroids and gets destroyed
// ^Asteroids that collide with bullets break up into smaller pieces till it gets destroyed
// ^players and asteroids wrap the screen

int main(int argc, char *argv[])
{
	Asteroids asteroidsGame;
	asteroidsGame.run();
	return 0;
}