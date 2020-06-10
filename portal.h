#ifndef PORTAL_H
#define PORTAL_H

#include "graphics.h"

enum {
    BLUE = 1,
    ORANGE = 2
};

class Portal : public GrElem {
    int Type_;
    int MoveSide_; //-1 - does not exist, 0 - none, 1 - left, 2 - right, 3 - up, 4 - down

    // Mouse position after click
    sf::Vector2i Target_;

    float Speed_;
    float SpeedX_;
    float SpeedY_;

    sf::Texture* texture_;
    sf::Sprite*  sprite_;
public:
    Portal(int type, sf::Texture* texture);

    /// Override graphical features
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

    /// Accesors
    void  SetMove     (int MoveSide);
    void  SetSpeed    (float speedX, float speedY);
    void  SetTarget   (sf::Vector2i mousePos);
    float GetSpeed    ();
    int   GetMoveSide ();

    /// Personal actions
    bool PortalMove(sf::Vector2f offset, bool withElapsed = true, float ElapsedSec = 0.1);
    void SpriteMove (const sf::Vector2f& offset, bool withElapsed = true, float ElapsedSec = 0.1); // 85x40

};

#endif // PORTAL_H
