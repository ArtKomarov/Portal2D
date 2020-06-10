#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>
#include <map>

#include <SFML/Graphics.hpp>

/// Sides
enum {
    LEFT  = 1,
    RIGHT = 2,
    UP    = 3,
    DOWN  = 4
};

/// Move ability
enum {
    BOUNDARY = 0,
    PORTAL   = 1,
    HERO     = 2
};

/// Is elem blocked on sides?
struct Blocked {
    bool left_  = true;
    bool right_ = true;
    bool top_   = true;
    bool bot_   = true;

    Blocked ();
    Blocked& operator = (bool state);
    bool operator == (bool state);
};

/// Window parameters
const unsigned int WINDOW_SIZE = 1000;
const unsigned int WINDOW_BOUNDS_OFFSET = 10;

///// Graphic elements interface /////
class GrElem {
protected:
    /// 0 - immovable, 1 - hero, 2 - light stuff
    int     MoveAbility_ = 0;
    Blocked block_;
public:
    //int Init() = 0;
    /// Setters
            void SetStability (bool condition);
    virtual void SetPosition  (const sf::Vector2f& position) = 0;

    /// Getters
    int                   GetMoveAbility () const;      // Only non-virtual
    virtual sf::Vector2f  GetPosition    () const = 0;
    virtual sf::FloatRect GetGlobalBounds() const = 0;

    /// Updates & Drowind stuff
    virtual void Actions      ()                           = 0;
    virtual int  Update       (sf::RenderWindow& target)   = 0;
    virtual int  Draw         (sf::RenderWindow& target)   = 0;
    virtual void Move         (sf::Vector2f      offset)   = 0;
    virtual void Stop         ()                           = 0;
    virtual bool EventHendler (const sf::Event&  event)    = 0;

    virtual bool MouseHendler (const sf::Event& event, sf::Vector2f MousePos) = 0;

    /// Necessary virtual destructor
    virtual      ~GrElem ();
    // int Render() = 0;

    friend void MoveApart (GrElem& elem1, GrElem& elem2);
};

/// Check, if elements are intersect
bool Intersect (const GrElem& elem1, const GrElem& elem2);

/// Push off two elements
//void MoveApart (GrElem& elem1, GrElem& elem2);

///// Boundary class /////
enum {
    BLACK_BOUNDARY = 0,
    WHITE_BOUNDARY = 1
};

class Boundary : public GrElem {
    int          type_;
    sf::Shape*   shape_;
    sf::Texture* texture_;
public:
    /// Constructor
    Boundary(int type, sf::Shape* shape, sf::Texture* texture);

    /// Accesors
    const sf::Vector2f getPosition() const;

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
};


///// Main graphics class /////

class graphics {
    sf::RenderWindow* window_;
    sf::Sprite*       windowSprite_;
    //const size_t      PosChangeMax_;
    //size_t            PosChange_;

    sf::Texture*      GlobalTexture_;

    // All graphical parts of elements
    std::map<std::string, GrElem*>* elements_;

public:
    /// Constructors
    graphics  ();
    graphics  (std::map<std::string, GrElem*> *elements, sf::Texture* GlobalTexture,
               sf::Sprite* windowSprite,  unsigned int WindowSize = WINDOW_SIZE);

    ///Destructor
    ~graphics ();

    /// Accessors
    bool WindowOpen () const;

    bool WindowPoolEvent (sf::Event &event);

    void CloseWindow ();

    void SetGlobalTexture(sf::Texture* texture);

    void SetElements     (std::map<std::string, GrElem*>* elems);

    /// Update
    void UpdateWindow (); // sf::Time& elapsed);

    /// Try to hendle event
    bool EventHendler(const sf::Event& event);

};


#endif // GRAPHICS_H
