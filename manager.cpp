#include "manager.h"
#include "graphics.h"

Manager::Manager() :
    gr_(),
    clock_() {
}

void Manager::GameLoop() {
    sf::Time elapsed;
    //bool HeroRun; // Did hero run in this loop?

    while (gr_.WindowOpen()) {
        sf::Event event;

        while (gr_.WindowPoolEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                gr_.CloseWindow();
                break;
            case sf::Event::KeyPressed:
                KeyPressedHandler(event);
                break;
            case sf::Event::KeyReleased:
                KeyNotPressedHandler();
                break;
            default:
                break;
            }
        }

        elapsed += clock_.restart();
        gr_.UpdateWindow(elapsed);
    }
}

void Manager::KeyPressedHandler(const sf::Event& event) {
    switch (event.key.code) {
    case sf::Keyboard::D:
        gr_.HeroMove(sf::Vector2f(5, 0));
        break;
    case sf::Keyboard::A:
        gr_.HeroMove(sf::Vector2f(-5, 0));
        break;
    case sf::Keyboard::W:
        gr_.HeroMove(sf::Vector2f(0, -10));
        break;
    case sf::Keyboard::S:
        gr_.HeroMove(sf::Vector2f(0, 2));
        break;
    case sf::Keyboard::Escape:
        gr_.CloseWindow();
        break;
    default:
        break;
    }
}

void Manager::KeyNotPressedHandler() {
    gr_.HeroStop();
}
