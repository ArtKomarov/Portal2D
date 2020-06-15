#ifndef MANAGER_H
#define MANAGER_H

#include <map>

#include "graphics.h"
#include "physics.h"

#include "hero.h"


class Manager {
    graphics graphics_;
    physics  physics_;
public:
    // Constructors/Destructor
    //Manager(sf::Texture *GlobalTexture, Hero* hero, std::map<const char*, Boundary*>* boundaries,
    //        std::map <std::string, GrElem*> *grElements, sf::Sprite *windowSprite, unsigned int WindowSize = 1000);
    /// Constructor
    Manager (std::vector<GrElem*>* graphicalElems, std::vector<PhysElem*>* physicalElems,
             sf::RenderWindow* window, sf::Sprite* background);

    /// Destructor
    ~Manager ();

    /// Main loop
    void gameLoop();

    /// Handle all events
    void eventHandling();

    //void KeyPressedHandler(const sf::Event& event);
    //void KeyNotPressedHandler();
};

#endif // MANAGER_H
