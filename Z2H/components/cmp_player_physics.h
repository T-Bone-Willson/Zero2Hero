#pragma once

#include "cmp_physics.h"
#include <SFML/Audio.hpp>

class PlayerPhysicsComponent : public PhysicsComponent {
protected:
  b2Vec2 _size;
  sf::Vector2f _maxVelocity;
  bool _grounded;
  float _groundspeed;

  bool isGrounded() const;

  // Jump Sound
  sf::SoundBuffer _buffer_jump;
  sf::Sound _jump_sound;

public:
  void update(double dt) override;

  explicit PlayerPhysicsComponent(Entity* p, const sf::Vector2f& size);

  PlayerPhysicsComponent() = delete;
};
