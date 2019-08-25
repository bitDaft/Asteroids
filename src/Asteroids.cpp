/*
 * File: Asteroids.cpp
 * Project: Project-TE
 * Created Date: Friday July 12th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Sunday August 25th 2019 11:31:23 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include "Asteroids.hpp"
#include <cstdlib>
#include <cmath>
#include <SFML/Graphics/CircleShape.hpp>

#define ASTEROID_SIZE 20
#define ASTEROID_VELOCITY 50

Asteroids::Asteroids() : player(NULL),
                         asteroidTex(-1),
                         playerTex(-1),
                         jetFireTex(-1),
                         rockCount(3),
                         difficulty(1),
                         stage(1),
                         level(1)
{
  srand(time(0));
  // _aMapper.bindInputToAction(sf::Keyboard::Up, sf::Event::KeyPressed, Actions::UP);
  // _aMapper.bindInputToAction(sf::Keyboard::Up, sf::Event::KeyReleased, Actions::UP_RELEASE);
  // _aMapper.bindInputToAction(sf::Keyboard::Down, sf::Event::KeyPressed, Actions::DOWN);
  // _aMapper.bindInputToAction(sf::Keyboard::Down, sf::Event::KeyReleased, Actions::DOWN_RELEASE);
  // _aMapper.bindInputToAction(sf::Keyboard::Left, sf::Event::KeyPressed, Actions::LEFT);
  // _aMapper.bindInputToAction(sf::Keyboard::Left, sf::Event::KeyReleased, Actions::LEFT_RELEASE);
  // _aMapper.bindInputToAction(sf::Keyboard::Right, sf::Event::KeyPressed, Actions::RIGHT);
  // _aMapper.bindInputToAction(sf::Keyboard::Right, sf::Event::KeyReleased, Actions::RIGHT_RELEASE);
  _aMapper.bindInputToAction(sf::Keyboard::Escape, sf::Event::KeyPressed, Actions::QUIT);
  _aMapper.bindInputToAction(sf::Keyboard::W, sf::Event::KeyPressed, Actions::UP);
  _aMapper.bindInputToAction(sf::Keyboard::W, sf::Event::KeyReleased, Actions::UP_RELEASE);
  _aMapper.bindInputToAction(sf::Keyboard::S, sf::Event::KeyPressed, Actions::DOWN);
  _aMapper.bindInputToAction(sf::Keyboard::S, sf::Event::KeyReleased, Actions::DOWN_RELEASE);
  _aMapper.bindInputToAction(sf::Keyboard::A, sf::Event::KeyPressed, Actions::LEFT);
  _aMapper.bindInputToAction(sf::Keyboard::A, sf::Event::KeyReleased, Actions::LEFT_RELEASE);
  _aMapper.bindInputToAction(sf::Keyboard::D, sf::Event::KeyPressed, Actions::RIGHT);
  _aMapper.bindInputToAction(sf::Keyboard::D, sf::Event::KeyReleased, Actions::RIGHT_RELEASE);
  _aMapper.bindInputToAction(sf::Keyboard::Space, sf::Event::KeyPressed, Actions::SPACE);
  _aMapper.bindInputToAction(sf::Keyboard::Space, sf::Event::KeyReleased, Actions::SPACE_RELEASE);

  _aMapper.bindInputToAction(sf::Mouse::Button::Left, sf::Event::MouseButtonPressed, Actions::MOUSE_LEFT);
  _aMapper.bindInputToAction(sf::Mouse::Button::Left, sf::Event::MouseButtonReleased, Actions::MOUSE_LEFT_RELEASE);
  _aMapper.bindInputToAction(sf::Mouse::Button::Right, sf::Event::MouseButtonPressed, Actions::MOUSE_RIGHT);
  _aMapper.bindInputToAction(sf::Mouse::Button::Right, sf::Event::MouseButtonReleased, Actions::MOUSE_RIGHT_RELEASE);
  _aMapper.bindInputToAction(sf::Mouse::Button::Middle, sf::Event::MouseButtonPressed, Actions::MOUSE_MIDDLE);
  _aMapper.bindInputToAction(sf::Mouse::Button::Middle, sf::Event::MouseButtonReleased, Actions::MOUSE_MIDDLE_RELEASE);
  _aMapper.bindInputToAction(sf::Mouse::Button::XButton1, sf::Event::MouseButtonPressed, Actions::MOUSE_X1);
  _aMapper.bindInputToAction(sf::Mouse::Button::XButton1, sf::Event::MouseButtonReleased, Actions::MOUSE_X1_RELEASE);
  _aMapper.bindInputToAction(sf::Mouse::Button::XButton2, sf::Event::MouseButtonPressed, Actions::MOUSE_X2);
  _aMapper.bindInputToAction(sf::Mouse::Button::XButton2, sf::Event::MouseButtonReleased, Actions::MOUSE_X2_RELEASE);
  _aMapper.bindInputToAction(sf::Event::MouseMoved, Actions::MOUSE_MOVED);
  _aMapper.bindInputToAction(sf::Event::MouseWheelScrolled, Actions::MOUSE_SCROLL);
}
Asteroids::~Asteroids()
{
}

float getRandomVelocity()
{
  float temp = 0;
  do
  {
    temp = (rand() % ASTEROID_VELOCITY) - ASTEROID_VELOCITY / 2;
  } while (temp > -15 && temp < 15);
  return temp;
}

void Asteroids::init()
{
  playerTex = ResourceManager::loadTexture("assets/plane.png");
  asteroidTex = ResourceManager::loadTexture("assets/asteroid.jpg");
  jetFireTex = ResourceManager::loadTexture("assets/jetFire.png");
  _reactionMapper->bindActionToReaction<quit>(Actions::QUIT);
  resetGame();
}
void Asteroids::makeRocks(int count)
{
  sf::Vector2u winSize = gameWindow.getSize();
  sf::Vector2f playerPos = player->getPosition();
  for (int i = 0; i < count; i++)
  {
    int x = 0;
    int y = 0;
    float distance = 0.f;
    do
    {
      x = (rand() % winSize.x);
      y = (rand() % winSize.y);
      sf::Vector2f p2r = sf::Vector2f(x, y) - playerPos;
      distance = p2r.x * p2r.x + p2r.y * p2r.y;
    } while (distance < (difficulty * ASTEROID_SIZE * 2) * (difficulty * ASTEROID_SIZE * 2));
    rocks.push_back(new Rocks(difficulty * ASTEROID_SIZE, x, y, getRandomVelocity(), getRandomVelocity(), ResourceManager::getTexture(asteroidTex), gameWindow));
  }
}
void Asteroids::resetGame()
{
  end();
  player = new Spaceship(gameWindow);
  player->setTexture(ResourceManager::getTexture(playerTex), ResourceManager::getTexture(jetFireTex));
  player->resetState();
  makeRocks(rockCount);
  _inputManager.clearEntity();
  _inputManager.pushEntity(player);
}
void Asteroids::resetPlayerState()
{
  if (player)
  {
    delete player;
    player = NULL;
  }
  player = new Spaceship(gameWindow);
  player->setTexture(ResourceManager::getTexture(playerTex), ResourceManager::getTexture(jetFireTex));
  player->resetState();
  // makeRocks(2);
  _inputManager.clearEntity();
  _inputManager.pushEntity(player);
}
void Asteroids::update(const sf::Time &dt)
{
  Bullet *t = player->getBullet();
  if (t)
  {
    bullets.push_back(t);
  }
  player->update(dt);
  for (auto rr = rocks.begin(); rr != rocks.end(); ++rr)
  {
    (*rr)->update(dt);
  }
  for (auto rr = bullets.begin(); rr != bullets.end(); ++rr)
  {
    (*rr)->update(dt);
  }
  for (auto rr = rocks.begin(); rr != rocks.end(); ++rr)
  {
    (*rr)->setPosition1();
    if (player->checkCollisionWithRock(*(*rr)))
    {
      player->destroy();
    }
    (*rr)->setPosition2();
    if (player->checkCollisionWithRock(*(*rr)))
    {
      player->destroy();
    }
    for (auto it = bullets.begin(); it != bullets.end(); ++it)
    {
      if ((*it)->isDestroyed())
      {
        continue;
      }
      sf::Vector2f pos = (*it)->getPosition();
      sf::Vector2u ss = gameWindow.getSize();
      if (pos.x > ss.x || pos.x < 0 || pos.y > ss.y || pos.y < 0)
      {
        (*it)->destroy();
      }
      (*rr)->setPosition1();
      if ((*rr)->getGlobalBounds().contains(pos))
      {
        if ((*rr)->getSize() > ASTEROID_SIZE)
        {
          const sf::Vector2f pos = (*rr)->getPosition();
          const sf::Vector2f vel = (*rr)->getVelocity();
          new_rocks.push_back(new Rocks((*rr)->getSize() >> 1, pos.x, pos.y, vel.y + getRandomVelocity(), vel.x + getRandomVelocity(), ResourceManager::getTexture(asteroidTex), gameWindow));
          new_rocks.push_back(new Rocks((*rr)->getSize() >> 1, pos.x, pos.y, vel.x + getRandomVelocity(), vel.y + getRandomVelocity(), ResourceManager::getTexture(asteroidTex), gameWindow));
        }
        (*rr)->destroy();
        (*it)->destroy();
        continue;
      }
      (*rr)->setPosition2();
      if ((*rr)->getGlobalBounds().contains(pos))
      {

        if ((*rr)->getSize() > ASTEROID_SIZE)
        {
          const sf::Vector2f pos = (*rr)->getPosition();
          const sf::Vector2f vel = (*rr)->getVelocity();
          new_rocks.push_back(new Rocks((*rr)->getSize() >> 1, pos.x, pos.y, vel.y + getRandomVelocity(), vel.x + getRandomVelocity(), ResourceManager::getTexture(asteroidTex), gameWindow));
          new_rocks.push_back(new Rocks((*rr)->getSize() >> 1, pos.x, pos.y, vel.x + getRandomVelocity(), vel.y + getRandomVelocity(), ResourceManager::getTexture(asteroidTex), gameWindow));
        }
        (*rr)->destroy();
        (*it)->destroy();
      }
    }
  }
  for (auto rr = rocks.begin(); rr != rocks.end();)
  {
    if ((*rr)->isDestroyed())
    {
      delete (*rr);
      rr = rocks.erase(rr);
    }
    else
    {
      ++rr;
    }
  }
  for (auto rr = new_rocks.begin(); rr != new_rocks.end(); rr++)
  {
    rocks.push_back((*rr));
  }
  new_rocks.clear();
  for (auto rr = bullets.begin(); rr != bullets.end();)
  {
    if ((*rr)->isDestroyed())
    {
      delete (*rr);
      rr = bullets.erase(rr);
    }
    else
    {
      ++rr;
    }
  }
  if (!rocks.size())
  {
    stage++;
    if (stage % 3 == 0)
    {
      difficulty += 0.75;
      stage = 1;
      rockCount = (rockCount >> 1) + (level >> 1);
      level++;
    }
    makeRocks(++rockCount);
  }
  if (player->isDestroyed())
  {
    resetGame();
  }
}
void Asteroids::draw(const sf::Time &)
{
  sf::CircleShape s;
  s.setFillColor(sf::Color::Red);
  for (auto it = rocks.begin(); it != rocks.end(); it++)
  {
    (*it)->setPosition1();
    gameWindow.draw(*(*it));
    (*it)->setPosition2();
    gameWindow.draw(*(*it));
  }
  for (auto it = bullets.begin(); it != bullets.end(); it++)
  {
    gameWindow.draw(*(*it));
  }
  gameWindow.draw(*player);
}
void Asteroids::end()
{
  if (player)
  {
    delete player;
    player = NULL;
  }
  for (auto rr = rocks.begin(); rr != rocks.end(); ++rr)
  {
    delete (*rr);
  }
  rocks.clear();
  for (auto rr = bullets.begin(); rr != bullets.end(); ++rr)
  {
    delete (*rr);
  }
  bullets.clear();
}