/*
 * File: Game.cpp
 * Project: Project-TE
 * Created Date: Sunday June 9th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Sunday July 21st 2019 5:15:09 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include "Game.hpp"

#define DEFAULT_FRAME_RATE (1.f / 120.f)
#define DEFAULT_SCREEN_WIDTH 640
#define DEFAULT_SCREEN_HEIGHT 480
#define DEFAULT_GAME_NAME ("Application 1")

// Default constructor
Game::~Game()
{
}
Game::Game()
    : InputHandler(this),
      timePerFrame(sf::seconds(DEFAULT_FRAME_RATE)),
      isRunning(true),
      fps(0),
      gameWindow(sf::VideoMode(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT), DEFAULT_GAME_NAME),
      _aMapper(),
      _inputManager(this, &_aMapper)
{
    gameWindow.setKeyRepeatEnabled(false);
}
// Constructor
Game::Game(const int w, const int h, const char *n)
    : InputHandler(this),
      timePerFrame(sf::seconds(DEFAULT_FRAME_RATE)),
      isRunning(true),
      fps(0),
      gameWindow(sf::VideoMode(w, h), n),
      _aMapper(),
      _inputManager(this, &_aMapper)
{
    gameWindow.setKeyRepeatEnabled(false);
}

void Game::setWindowSize(const int width, const int height)
{
    sf::Vector2u size;
    size.x = width;
    size.y = height;
    gameWindow.setSize(size);
}

void Game::setWindowTitle(const char *title)
{
    gameWindow.setTitle(title);
}

void Game::setFrameRate(const float seconds)
{
    timePerFrame = sf::seconds(1.f / seconds);
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    init();
    // todo: Re-evaluate loop
    // todo: Panic check
    // todo: interpolation
    int looper = 0;
    sf::Time time = sf::Time::Zero;
    while (isRunning)
    {
        processEvents();
        sf::Time dt = clock.restart();
        // ^simple panic check which caps the difference to 1 second
        // ^refactor it to actually handle a panic to revert to a determinable state instead of clamping
        // ^need to test the effect of clamping vs panic handling
        if (dt.asSeconds() > 1.f)
        {
            dt = sf::seconds(1.f);
        }

        // ^FPS handler
        if (time.asSeconds() > 1.f)
        {
            fps = 0.25 * looper + 0.75 * fps;
            looper = 0;
            time -= sf::seconds(1.f);
        }
        looper++;
        time += dt;
        timeSinceLastUpdate += dt;
        while (timeSinceLastUpdate > timePerFrame && isRunning)
        {
            timeSinceLastUpdate -= timePerFrame;
            processEvents();
            update(timePerFrame);
        }
        // TODO: calculate the interpolation from the remaning time and pass it onto render so as to obtain the intermediary state
        // ?Instead of sending remaning time, why not send an interpolation ration between [0,1]
        sf::Time remaining_time = sf::Time::Zero; // !replace with the calculated time
        if (isRunning)
            render(remaining_time);
    }
    end();
}

void Game::processEvents()
{
    sf::Event event;
    while (gameWindow.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            isRunning = false;
            gameWindow.close();
            break;
        case sf::Event::KeyPressed:
        case sf::Event::KeyReleased:
        case sf::Event::MouseButtonPressed:
        case sf::Event::MouseButtonReleased:
        case sf::Event::MouseMoved:
        case sf::Event::MouseWheelScrolled:
        case sf::Event::MouseWheelMoved:
            _inputManager.processInputsEvent(event);
            break;

        default:
            break;
        }
    }
}
bool Game::quit(sf::Event &)
{
    isRunning = false;
    gameWindow.close();
    return false;
}
void Game::quitForce()
{
    isRunning = false;
    gameWindow.close();
}

void Game::render(const sf::Time &dt)
{
    // there will be calculation here to determine the intermediary positions
    gameWindow.clear();
    draw(dt);
    gameWindow.display();
}
float Game::getFPS()
{
    return fps;
}