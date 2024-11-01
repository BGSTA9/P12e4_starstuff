#ifndef SOURCE_HEADERS_DUSTGRAIN_H_
#define SOURCE_HEADERS_DUSTGRAIN_H_

#include "Common.h"

class DustGrain {
public:
    sf::Vector2f _velocity{0.0f, 0.0f};  // Initialize velocity to zero
    sf::Vector2f _position;
    sf::Color _color;

    // Constructor declaration only
    DustGrain(const sf::Vector2f& initial_position, const sf::Color& initial_color);
};

#endif /* SOURCE_HEADERS_DUSTGRAIN_H_ */