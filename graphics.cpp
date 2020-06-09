#include "graphics.h"

#include <iostream>
#include <unistd.h>

graphics::graphics() :
    window_(sf::VideoMode(800, 800), "SFML works!"),
    PosChangeMax_(1000),
    PosChange_(0),
    hero_(sf::Vector2f(window_.getSize().x / 2, window_.getSize().y / 2)),
    shape_(100.f) {

    // Init window
    window_.setPosition(sf::Vector2i(0, 0));
    window_.clear(sf::Color::Cyan);

    shape_.setFillColor(sf::Color::Green);

    //window_.setVerticalSyncEnabled(true);
    window_.setFramerateLimit(60);

    //hero_.setColor(sf::Color(255, 0, 0));
    window_.draw(hero_.GetSprite());
}

// Accessors
bool graphics::WindowOpen() const {
    return window_.isOpen();
}

bool graphics::WindowPoolEvent(sf::Event &event) {
    return window_.pollEvent(event);
}

void graphics::HeroMove(const sf::Vector2f& offset) {
    hero_.SpriteMove(offset);
}

void graphics::HeroStop() {
    hero_.SpriteStop();
}

void graphics::CloseWindow() {
    window_.close();
}

// Update
void graphics::UpdateWindow(sf::Time& elapsed) {
//    window_.setPosition(
//                sf::Vector2i(
//                    window_.getPosition().x + rand() % 10,
//                    window_.getPosition().y + rand() % 10
//                    )
//                );
//    window_.setSize(sf::Vector2u(100 + rand() % 500, 100 + rand() % 500));
//    shape_.setPosition(sf::Vector2f(window_.getPosition().x, window_.getPosition().y));

    std::cout << window_.getPosition().x << " " << window_.getPosition().y << std::endl;
//    hero_.move(1, 0);
//    if(elapsed.asMilliseconds() > 200) {
//        hero_.setTextureRect(sf::IntRect((hero_.getTextureRect().left + 50) % (50*6), hero_.getTextureRect().top, 50, 60));
//        elapsed = elapsed.Zero;
//        std::cout << "gg";
//    }

    window_.clear(sf::Color::Cyan);
    window_.draw(shape_);
    window_.draw(hero_.GetSprite());
    window_.display();
//    texture_.update(window_);
    //sleep(0.1);
}

HeroSprite::HeroSprite(const sf::Vector2f& position) :
    lastMove_(1, 1) {
    if(!texture_.loadFromFile("/home/artem/Main/Games/HeroRunSprite.png",
                               sf::IntRect(0, 0, 1000, 1000)
                               )) {
        std::cerr << "Error while loading texture" << std::endl;
    }
    sprite_.setTexture(texture_);
    sprite_.setTextureRect(sf::IntRect(0, 0, 49, 60));
    sprite_.setPosition(position);
}

const sf::Sprite& HeroSprite::GetSprite() const {
    return sprite_;
}

void HeroSprite::SpriteMove(const sf::Vector2f& offset) {
    // Move sprite
    sprite_.setPosition(sprite_.getPosition() + offset);

    // Select next texture rectangle
    if(offset.x > 0) {
        int CurrAreaNum = sprite_.getTextureRect().left / 49;
        std::cout << CurrAreaNum << std::endl;
        CurrAreaNum -= (CurrAreaNum > 7);
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

        if(lastMove_.x < 0)
            left = 0;

        sprite_.setTextureRect(sf::IntRect(left, 0, 49, 60));

        lastMove_.x = 1;
    }
    else if(offset.x < 0) {
        int left = texture_.getSize().x - 49 - (texture_.getSize().x - sprite_.getTextureRect().left) % (49*5);

        if(lastMove_.x > 0)
            left = texture_.getSize().x - 49;

        sprite_.setTextureRect(sf::IntRect(left, 60, 49, 60));

        lastMove_.x = -1;
    }
}

void HeroSprite::SpriteStop() {
    // Set sprite stay area
    int left = 0;
    int top  = 0;

    // If she run into another side
    if(lastMove_.x < 0) {
        left = texture_.getSize().x - 49;
        top = 60;
    }

    sprite_.setTextureRect(sf::IntRect(left, top, 49, 60));
}
