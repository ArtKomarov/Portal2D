#ifndef BOUNDARY_H
#define BOUNDARY_H

//#include "graphics.h"
#include "grelem.h"

/// Types for portals
enum {
    BLACK_BOUNDARY = 0,
    WHITE_BOUNDARY = 1
};

class Boundary : public GrElem {
    int type_; // boundary type
public:
    /// Constructor
    Boundary (int type, sf::Texture* texture, sf::Sprite* sprite);

    /// Destructor
    virtual ~Boundary();

    /// Getters
    int getType() const;

    ///// Override graphical features /////
//    /// Setters
//    void setPosition (const sf::Vector2f& position) override;

//    /// Getters
//    const sf::Vector2f&  getPosition     () const override;
//    sf::FloatRect        getGlobalBounds () const override;

//    /// Update (draw boundary)
//    int  Update   (sf::RenderWindow &target) override;

//    /// Positioning
//    void mustMove (sf::Vector2f offset) override;
//    void Stop     ()                    override;
//    void Intersect (GrElem& elem, sf::Vector2u windowSize) override;

};

#endif // BOUNDARY_H
