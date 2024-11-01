#ifndef SOURCE_HEADERS_ENGINE_H_
#define SOURCE_HEADERS_ENGINE_H_

#include "Emitter.h"
#include "Common.h"
#include <SFML/Graphics.hpp>
#include <memory>

class Engine {
private:
    sf::Vector2f room_dimensions;
    int number_of_particles;

    std::unique_ptr<sf::RenderWindow> _window;
    std::unique_ptr<sf::VertexArray> _particles;
    std::unique_ptr<Emitter> _emitter;
    sf::Vector2f _mouse_position;

    void _processInput();
    void _update(sf::Time dt);
    void _render();

public:
    Engine();
    ~Engine() = default;
    void run();
};

#endif /* SOURCE_HEADERS_ENGINE_H_ */