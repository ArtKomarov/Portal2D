#include <iostream>

#include "hero.h"
#include "graphics.h"

const int JUMP_SPRITE_LEFT_OFFSET =  49 * 5 + 30;

Blocked::Blocked () :
    left_  (false),
    right_ (false),
    top_   (false),
    bot_   (false) {}

Hero::Hero() :
    Speed_     (10),
    inJumping_ (0),
    inFalling_ (false),
    blocked_   () {
    if(!texture_.loadFromFile("/home/artem/Main/Games/HeroRunSprite.png",
                               sf::IntRect(0, 0, 1000, 1000)
                               )) {
        std::cerr << "Error while loading texture" << std::endl;
    } else {
        sprite_.setTexture     (texture_);
        sprite_.setTextureRect (sf::IntRect(0, 0, 49, 63));
    }
}

Hero::Hero(const GrElem &hero) :
    texture_(dynamic_cast<const Hero &> (hero).texture_),
    sprite_ (dynamic_cast<const Hero &> (hero).sprite_),
    lastMove_(1, 1) {}

Hero::Hero(const sf::Vector2f& position) :
    lastMove_(1, 1) {
    if(!texture_.loadFromFile("/home/artem/Main/Games/HeroRunSprite.png",
                               sf::IntRect(0, 0, 1000, 1000)
                               )) {
        std::cerr << "Error while loading texture" << std::endl;
    }

    sprite_.setTexture     (texture_);
    sprite_.setTextureRect (sf::IntRect(0, 0, 49, 63));
    sprite_.setPosition    (position);
}

Hero::~Hero() {}

const sf::Vector2f Hero::GetLegPosition() {
    return sf::Vector2f(sprite_.getPosition().x, sprite_.getPosition().y - 30);
}

//const sf::Sprite& Hero::GetSprite() const {
//    return sprite_;
//}

bool Hero::EventHendler(const sf::Event &event) {
    bool catched = false;
    switch (event.type) {
    case sf::Event::KeyPressed:
        catched = this->KeyPressedHandler(event);
        break;
    case sf::Event::KeyReleased:
        catched = this->KeyNotPressedHandler(event);
        break;
    default:
        catched = false;
    }
    return catched;
}

bool Hero::KeyPressedHandler(const sf::Event& event) {
    if(event.type != sf::Event::KeyPressed)
        return false;
    bool catched = false;


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this->SpriteMove(sf::Vector2f(Speed_, 0), false);
        catched = true;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->SpriteMove(sf::Vector2f(-Speed_, 0), false);
        catched = true;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        this->SpriteMove(sf::Vector2f(0, -Speed_), false);
        catched = true;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        this->SpriteMove(sf::Vector2f(0, Speed_), false);
        catched = true;
    }


    return catched;
}

/// When move key not pressed, stop the hero (set proper sprite)
bool Hero::KeyNotPressedHandler (const sf::Event& event) {
    this->SpriteStop();
    return false;
}

/// Set hero position
void Hero::SetPosition (const sf::Vector2f &position) {
    sprite_.setPosition(position);
}

/// Get hero position
sf::Vector2f Hero::GetPosition() const {
    return sprite_.getPosition();
}

/// Get sprite bounds for intersection
sf::FloatRect Hero::GetGlobalBounds() const {
    return sprite_.getGlobalBounds();
}

/// Update hero
int Hero::Update (sf::RenderTarget &target) {
    if(inJumping_ > 0) {
        if(--inJumping_ > 0)
            this->SpriteMove(sf::Vector2f(0, -Speed_));
        else {
            this->SpriteStop();
            inFalling_ = true;
        }
    }
    else if(!blocked_.bot_) {
        inFalling_ = true;
        this->SpriteMove(sf::Vector2f(0, Speed_));
    }

    return this->Draw(target);
}

/// Draw hero sprite
int Hero::Draw (sf::RenderTarget &target) {
    target.draw(sprite_);
    return 0;
}

/// Move hero, move his sprite
void Hero::SpriteMove(const sf::Vector2f& offset, bool withElapsed) { // TODO: Разбить по функциям!!!
    // Set clock for checking elapsed time
    static sf::Clock moveClock;

    if(withElapsed) {
        sf::Time elapsed = moveClock.getElapsedTime();
        if(elapsed.asSeconds() < 0.1)
            return;
        moveClock.restart();
    }

    // Move hero
    sprite_.move(offset);

    // Select next texture rectangle (move sprite)
    if(offset.y < 0) {
        if(!blocked_.top_) {
            int left;

            if(offset.x < 0 || (offset.x == 0 && lastMove_.x < 0))
                left = texture_.getSize().x - 49 - JUMP_SPRITE_LEFT_OFFSET;
            else
                left = JUMP_SPRITE_LEFT_OFFSET;

            sprite_.setTextureRect(sf::IntRect(left, 63 * (left != 5 * 49 + 30), 49, 63));
        }
        else {
            inJumping_ = 0;
            inFalling_ = true;
        }
    }
    if(offset.x != 0) {

        int CurrAreaNum;
        if(sprite_.getTextureRect().top == 0) {
            CurrAreaNum  = sprite_.getTextureRect().left / 49;
            CurrAreaNum -= (CurrAreaNum > 7);
        }
        else {
            CurrAreaNum  = (texture_.getSize().x - sprite_.getTextureRect().left) / 49 - 1;
            CurrAreaNum -= (CurrAreaNum > 7);
        }
//        int left = (
//                    CurrAreaNum * 49 +
//                    (CurrAreaNum >= 4) * 30 + (CurrAreaNum >= 6) * 10 + (CurrAreaNum >= 7) * 10 + (CurrAreaNum >= 8) * 15 + (CurrAreaNum >= 9) * 15
//                    ) % (49*10 + 90);
        int left;
        if(CurrAreaNum != 9) {
            left = (CurrAreaNum + 1) * 49;
            switch (CurrAreaNum + 1) {
            case 4:
                left += 20;
                break;
            case 5:
                left += 30;
                break;
            case 6:
                left += 40;
                break;
            case 7:
                left += 50;
                break;
            case 8:
                left += 75;
                break;
            case 9:
                left += 90;
                break;
            }
        }
        else {
            left = 49*3;
        }

        if(lastMove_.x < 0 && offset.x > 0)
            left = 0;

        if(offset.x < 0) {
            if(lastMove_.x > 0)
                left = texture_.getSize().x - 49;
            else
                left = texture_.getSize().x - 49 - left;
        }

        sprite_.setTextureRect(sf::IntRect(left, 63 * (offset.x < 0), 49, 63));

        if(offset.x > 0)
            lastMove_.x = 1;
        else if(offset.x < 0)
            lastMove_.x = -1;

    }
//    }
//    else if(offset.x < 0) {
//        int left = texture_.getSize().x - 49 - (texture_.getSize().x - sprite_.getTextureRect().left) % (49*5);

//        if(lastMove_.x > 0)
//            left = texture_.getSize().x - 49;

//        sprite_.setTextureRect(sf::IntRect(left, 60, 49, 60));

//        lastMove_.x = -1;
//    }

}

void Hero::SpriteStop() {
    // Set sprite stay area
    int left = 0;
    int top  = 0;

    // If she run into another side
    if(lastMove_.x < 0) {
        left = texture_.getSize().x - 49;
        top = 63;
    }

    sprite_.setTextureRect(sf::IntRect(left, top, 49, 63));
}
