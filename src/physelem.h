#ifndef PHYSELEM_H
#define PHYSELEM_H

#include <vector>

#include "grelem.h"


/// Sides
enum {
    STAY  = 0,
    LEFT  = 1,
    RIGHT = 2,
    UP    = 3,
    DOWN  = 4
};

/// Is elem blocked on sides?
struct Blocked {
    bool left_  = true;
    bool right_ = true;
    bool top_   = true;
    bool bot_   = true;

    Blocked ();
    Blocked& operator=  (bool state);
    bool     operator== (bool state);
};

class PhysElem : public GrElem {
protected:
    //float       moveAbility_ = 0; // Lightness
    // Sides, that you can't move
    Blocked block_;

    /// Speed
    float speedX_; // dm/s (~10 pix/s)
    float speedY_; // dm/s (~10 pix/s)

    sf::Clock moveClockX_;
    sf::Clock moveClockY_;

    /// Acceleration
    float accelX_; // dm/s^2
    float accelY_; // dm/s^2

    sf::Clock accelClockX_;
    sf::Clock accelClockY_;

    void incrSpeedX (float speedOffset);
    void incrSpeedY (float speedOffset);
public:

    /// Constructors
    //PhysElem ();
    PhysElem (sf::Texture* texture, sf::Sprite* sprite);

    /// Destructor
    ~PhysElem ();

    /// Setters
    void setBlock (bool state, int side = -1);

    void setAccelX (float accelX);
    void setAccelY (float accelY);

    void incrAccelX (float accelOffset);
    void incrAccelY (float accelOffset);

    void setSpeedX (float speedX);
    void setSpeedY (float speedY);

    void clockRestart ();

    /// Getters
    //int GetMoveAbility () const;
    bool getBlock (int side = DOWN) const;

    sf::Vector2f getSpeed() const;
    sf::Vector2f getAccel() const;

    //              Override graphical part             //
    // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^//

//    /// Setters
//    virtual void setPosition (const sf::Vector2f& position) override;

//    /// Getters
//    virtual const sf::Vector2f&  getPosition     () const override;
//    virtual sf::FloatRect        getGlobalBounds () const override;

//    /// Update (draw element)
//    virtual void Update (sf::RenderWindow &target) override;

//    /// Positioning
//    virtual void mustMove  (sf::Vector2f offset) override;
//    virtual void Stop      ()                    override;
//    virtual void Intersect (GrElem& elem, sf::Vector2u windowSize) override;

    // Support function, that can be used in intersect

    /// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv ///



    //                Pysical element stuff               //
    // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^//

    /// Every iteration action
    virtual void Action ();

    /// Move element
    virtual sf::Vector2i Move();
    /// Stop sprite
    //virtual void Stop () = 0;

    // vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv //

    /// Handle event
    virtual void eventHendler (const sf::Event& event, const sf::Vector2f& mousePos);

    //friend void MoveApart (GrElem& elem1, GrElem& elem2); // in grelem

};

/// Support functions
/// Default kind of intersection
void pushOff (PhysElem &this_elem, GrElem& elem, sf::Vector2u windowSize);

void getDistances (PhysElem &this_elem, GrElem &elem, float& LDist, float& RDist, float& TDist, float& BDist);

int getPushSide (PhysElem &this_elem, GrElem &elem, sf::Vector2u &windowSize);

void pushToSide (PhysElem &this_elem, GrElem &elem, int side);

#endif // PHYSELEM_H
