#ifndef GRELEM_H
#define GRELEM_H

#include <SFML/Graphics.hpp>

///// Graphic elements interface /////
class GrElem {
    bool active_;  // is element acitve, or it need to be deleted?
protected:
    bool essential_; // is this element essential to game?

    sf::Texture *texture_; // Element texture
    sf::Sprite  *sprite_;  // Element sprite
public:
    /// Constructors
    //GrElem ();
    GrElem (sf::Texture *texture, sf::Sprite *sprite);

    /// Setters
    //        void setTexture  (sf::Texture* texture);
    virtual void setPosition (const sf::Vector2f& position);

    void setActive (bool state);

    /// Getters
    bool getActive    () const;
    bool getEssential () const;

    virtual const sf::Vector2f&  getPosition     () const;
    virtual sf::FloatRect        getGlobalBounds () const;

    /// Update (Draw)
    virtual void Update (sf::RenderWindow& target);

    ///                   Positioning                     ///
    /// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^///

    /// MustMove == sprite.move()
    virtual void mustMove (sf::Vector2f offset);

    /// Stop sprite
    //virtual void Stop ();

    /// Actions while intersection
    /**
     * @brief Intersect
     * @param elem
     * @param windowSize
     *
     * Be carefull with this method.
     * Becouse it used when your element intersects all other elements.
     */
    virtual void Intersect (GrElem& elem, sf::Vector2u windowSize);

    /// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv ///

    /// Necessary virtual destructor
    virtual ~GrElem ();
};

#define IF_CLASS(CLASS_TYPE, CLASS_OBJECT, ELEM) \
    if((CLASS_OBJECT = dynamic_cast<CLASS_TYPE*>(&elem)) != nullptr)


#endif // GRELEM_H
