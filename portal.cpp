#include <iostream>

#include "portal.h"

Portal::Portal(int type, sf::Texture* texture) :
    Type_(type),
    MoveSide_(-1),
    Speed_(70),
    SpeedX_(0),
    SpeedY_(0),
    texture_(texture),
    sprite_(new sf::Sprite(*texture)) {

    this->SetPosition(sf::Vector2f(500, 500));
    MoveAbility_ = PORTAL;
}

void Portal::SetPosition(const sf::Vector2f &position) {
    std::cout << __PRETTY_FUNCTION__ << ": " << position.x << " " << position.y << std::endl;
    sprite_->setPosition(position);
}

sf::Vector2f Portal::GetPosition() const {
    return sprite_->getPosition();
}

sf::FloatRect Portal::GetGlobalBounds() const {
    return sprite_->getGlobalBounds();
}

void Portal::Actions() {
    if(MoveSide_ > 0)
        this->PortalMove(sf::Vector2f(SpeedX_, SpeedY_));
//    switch (MoveSide_) {
//    case -1:
//        break;
//    case 0:
//        break;
//    case LEFT:
//        this->PortalMove(sf::Vector2f(-Speed_, 0));
//        break;
//    case RIGHT:
//        this->PortalMove(sf::Vector2f(Speed_, 0));
//        break;
//    case UP:
//        this->PortalMove(sf::Vector2f(Speed_, -1));
//        break;
//    case DOWN:
//        this->PortalMove(sf::Vector2f(Speed_, 1));
//        break;
//    default:
//        break;
//    }
}

int Portal::Update(sf::RenderWindow &target) {

    if(MoveSide_ > 0)
        block_ = false;

    if(SpeedX_ == 0 && SpeedY_ == 0 && MoveSide_ > 0) {

        float speedX = Target_.x - this->GetPosition().x - this->GetGlobalBounds().width / 2; //+ target.mapPixelToCoords(target.getPosition()).x; // BAD POSITION!!! BAG!
        float speedY = Target_.y - this->GetPosition().y - this->GetGlobalBounds().height / 2; //+ target.mapPixelToCoords(target.getPosition()).y;

        std::cout << "window: " << target.mapPixelToCoords(target.getPosition()).x << " " << target.mapPixelToCoords(target.getPosition()).y << std::endl;
        std::cout << "target: " << Target_.x << " " << Target_.y << std::endl;
        std::cout << "Portal pos: " << this->GetPosition().x << " " << this->GetPosition().y << std::endl;

        float Sum = std::abs(speedX) + std::abs(speedY);

        // Normalize * speed
        speedX = (speedX / Sum) * this->GetSpeed();
        speedY = (speedY / Sum) * this->GetSpeed();

        this->SetSpeed(speedX, speedY);
    }


    if(MoveSide_ > 0)
        sprite_->setTextureRect(sf::IntRect(185, 27 + 38 * (Type_ == ORANGE), 10, 30));
    else if(MoveSide_ == 0)
        sprite_->setTextureRect(sf::IntRect(160, 27 + 38 * (Type_ == ORANGE), 10, 30));
    else
        sprite_->setTextureRect(sf::IntRect(190, 27, 10, 30));


    return this->Draw(target);
}

int Portal::Draw(sf::RenderWindow &target) {
    target.draw(*sprite_);
    return 0;
}

void Portal::Move(sf::Vector2f offset) {
    std::cout << __PRETTY_FUNCTION__ << ": " << Type_ << std::endl;
    sprite_->move(offset);
}

void Portal::Stop() {
    std::cout << __PRETTY_FUNCTION__ << ": " << this->GetPosition().x << " " << this->GetPosition().y << std::endl;
    if(MoveSide_ > 0)
        MoveSide_ = 0;
    SpeedX_   = 0;
    SpeedY_   = 0;
}

bool Portal::EventHendler(const sf::Event &event) {
    return false;
}

bool Portal::MouseHendler(const sf::Event &event, sf::Vector2f MousePos) {
    Target_.x = MousePos.x;
    Target_.y = MousePos.y;
    return false;
}

void Portal::SetMove(int MoveSide) {
    MoveSide_ = MoveSide;
}

void Portal::SetSpeed(float speedX, float speedY) {
    SpeedX_ = speedX;
    SpeedY_ = speedY;
}

//void Portal::SetTarget(sf::Vector2i mousePos) {
//    Target_ = mousePos;
//}

float Portal::GetSpeed() {
    return Speed_;
}

int Portal::GetMoveSide() {
    return this->MoveSide_;
}

bool Portal::PortalMove(sf::Vector2f offset, bool withElapsed, float ElapsedSec) {
    // Set clock for checking elapsed time
    static sf::Clock moveLeftClock;
    static sf::Clock moveRightClock;
    static sf::Clock moveUpClock;
    static sf::Clock moveDownClock;

    if(withElapsed) {

        if(offset.x > 0) {
            sf::Time elapsed = moveRightClock.getElapsedTime();

            if(elapsed.asSeconds() < ElapsedSec) {
                if(offset.y == 0)
                    return false;
                else
                    offset.x = 0;
            }
            else
                moveRightClock.restart();
        } else if(offset.x < 0) {
            sf::Time elapsed = moveLeftClock.getElapsedTime();

            if(elapsed.asSeconds() < ElapsedSec) {
                if(offset.y == 0)
                    return false;
                else
                    offset.x = 0;
            }
            else
                moveLeftClock.restart();
        }

        if(offset.y > 0) {
            sf::Time elapsed = moveDownClock.getElapsedTime();

            if(elapsed.asSeconds() < ElapsedSec) {
                if(offset.x == 0)
                    return false;
                else
                    offset.y = 0;
            }
            else
                moveDownClock.restart();
        } else if(offset.y < 0) {
            sf::Time elapsed = moveUpClock.getElapsedTime();

            if(elapsed.asSeconds() < ElapsedSec) {
                if(offset.x == 0)
                    return false;
                else
                    offset.y = 0;
            }
            else
                moveUpClock.restart();
        }

    }

    this->Move(offset);
    return true;
}

void Portal::SpriteMove(const sf::Vector2f &offset, bool withElapsed, float ElapsedSec) {
    this->PortalMove(offset, withElapsed, ElapsedSec);
}
