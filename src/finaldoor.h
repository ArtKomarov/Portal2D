#ifndef FINALDOOR_H
#define FINALDOOR_H

#include "physelem.h"

const int DEFAULT_OPEN_SPEED = 10;

/// Door states
enum {
    CLOSED = 0,
    OPEN   = 7
};

const int FDOOR_POS_X = 29;
const int FDOOR_POS_Y = 321;

const int FDOOR_WIDTH = 72;
const int FDOOR_HEIGHT = 53;

class FinalDoor : public GrElem {
    int State_;

    sf::Clock toOpen_;
    sf::Clock toClose_;

    /// How fast door opens
    float openSpeed_; // it is not the same as physical element speed!

public:
    FinalDoor (sf::Texture* texture, sf::Sprite* sprite);

    /// Override graphical functons ///
    /// Update (drow)
    void Update (sf::RenderWindow& target) override;

    /// Intersect with hero
    void Intersect (GrElem& elem, sf::Vector2u windowSize) override;
};

#endif // FINALDOOR_H
