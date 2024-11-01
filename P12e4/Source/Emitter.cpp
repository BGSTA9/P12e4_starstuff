#include "Emitter.h"
#include <random>
#include <algorithm>
#include <cmath>

Emitter::Emitter(const sf::Vector2f& room_dimensions, int number_of_particles)
    : _number_of_particles(number_of_particles),
      _friction(0.001f) {

    int offset = static_cast<int>(room_dimensions.x / 10);
    std::random_device rd;
    std::mt19937 e2(rd());

    std::uniform_int_distribution<int> width_distribution(offset, static_cast<int>(room_dimensions.x - offset));
    std::uniform_int_distribution<int> height_distribution(offset, static_cast<int>(room_dimensions.y - offset));
    std::uniform_int_distribution<int> opacity_distribution(50, 250);

    sf::Color color(51, 153, 255, 0);

    _particles.reserve(_number_of_particles); // Reserve memory upfront

    for (int i = 0; i < _number_of_particles; ++i) {
        float random_position_x = static_cast<float>(width_distribution(e2));
        float random_position_y = static_cast<float>(height_distribution(e2));
        color.a = static_cast<sf::Uint8>(opacity_distribution(e2));

        _particles.emplace_back(sf::Vector2f(random_position_x, random_position_y), color);
    }
}

void Emitter::update(const sf::Vector2f& mouse_position, sf::Time dt) {
    float dt_seconds = dt.asSeconds();
    for (auto& p : _particles) {
        sf::Vector2f& pos = p._position;

        sf::Vector2f acceleration = mouse_position - pos;
        float mag = std::hypot(acceleration.x, acceleration.y);
        if (mag > std::numeric_limits<float>::epsilon()) {
            acceleration /= mag;
        }

        sf::Vector2f& velocity = p._velocity;

        velocity += acceleration * (5.0f * dt_seconds);
        velocity -= _friction * velocity;
        pos += velocity;

        float velocity_mag = std::hypot(velocity.x, velocity.y);
        float red_value = velocity_mag * (255.0f / max_velocity);
        p._color.r = static_cast<sf::Uint8>(std::min(red_value, 255.0f));
    }
}

const std::vector<DustGrain>& Emitter::getParticles() const {
    return _particles;
}