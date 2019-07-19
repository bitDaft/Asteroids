/*
 * File: Asteroids.cpp
 * Project: Project-TE
 * Created Date: Friday July 12th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday July 19th 2019 1:24:42 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include "Asteroids.hpp"
#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>
#include <cstdlib>

#define ASTEROID_SIZE 66

Asteroids::Asteroids() : player(gameWindow)
{
  srand(time(0));
  playerTex = ResourceManager::loadTexture("assets/plane.png");
  asteroidTex = ResourceManager::loadTexture("assets/asteroid.jpg");
}
Asteroids::~Asteroids()
{
}

void Asteroids::init()
{
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

  _reactionMapper->bindActionToReaction<quit>(Actions::QUIT);

  rocks.push_back(new Rocks(ASTEROID_SIZE, (rand() % gameWindow.getSize().x), (rand() % gameWindow.getSize().y), (rand() % 30) - 15, (rand() % 30) - 15, ResourceManager::getTexture(asteroidTex), gameWindow));
  rocks.push_back(new Rocks(ASTEROID_SIZE, (rand() % gameWindow.getSize().x), (rand() % gameWindow.getSize().y), (rand() % 30) - 15, (rand() % 30) - 15, ResourceManager::getTexture(asteroidTex), gameWindow));
  rocks.push_back(new Rocks(ASTEROID_SIZE, (rand() % gameWindow.getSize().x), (rand() % gameWindow.getSize().y), (rand() % 30) - 15, (rand() % 30) - 15, ResourceManager::getTexture(asteroidTex), gameWindow));

  player.setTexture(ResourceManager::getTexture(playerTex));
  _inputManager.pushEntity(&player);
}
void Asteroids::update(const sf::Time &dt)
{
  Bullet *t = player.getBullet();
  if (t)
  {
    bullets.push_back(t);
  }
  player.update(dt);
  for (auto it = rocks.begin(); it != rocks.end();)
  {
    (*it)->update(dt);
    it++;
  }
  for (auto it = bullets.begin(); it != bullets.end(); ++it)
  {
    (*it)->update(dt);
    sf::Vector2f pos = (*it)->getPosition();
    sf::Vector2u ss = gameWindow.getSize();
    if (pos.x > ss.x || pos.x < 0 || pos.y > ss.y || pos.y < 0)
    {
      (*it)->destroy = true;
    }
    for (auto rr = rocks.begin(); rr != rocks.end(); ++rr)
    {
      if ((*rr)->getGlobalBounds().contains(pos))
      {
        if ((*rr)->getSize() > ASTEROID_SIZE / 4)
        {
          const sf::Vector2f pos = (*rr)->getPosition();
          const sf::Vector2f vel = (*rr)->getVelocity();
          new_rocks.push_back(new Rocks((*rr)->getSize() >> 1, pos.x, pos.y, vel.x + (rand() % 30) - 15, vel.y + (rand() % 30) - 15, ResourceManager::getTexture(asteroidTex), gameWindow));
          new_rocks.push_back(new Rocks((*rr)->getSize() >> 1, pos.x, pos.y, vel.x + (rand() % 30) - 15, vel.y + (rand() % 30) - 15, ResourceManager::getTexture(asteroidTex), gameWindow));
        }
        (*rr)->destroy = true;
        (*it)->destroy = true;
        break;
      }
    }
  }
  for (auto rr = rocks.begin(); rr != rocks.end();)
  {
    if ((*rr)->destroy)
    {
      delete (*rr);
      (*rr) = NULL;
      rr = rocks.erase(rr);
    }
    else
    {
      ++rr;
    }
  }
  for (auto rr = bullets.begin(); rr != bullets.end();)
  {
    if ((*rr)->destroy)
    {
      delete (*rr);
      (*rr) = NULL;
      rr = bullets.erase(rr);
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
}
void Asteroids::draw(const sf::Time &)
{
  gameWindow.draw(player.getSprite());
  for (auto it = rocks.begin(); it != rocks.end(); it++)
  {
    gameWindow.draw(*(*it));
  }
  for (auto it = bullets.begin(); it != bullets.end(); it++)
  {
    gameWindow.draw(*(*it));
  }
}