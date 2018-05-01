#pragma once

#include "engine.h"
#include <SFML/Audio.hpp>

class Level1Scene : public Scene {
public:
  void Load() override;

  void UnLoad() override;

  void Update(const double& dt) override;

  void Render() override;

  // Background Music
  std::shared_ptr<sf::Music> backGround_Music;

};
