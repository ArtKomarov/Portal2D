#ifndef HERO_H
#define HERO_H

#include "SFML/Graphics.hpp"
#include "graphics.h"
#include "portal.h"

class Hero : public GrElem {
    /// Graphics part
    sf::Texture texture_;
    sf::Sprite  sprite_;

    /// Properties
    int  Speed_;
    int  inJumping_;
    Portal* portals_[2];
    //bool inFalling_;

    /// Other
    sf::Vector2f lastMove_;

public:
    /// Constructors/Destructor
    Hero  (sf::Texture* globalTexture);
    Hero  (const GrElem& hero);
    Hero  (const sf::Vector2f& position);
    ~Hero ();

    /// Accessors
    //const sf::Sprite& GetSprite() const;
    Portal** GetPortals();


    /// Override graphical methods
    void          SetPosition     (const sf::Vector2f& position) override;
    sf::Vector2f  GetPosition     () const                       override;
    sf::FloatRect GetGlobalBounds () const                       override;
    void          Actions         ()                             override;
    int           Update          (sf::RenderWindow&   target)   override;
    int           Draw            (sf::RenderWindow&   target)   override;
    void          Move            (sf::Vector2f        offset)   override;
    void          Stop            ()                             override;
    bool          EventHendler    (const sf::Event&    event)    override;
    bool          MouseHendler    (const sf::Event& event, sf::Vector2f MousePos) override;

    /// Personal hendlers
    bool KeyPressedHandler    (const sf::Event& event);
    void MousePressedHendler();
    bool KeyNotPressedHandler (const sf::Event& event);

    /// Hero move ( to-to-to-to-to-toooooo :D )
    bool HeroMove  (sf::Vector2f offset, bool withElapsed = true,  float ElapsedSec = 0.1);
    void SpriteMove(const sf::Vector2f& offset, bool withElapsed = true, float ElapsedSec = 0.1);
    void SpriteStop();
};

#endif // HERO_H
