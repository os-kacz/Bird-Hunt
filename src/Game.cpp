
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{
  return true;
}

void Game::update(float dt)
{

}

void Game::render()
{

}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);

  // check if in bounds of bird Sprite
  if (collisionCheck(click, bird))
  {
  }
}

void Game::keyPressed(sf::Event event)
{

}


bool Game::collisionCheck(sf::Vector2i click, sf::Sprite sprite)
{
  return false;
}

void Game::spawn()
{

}
