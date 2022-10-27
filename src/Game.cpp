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

/*bool Text::init(sf::Text z, std::string str, int fs, float y, float x)
{
  if (!font.loadFromFile("Data/Fonts/OpenSans-bold.tff"))
  {
    std::cout << "Error loading OpenSans-bold.tff";
    return false;
  }
  z.setString(str);
  z.setFont(font);
  z.setCharacterSize(fs);
  z.setFillColor(sf::Color::White);

  z.setPosition(
    window.getSize().x / 2 - z.getGlobalBounds().width / 2 + x,
    window.getSize().y / 2 - z.getGlobalBounds().height / 2 + y);
}*/

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
  spawn();
  bird.setScale(.5, .5);

  title_text.setString("Whack-a-mole\n");
  title_text.setFont(font);
  title_text.setCharacterSize(65);
  title_text.setFillColor(sf::Color::White);

  title_text.setPosition(
    window.getSize().x / 2 - title_text.getGlobalBounds().width / 2 + 0,
    window.getSize().y / 2 - title_text.getGlobalBounds().height / 2 + 0);

  play_option.setString(">Play");
  play_option.setFont(font);
  play_option.setCharacterSize(55);
  play_option.setFillColor(sf::Color::White);

  play_option.setPosition(
    window.getSize().x / 4 - play_option.getGlobalBounds().width / 2 + 125,
    window.getSize().y / 2 - play_option.getGlobalBounds().height / 2 + 60);

  quit_option.setString(" Quit");
  quit_option.setFont(font);
  quit_option.setCharacterSize(55);
  quit_option.setFillColor(sf::Color::White);

  quit_option.setPosition(
    window.getSize().x / 4 - quit_option.getGlobalBounds().width / 2 + 125,
    window.getSize().y / 2 - quit_option.getGlobalBounds().height / 2 + 150);

  menu_text.setString("Score: " + std::to_string(score));
  menu_text.setFont(font);
  menu_text.setCharacterSize(30);
  menu_text.setFillColor(sf::Color::Blue);
  menu_text.setPosition(10, 10);

  return true;
}

void Game::update(float dt)
{
  // if reverse is true, make it go backwards and flip sprite
  if (reverse)
  {
    bird.setTextureRect(sf::IntRect(
      bird.getLocalBounds().width, 0, -bird.getLocalBounds().width, bird.getLocalBounds().height));
    bird.move(-1.0f * speed * dt, 0);
  }
  // if reverse is false, make it go forwards and flip sprite
  else
  {
    bird.setTextureRect(sf::IntRect(
      0, 0, bird.getLocalBounds().width, bird.getLocalBounds().height));
    bird.move(1.0f * speed * dt, 0);
  }
  // if bird's position is more than 1080(x) - the width of the bird OR the bird's position is less than 0, flip the boolean reverse
  if ((bird.getPosition().x > (window.getSize().x - bird.getGlobalBounds().width)) || (bird.getPosition().x < 0))
  {
    reverse = !reverse;
  }
}

void Game::render()
{
  if (in_menu)
  {
    window.draw(title_text);
    window.draw(play_option);
    window.draw(quit_option);
  }
  else
  {
    window.draw(background);
    window.draw(bird);
    window.draw(menu_text);
  }
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);

  // check if in bounds of bird Sprite
  if (collisionCheck(click, bird))
  {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      score++;
      menu_text.setString("Score: " + std::to_string(score));

      spawn();
    }
  }
}

void Game::keyPressed(sf::Event event)
{
  if (
    (event.key.code == sf::Keyboard::Up) ||
    (event.key.code == sf::Keyboard::Down))
    {
      play_selected = !play_selected;
      if (play_selected)
      {
        play_option.setString(">Play");
        quit_option.setString(" Quit");
      }
      else
      {
        play_option.setString(" Play");
        quit_option.setString(">Quit");
      }
    }
  else if (event.key.code == sf::Keyboard::Enter)
  {
    if (play_selected)
    {
      in_menu = false;
    }
    else
    {
      window.close();
    }
  }
}

bool Game::collisionCheck(sf::Vector2i click, sf::Sprite sprite)
{
  if (
    (click.x > bird.getPosition().x) && click.x < (bird.getGlobalBounds().width + bird.getPosition().x)
    &&
    (click.y > bird.getPosition().y) && click.y < (bird.getGlobalBounds().height + bird.getPosition().y)
    )
  {
    return true;
  }
  else
  {
    return false;
  }
}

void Game::spawn()
{
  std::srand(time(nullptr));
  int xbound = 1080 - bird.getGlobalBounds().width;
  int ybound = 720 - bird.getGlobalBounds().height;
  int x = rand() % xbound + 1;
  int y = rand() % ybound + 1;
  bird.setPosition(x, y);
  if ((std::rand() % 2 + 1) == 1)
  {
    reverse = !reverse;
  }
}