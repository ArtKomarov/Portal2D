#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics.hpp>

class HeroSprite {
    sf::Texture texture_;
    sf::Sprite  sprite_;

    sf::Vector2f lastMove_;

public:
    HeroSprite(const sf::Vector2f& position);

    // Accessors
    const sf::Sprite& GetSprite() const;

    // Move
    void SpriteMove(const sf::Vector2f& offset);
    void SpriteStop();
};

// Graphic elements interface
struct GrElem {
    //int Init() = 0;
    virtual int Update       (sf::RenderTarget& target) = 0;
    virtual int Draw         (sf::RenderTarget& target) = 0;
    virtual bool EventHendler (sf::Event event)         = 0;
    virtual     ~GrElem      ();
    // int Render() = 0;
};

class graphics {
    sf::RenderWindow window_;
    const size_t     PosChangeMax_;
    size_t           PosChange_;

    HeroSprite hero_;

    sf::CircleShape  shape_;
public:
    graphics();

    // Accessors
    bool WindowOpen() const;

    bool WindowPoolEvent(sf::Event &event);

    void HeroMove(const sf::Vector2f& offset);
    void HeroStop();

    void CloseWindow();

    // Update
    void UpdateWindow(sf::Time& elapsed);

};


#endif // GRAPHICS_H
