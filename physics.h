#ifndef PHYSICS_H
#define PHYSICS_H

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "physelem.h"

class physics {
    std::vector<PhysElem*>* elements_;
    float accelOfGravity_ = 300;
public:
    /// Constructor
    physics(std::vector<PhysElem*>* elements);

    /// Init physical elements
    /// (set move, acceleration clock to zero)
    void Start ();

    /// Elements actions loop
    void Activities ();

    /// Moves after activities
    void Movement ();

    /// Elements events handling loop
    void eventHandling (const sf::Event &event, const sf::Vector2f& mousePosition);



};

#endif // PHYSICS_H
