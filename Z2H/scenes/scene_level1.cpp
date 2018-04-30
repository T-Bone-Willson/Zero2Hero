#include "scene_level1.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include <system_resources.h> // Allows us to use "Resources" for getting player Texture
#include <LevelSystem.h>
#include <iostream>
#include <thread>

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;

void Level1Scene::Load() {
  cout << " Level 1 Load" << endl;
  ls::loadLevelFile("res/level_1.txt", 40.0f); // Don't touch this!

  auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
  ls::setOffset(Vector2f(0, ho));

  // Background Music

  backGround_Music = Resources::get<Music>("retro_soundtrack01.ogg");
  backGround_Music->play();
  backGround_Music->setLoop(true);

  // Create player
  {
    player = makeEntity();
    player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	// Changed "<ShapeComponent>" to "<SpriteComponent>" because we are now dealing with sprites
    auto s = player->addComponent<SpriteComponent>();
	auto texture = Resources::get<Texture>("AverageJoe.png");
	// Set texture "texture"
	s->setTexture(texture);
	// Player Sprite cut out from sheet
	s->getSprite().setTextureRect(sf::IntRect(0, 0, 64, 64));
	s->getSprite().setOrigin(10.f, 15.f);

    player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 90.f)); // Originaly set at 20.f, 30.f
  }

  // Add physics colliders to level tiles.
  {
    auto walls = ls::findTiles(ls::WALL);
    for (auto w : walls) {
      auto pos = ls::getTilePosition(w);
	  // Originaly set at 20.0f, 20.0f
      pos += Vector2f(1.f, 20.f); //offset to center 
      auto e = makeEntity();
      e->setPosition(pos);
      e->addComponent<PhysicsComponent>(false, Vector2f(40.f, 40.f)); // Don't touch this!

//--------------------------  TRIED TO SET SPRITES TEXTURE FOR WALLS. DID NOT WORK!!!!  -------------
	  /*
	  auto s = e->addComponent<SpriteComponent>();
	  auto texture2 = Resources::get<Texture>("TestWall.png");
	  s->setTexture(texture2);
	  s->getSprite().setTextureRect(sf::IntRect(0, 0, 32, 32));
	  s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);*/
    }
  }

  // Add texture to "EMPTY"
  {
	  auto empty = ls::findTiles(ls::EMPTY);
	  for (auto emp : empty) {
		  auto pos = ls::getTilePosition(emp);
		  pos += Vector2f(1.f, 20.f); //offset to center 
		  auto e = makeEntity();
		  e->setPosition(pos);
		  auto s = e->addComponent<SpriteComponent>();
		  auto texture2 = Resources::get<Texture>("TestWall.png");
		  s->setTexture(texture2);
		  s->getSprite().setTextureRect(sf::IntRect(0, 0, 32, 32));
		  s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);

	  }
  }

  setLoaded(true);
}

void Level1Scene::UnLoad() {
  cout << "Level 1 Unload" << endl;
  player.reset();

  // Unload Background Music
  backGround_Music->stop();
  backGround_Music.reset();

  ls::unload();
  Scene::UnLoad();
}

void Level1Scene::Update(const double& dt) {

  if (ls::getTileAt(player->getPosition()) == ls::END) {
    Engine::ChangeScene((Scene*)&menu); // Once reached exit, will take you back to Main Menu.
  }

  // Allows you to press exit to go back to main menu.
  if (sf::Keyboard::isKeyPressed(Keyboard::Escape)) {
	  Engine::ChangeScene(&menu);
  }

  Scene::Update(dt);
}

void Level1Scene::Render() {
  ls::render(Engine::GetWindow());
  Scene::Render();
}
