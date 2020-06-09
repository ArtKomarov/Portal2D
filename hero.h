#ifndef HERO_H
#define HERO_H

#include "SFML/Graphics.hpp"
#include "graphics.h"


class Hero : GrElem {
    // Graphics part
    sf::Texture texture_;
    sf::Sprite  sprite_;

    // Other
    sf::Vector2f lastMove_;

public:
    // Constructors
    Hero(const sf::Vector2f& position);

    // Accessors
    const sf::Sprite& GetSprite() const;

    // Override graphical methods
    bool EventHendler (const sf::Event& event)   override;
    int Update       ()                         override;
    int Draw         (sf::RenderTarget& target) override;

    // Move
    void SpriteMove(const sf::Vector2f& offset);
    void SpriteStop();
};

#endif // HERO_H
