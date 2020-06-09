#ifndef MANAGER_H
#define MANAGER_H

#include "graphics.h"


class Manager {
    graphics gr_;
    sf::Clock clock_;
public:
    Manager();
    void GameLoop();

    void KeyPressedHandler(const sf::Event& event);
    void KeyNotPressedHandler();
};

#endif // MANAGER_H
