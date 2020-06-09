#include "hero.h"
#include "graphics.h"

Hero::Hero(const sf::Vector2f& position) :
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

const sf::Sprite& Hero::GetSprite() const {
    return sprite_;
}

bool Hero::EventHendler(const sf::Event &event) {
    switch (event.key.code) {
    case sf::Keyboard::D:
        this->SpriteMove(sf::Vector2f(5, 0));
        break;
    case sf::Keyboard::A:
        this->SpriteMove(sf::Vector2f(-5, 0));
        break;
    case sf::Keyboard::W:
        this->SpriteMove(sf::Vector2f(0, -10));
        break;
    case sf::Keyboard::S:
        this->SpriteMove(sf::Vector2f(0, 2));
        break;
    default:
        return false;
    }
    return true;
}

int Hero::Update (sf::RenderTarget &target) {
    this->Draw(target);
}

int Hero::Draw (sf::RenderTarget &target) {
    target.draw(sprite_);
}

void Hero::SpriteMove(const sf::Vector2f& offset) {
    // Move sprite
    //sprite_.setPosition(sprite_.getPosition() + offset);
    sprite_.move(offset);

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

void Hero::SpriteStop() {
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
