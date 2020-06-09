#ifndef HERO_H
#define HERO_H

#include "SFML/Graphics.hpp"
#include "graphics.h"

struct Blocked {
    bool left_;
    bool right_;
    bool top_;
    bool bot_;

    Blocked ();
};

class Hero : public GrElem {
    /// Graphics part
    sf::Texture texture_;
    sf::Sprite  sprite_;

    /// Properties
    int  Speed_;
    int  inJumping_;
    bool inFalling_;
    Blocked blocked_;

    /// Other
    sf::Vector2f lastMove_;

public:
    /// Constructors/Destructor
    Hero  ();
    Hero  (const GrElem& hero);
    Hero  (const sf::Vector2f& position);
    ~Hero ();

    /// Accessors
    const sf::Vector2f GetLegPosition();
    //const sf::Sprite& GetSprite() const;


    /// Override graphical methods
    void          SetPosition     (const sf::Vector2f& position) override;
    sf::Vector2f  GetPosition     () const                       override;
    sf::FloatRect GetGlobalBounds () const                       override;
    int           Update          (sf::RenderTarget&   target)   override;
    int           Draw            (sf::RenderTarget&   target)   override;
    bool          EventHendler    (const sf::Event&    event)    override;

    /// Personal hendlers
    bool KeyPressedHandler(const sf::Event& event);
    bool KeyNotPressedHandler(const sf::Event& event);

    /// Hero move ( to-to-to-to-to-toooooo :D )
    void SpriteMove(const sf::Vector2f& offset, bool withElapsed = true);
    void SpriteStop();
};

#endif // HERO_H
