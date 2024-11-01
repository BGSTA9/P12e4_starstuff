#include "../Headers/Engine.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

Engine::Engine() 
    : room_dimensions(1280, 720), 
      number_of_particles(120000),
      _window(std::make_unique<sf::RenderWindow>(
          sf::VideoMode(room_dimensions.x, room_dimensions.y), "Star Stuff")),
      _emitter(std::make_unique<Emitter>(room_dimensions, number_of_particles)),
      _particles(std::make_unique<sf::VertexArray>(sf::Points, number_of_particles)),
      _mouse_position(room_dimensions.x / 2, room_dimensions.y / 2) {}

void Engine::_processInput() {
    sf::Event event;
    while (_window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                _window->close();
                break;

            case sf::Event::MouseMoved:
                _mouse_position = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*_window));
                break;

            case sf::Event::MouseLeft:
                _mouse_position = sf::Vector2f(room_dimensions.x / 2, room_dimensions.y / 2);
                break;

            default:
                break;
        }
    }
}

void Engine::_update(sf::Time dt) {
    const auto& dustGrains = _emitter->getParticles();  // Access particles by reference

    _emitter->update(_mouse_position, dt);  // Update emitter with mouse position

    int i = 0;
    for (const auto& temp : dustGrains) {
        (*_particles)[i].position = temp._position;  // Update particle position
        (*_particles)[i].color = temp._color;        // Update particle color
        ++i;
    }
}

void Engine::_render() {
    _window->clear(sf::Color::Black);  // Clear the window with black color
    _window->draw(*_particles, sf::BlendAdd);  // Draw particles with additive blending
    _window->display();  // Display the updated frame
}

void Engine::run() {
    sf::Clock game_clock;
    const sf::Time time_per_frame = sf::seconds(1.f / 60.f);
    sf::Time time_since_last_update = sf::Time::Zero;

    while (_window->isOpen()) {
        _processInput();  // Handle input events
        time_since_last_update += game_clock.restart();

        // Update simulation in fixed time steps
        while (time_since_last_update > time_per_frame) {
            time_since_last_update -= time_per_frame;
            _processInput();  // Handle input again to avoid lag during update
            _update(time_per_frame);  // Update simulation logic
        }

        _render();  // Render the current frame

        // Frame rate control: sleep if processing was faster than expected
        if (time_since_last_update < time_per_frame) {
            sf::sleep(time_per_frame - time_since_last_update);
        }
    }
}