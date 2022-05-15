#ifndef HERO_H
#define HERO_H

#include "SFML/Graphics.hpp"
#include "graphics.h"
#include "physics.h"
//#include "portal.h"

class Hero : public PhysElem {
    float defSpeedX_;
    float defSpeedY_;

    /// Properties
    //Portal* portals_[2];
    //bool inFalling_;

    /// Other
    sf::Vector2f lastMove_;

public:
    /// Constructors/Destructor
    Hero  (sf::Texture* texture, sf::Sprite* sprite);
//    Hero  (sf::Texture* globalTexture);
//    Hero  (const GrElem& hero);
//    Hero  (const sf::Vector2f& position);
    ~Hero ();

    /// Accessors
    //const sf::Sprite& GetSprite() const;
    //Portal** GetPortals();
    sf::Vector2f getLastMove() const;

    /// Setters
    void setDefSpeedX (float speedX);
    void setDefSpeedY (float speedY);


    /// Override graphical methods
//    void          SetPosition     (const sf::Vector2f& position) override;
//    sf::Vector2f  GetPosition     () const                       override;
//    sf::FloatRect GetGlobalBounds () const                       override;
//    int           Update          (sf::RenderWindow&   target)   override;
//    int           Draw            (sf::RenderWindow&   target)   override;
//    void          Move            (sf::Vector2f        offset)   override;

    /// Override physical functions
    void         Action () override;
    sf::Vector2i Move   () override;

    /// Override graphical functions
    virtual void Intersect (GrElem& elem, sf::Vector2u windowSize) override;

    /// Events of release buttons, TODO: R
    void eventHendler (const sf::Event& event, const sf::Vector2f &mousePos) override;

    /// Personal functions
    void Stop ();

//    bool MouseHendler(const sf::Event& event, sf::Vector2f MousePos);

//    /// Personal hendlers
//    bool KeyPressedHandler    (const sf::Event& event);
//    void MousePressedHendler();
//    bool KeyNotPressedHandler (const sf::Event& event);

//    /// Hero move ( to-to-to-to-to-toooooo :D )
//    bool HeroMove  (sf::Vector2f offset, bool withElapsed = true,  float ElapsedSec = 0.1);
//    void SpriteMove(const sf::Vector2f& offset, bool withElapsed = true, float ElapsedSec = 0.1);
//    void SpriteStop();
};

#endif // HERO_H
