/*
 * File: Asteroids.cpp
 * Project: Project-TE
 * Created Date: Friday July 12th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Sunday July 14th 2019 4:26:30 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include "Asteroids.hpp"
#include <iostream>

Asteroids::Asteroids() : player(gameWindow)
{
  unsigned int playertex = ResourceManager::loadTexture("assets/plane.png");
  player.setTexture(ResourceManager::getTexture(playertex));
  _inputManager.pushEntity(&player);
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
}
void Asteroids::update(const sf::Time dt)
{
  Bullet *t = player.getBullet();
  if (t)
  {
    bullets.push_back(t);
  }
  player.update(dt);
  for (auto it = bullets.begin(); it != bullets.end();)
  {
    (*it)->update(dt);
    sf::Vector2f pos = (*it)->getPos();
    sf::Vector2u ss = gameWindow.getSize();
    if (pos.x > ss.x || pos.x < 0 || pos.y > ss.y || pos.y < 0)
    {
      delete (*it);
      (*it) = NULL;
      it = bullets.erase(it);
      // if (!bullets.size())
      //   break;
    }
    else
    {
      it++;
    }
  }
}
void Asteroids::draw(sf::RenderWindow &rwin)
{
  rwin.draw(player.getSprite());
  for (auto it = bullets.begin(); it != bullets.end(); it++)
  {
    rwin.draw((*it)->getSprite());
  }
}