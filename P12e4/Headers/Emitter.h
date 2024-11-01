#ifndef EMITTER_H
#define EMITTER_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Time.hpp>
#include <vector>
#include "DustGrain.h"

class Emitter {
public:
    Emitter(const sf::Vector2f& room_dimensions, int number_of_particles);

    void update(const sf::Vector2f& mouse_position, sf::Time dt);
    const std::vector<DustGrain>& getParticles() const;

private:
    int _number_of_particles;
    float _friction;
    std::vector<DustGrain> _particles;
    static constexpr float max_velocity = 200.0f;
};

#endif // EMITTER_H