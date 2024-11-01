#ifndef SOURCE_HEADERS_CONFIG_H_
#define SOURCE_HEADERS_CONFIG_H_

#include <SFML/System/Vector2.hpp>
#include <cmath>
# include <stdint.h>

inline float Q_rsqrt(float x) { //Fast Inverse Square Root = Q_rsqrt
    float xhalf = 0.5f * x;
    int i = *(int*)&x;
    i = 0x5f3759df - (i >> 1);
    x = *(float*)&i;
    x = x * (1.5f - xhalf * x * x);  // Newton-Raphson iteration to refine the approximation.
    return x;
}

inline float getMagnitude(const sf::Vector2f &vec) {
    return 1.0f / Q_rsqrt(vec.x * vec.x + vec.y * vec.y);
}

inline void normalize(sf::Vector2f &vec) {
    vec /= getMagnitude(vec);
}

#endif /* SOURCE_HEADERS_CONFIG_H_ */