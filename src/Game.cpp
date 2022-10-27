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
  in_menu = true;
  if (!background_texture.loadFromFile("Data/Images/background.png"))
  {
    std::cout << "Error loading background.png";
    return false;
  }
  if (!bird_texture.loadFromFile("Data/Images/bird.png"))
  {
    std::cout << "Error loading bird.png";
    return false;
  }
  if (!font.loadFromFile("Data/Fonts/OpenSans-bold.ttf"))
  {
    std::cout << "Error loading OpenSans-bold.tff";
    return false;
  }
  background.setTexture(background_texture);
  bird.setTexture(bird_texture);
  bird.setPosition(
    100 + bird.getGlobalBounds().width / 2,
    100 + bird.getGlobalBounds().height / 2);
  bird.setScale(.5, .5);

  title_text.setString("Whack-a-mole");
  title_text.setFont(font);
  title_text.setCharacterSize(100);
  title_text.setFillColor(sf::Color::White);

  title_text.setPosition(
    window.getSize().x / 2 - title_text.getGlobalBounds().width / 2,
    window.getSize().y / 2 - title_text.getGlobalBounds().height / 2);
  return true;
}

void Game::update(float dt)
{

}

void Game::render()
{
  if (in_menu)
  {
    window.draw(title_text);
  }
  window.draw(background);
  window.draw(bird);

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