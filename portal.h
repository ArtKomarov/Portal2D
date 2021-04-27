#ifndef PORTAL_H
#define PORTAL_H

#include <SFML/Audio.hpp>

#include "physelem.h"
#include "hero.h"

/// Portal type
enum {
    BLUE = 1,
    ORANGE = 2
};

/// State
enum {
    NOTCARYY = -2,
    NOTEXIST = -1,
    MOVE     = 1
}; // + Sides from physelem

class Portal : public PhysElem {
    int Type_;
    int portSide_;

    sf::IntRect NotExistRect_;
    sf::IntRect StayRect_;
    sf::IntRect MoveRect_;

    Hero*   hero_;
    Portal* port2_;


    int State_; //-2 - inactive (do not teleport), -1 - does not exist, 0 - stay, 1 - left, 2 - right, 3 - up, 4 - down

    float defSpeed_;

    sf::SoundBuffer soundBuff_;
    sf::Sound       fireSound_;

    // Mouse position after click
    //sf::Vector2f Target_;

    //sf::Texture* texture_;
    //sf::Sprite*  sprite_;
public:
    Portal(int type, sf::Texture* texture, sf::Sprite* sprite, Hero* hero);

    /// Setters
    void setPortal2 (Portal* portal2);

    /// Getters
    int getPortSide () const;

    /// Override physical functions
    void          Action () override;
    sf::FloatRect getGlobalBounds() const override;
    //sf::Vector2i Move   () override;

    /// Handle mouse click
    void eventHendler (const sf::Event& event, const sf::Vector2f &mousePos) override;


    /// Override graphical features
    virtual void Intersect (GrElem& elem, sf::Vector2u windowSize) override;

//    void          Actions         ()                             override;
//    int           Update          (sf::RenderWindow&   target)   override;
//    int           Draw            (sf::RenderWindow&   target)   override;
//    void          Move            (sf::Vector2f        offset)   override;
//    void          Stop            ()                             override;
//    bool          EventHendler    (const sf::Event&    event)    override;
//    bool          MouseHendler    (const sf::Event& event, sf::Vector2f MousePos) override;

//    /// Accesors
//    void  SetMove     (int MoveSide);
//    void  SetSpeed    (float speedX, float speedY);
//    void  SetTarget   (sf::Vector2i mousePos);
//    float GetSpeed    ();
//    int   GetMoveSide ();

//    /// Personal actions
//    bool PortalMove(sf::Vector2f offset, bool withElapsed = true, float ElapsedSec = 0.1);
//    void SpriteMove (const sf::Vector2f& offset, bool withElapsed = true, float ElapsedSec = 0.1); // 85x40

};

#endif // PORTAL_H
