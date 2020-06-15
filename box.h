#ifndef BOX_H
#define BOX_H

#include "physelem.h"

/// The simplest physical element
class Box : public PhysElem {
    /// Constuctor
public:
    Box (sf::Texture* texture, sf::Sprite* sprite);


    /// Override intersect by push off
    void Intersect (GrElem& elem, sf::Vector2u windowSize) override;

    /// Overrude get global bounds for pretty moving
    sf::FloatRect getGlobalBounds() const override;
};

#endif // BOX_H
