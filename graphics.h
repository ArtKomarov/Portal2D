#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>
#include <map>

#include <SFML/Graphics.hpp>

///// Graphic elements interface /////
struct GrElem {
    //int Init() = 0;
    /// Setters
    virtual void SetPosition  (const sf::Vector2f& position) = 0;
    /// Getters
    virtual sf::Vector2f  GetPosition ()    const            = 0;
    virtual sf::FloatRect GetGlobalBounds() const            = 0;

    /// Updates & Drowind stuff
    virtual int  Update       (sf::RenderTarget& target)     = 0;
    virtual int  Draw         (sf::RenderTarget& target)     = 0;
    virtual bool EventHendler (const sf::Event& event)       = 0;

    /// Necessary virtual destructor
    virtual      ~GrElem ();
    // int Render() = 0;
};

bool Intersect (const GrElem& elem1, const GrElem& elem2);

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
    int           Update          (sf::RenderTarget&   target)   override;
    int           Draw            (sf::RenderTarget&   target)   override;
    bool          EventHendler    (const sf::Event&    event)    override;
};


///// Main graphics class /////

class graphics {
    sf::RenderWindow* window_;
    const size_t     PosChangeMax_;
    size_t           PosChange_;

    // All graphical parts of elements
    std::map<std::string, GrElem*> elements_;

public:
    // Constructors/Destructor
    graphics  ();
    graphics  (std::map<std::string, GrElem*> &elements);
    ~graphics ();

    // Accessors
    bool WindowOpen () const;

    bool WindowPoolEvent (sf::Event &event);

    void CloseWindow ();

    // Update
    void UpdateWindow (); // sf::Time& elapsed);

};


#endif // GRAPHICS_H
