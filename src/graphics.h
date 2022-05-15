#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>

#include <SFML/Graphics.hpp>

#include "grelem.h"

/*
 * Физика содержит:
 *   - обработка событий
 *   - action
*/

///// Main graphics class /////

class graphics {
    sf::RenderWindow* window_; // main window
    sf::Sprite*       background_; // background sprite

    // All graphical parts of elements
    std::vector<GrElem*>* elements_;

public:
    /// Constructors
    graphics (sf::RenderWindow* window, sf::Sprite* background, std::vector<GrElem*> *elements);

    /// Destructor
    ~graphics ();

    /// Work with window
    bool windowIsOpen    () const;
    bool windowPoolEvent (sf::Event &event);

    sf::Vector2f getMousePosition() const;
//    void clearWindow     ();
//    void displayWindow   ();
    void closeWindow ();

    /// Start screen
    void Start ();

    /// Last screen
    void Finish ();

    /// Positioning && collision
    void Placement ();

    /// Used in update, erase objects, clear window
    bool Clean();

    /// Drawing elements
    void Update ();

//    /// Setters
//    void SetGlobalTexture (sf::Texture          *texture);
//    void SetElements      (std::vector<GrElem*> *elems);
//    set window?

//    /// Update
//    void updateWindow (); // sf::Time& elapsed);

//    /// Try to hendle event
//    bool eventHendler(const sf::Event& event);

};

/// Support positioning functions
void checkIters (unsigned iter, unsigned maxIters);

bool checkOutOfBound_X (GrElem* elem, int bound, bool bigger);

bool checkOutOfBound_Y (GrElem* elem, int bound, bool bigger);

#endif // GRAPHICS_H
