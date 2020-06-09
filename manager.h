#ifndef MANAGER_H
#define MANAGER_H

#include <map>

#include "graphics.h"
#include "hero.h"


class Manager {
    Hero      hero_;
    std::map<const char*, Boundary*> boundaries_;
    graphics*  gr_;
    sf::Clock clock_;
public:
    // Constructors/Destructor
    Manager();
    ~Manager();

    // Main loop
    void GameLoop();

    void KeyPressedHandler(const sf::Event& event);
    void KeyNotPressedHandler();
};

#endif // MANAGER_H
