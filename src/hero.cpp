#include <iostream>

#include "common.h"
#include "hero.h"
#include "graphics.h"
#include "boundary.h"

const int HERO_HEIGHT = 59;
const int HERO_WIDTH  = 49;

const int JUMP_SPRITE_LEFT_OFFSET =  HERO_WIDTH * 5 + 30;

static sf::Clock JumpClock;

/// Constructors
Hero::Hero(sf::Texture *texture, sf::Sprite *sprite) :
    PhysElem(texture, sprite),
    defSpeedX_(200),
    defSpeedY_(300) {

    essential_ = true;

    block_ = false;

    lastMove_.x = 1;
    lastMove_.y = 1;

}

//Hero::Hero(sf::Texture* globalTexture) :
//    Speed_     (10),
//    inJumping_ (0),
//    portals_{new Portal(BLUE, globalTexture), new Portal(ORANGE, globalTexture)} {

//    MoveAbility_ = HERO;
//    block_  = false;

//    if(!texture_.loadFromFile("/home/artem/Main/Games/HeroRunSprite.png",
//                               sf::IntRect(0, 0, 1000, 1000)
//                               )) {
//        std::cerr << "Error while loading texture" << std::endl;
//    } else {
//        sprite_.setTexture     (texture_);
//        sprite_.setTextureRect (sf::IntRect(0, 0, 49, 63));
//    }
//}

//// Unused
//Hero::Hero(const GrElem &hero) :
//    texture_(dynamic_cast<const Hero &> (hero).texture_),
//    sprite_ (dynamic_cast<const Hero &> (hero).sprite_),
//    portals_{dynamic_cast<const Hero &> (hero).portals_[0], dynamic_cast<const Hero &> (hero).portals_[1]},
//    lastMove_(1, 1){}

//Hero::Hero(const sf::Vector2f& position) :
//    lastMove_(1, 1) {
//    if(!texture_.loadFromFile("/home/artem/Main/Games/HeroRunSprite.png",
//                               sf::IntRect(0, 0, 1000, 1000)
//                               )) {
//        std::cerr << "Error while loading texture" << std::endl;
//    }

//    sprite_.setTexture     (texture_);
//    sprite_.setTextureRect (sf::IntRect(0, 0, 49, 63));
//    this->SetPosition    (position);
//}

/// Destructor
Hero::~Hero() {
}

sf::Vector2f Hero::getLastMove() const {
    return lastMove_;
}

void Hero::setDefSpeedX(float speedX) {
    defSpeedX_ = speedX;
}

void Hero::setDefSpeedY(float speedY) {
    defSpeedY_ = speedY;
}

//Portal **Hero::GetPortals() {
//    return portals_;
//}

void Hero::Action() {

    PhysElem::Action();

    //std::cout << __PRETTY_FUNCTION__ << std::endl;
    //std::cout << "SpeedX = " << speedX_ << ", SpeedY = " << speedY_ << std::endl;
    //std::cout << "AccelX = " << accelX_ << ", AccelY = " << accelY_ << std::endl;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !block_.bot_) {
        std::cout << "S" << std::endl;

        this->Stop();
        speedX_ = 0;
    }

    if(sf::Keyboard::isKeyPressed (sf::Keyboard::W) && speedY_ == 0
            && accelY_ == 0 && block_.bot_ && !block_.top_) { // key pressed + no double jump + earth + can jump
        std::cout << "W" << std::endl;

        block_ = false;

        speedY_ = -defSpeedY_;

    }


    if(sf::Keyboard::isKeyPressed (sf::Keyboard::D) && !block_.right_ && (speedX_ >= 0 || speedY_ == 0)) {
        std::cout << "D" << std::endl;

        block_ = false;

        speedX_ = defSpeedX_;
    }

    if(sf::Keyboard::isKeyPressed (sf::Keyboard::A) && !block_.left_ && (speedX_ <= 0 || speedY_ == 0)) {
        std::cout << "A" << std::endl;

        block_ = false;

        speedX_ = -defSpeedX_;
    }

    if(block_.bot_
            && !sf::Keyboard::isKeyPressed (sf::Keyboard::A)
            && !sf::Keyboard::isKeyPressed (sf::Keyboard::D)
            && !sf::Keyboard::isKeyPressed (sf::Keyboard::W)) {
        this->Stop();
        speedX_ = 0;
    }

}

sf::Vector2i Hero::Move() {
    static float moveCounterX;
    static float moveCounterY;


    sf::Vector2i offset = PhysElem::Move();

    if(speedX_ == 0 && speedY_ == 0)
        this->Stop();

    if(offset.x != 0)
        moveCounterX++;
    else
        moveCounterX = 0;

    if(offset.y != 0)
        moveCounterY++;
    else
        moveCounterY = 0;

    //std::cout << __PRETTY_FUNCTION__ << std::endl;
    //std::cout << "Offset, move counters" << offset.x << " " << moveCounterX << ", " << offset.y << " " << moveCounterY << std::endl;

    if((offset.x == 0 || moveCounterX < 1000 / std::abs(speedX_)) && (offset.y == 0 || moveCounterY < 1000 / std::abs(speedY_))) {
        offset.x = 0;
        offset.y = 0;
        return offset;
    }

    if(moveCounterX >= 1000 / std::abs(speedX_)) {
        moveCounterX -= 1000 / std::abs(speedX_);
    }
    else {
        offset.x = 0;
    }

    if(moveCounterY >= 1000 / std::abs(speedY_)) {
        moveCounterY -= 1000 / std::abs(speedY_);
    }
    else {
        offset.y = 0;
    }



    // Select next texture rectangle (move sprite)
    int left = 0;

    if(offset.y < 0) {
        //std::cout << "Move up" << std::endl;

        if(offset.x < 0 || (offset.x == 0 && lastMove_.x < 0))
            left = texture_->getSize().x - HERO_WIDTH - JUMP_SPRITE_LEFT_OFFSET;
        else
            left = JUMP_SPRITE_LEFT_OFFSET;

        sprite_->setTextureRect(sf::IntRect(left, 63 * (left != 5 * HERO_WIDTH + 30), HERO_WIDTH, HERO_HEIGHT));

        block_.bot_ = false; // unnecessary?

        //return offset;
    }
    else if(offset.y > 0 && speedX_ == 0) {
        this->Stop();
    }

    if(offset.x != 0) {
        // Get number of current area in texture
        int CurrAreaNum;
        if(sprite_->getTextureRect().top == 0) {
            CurrAreaNum  = sprite_->getTextureRect().left / HERO_WIDTH;
            CurrAreaNum -= (CurrAreaNum > 7);
            CurrAreaNum += (CurrAreaNum < 2);
        }
        else {
            CurrAreaNum  = (texture_->getSize().x - sprite_->getTextureRect().left) / HERO_WIDTH - 1;
            CurrAreaNum -= (CurrAreaNum > 7);
            CurrAreaNum += (CurrAreaNum < 2);
        }
//        int left = (
//                    CurrAreaNum * 49 +
//                    (CurrAreaNum >= 4) * 30 + (CurrAreaNum >= 6) * 10 + (CurrAreaNum >= 7) * 10 + (CurrAreaNum >= 8) * 15 + (CurrAreaNum >= 9) * 15
//                    ) % (49*10 + 90);
        int left;
        if(CurrAreaNum != 9) {
            left = (CurrAreaNum + 1) * HERO_WIDTH;
            switch (CurrAreaNum + 1) {
            case 1:
            case 2:
            case 3:
                left = 4 * HERO_WIDTH + 20;
                break;
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

        if(lastMove_.x < 0 && offset.x > 0) {
            left = 0;
        }

        if(offset.x < 0) {
            if(lastMove_.x > 0)
                left = texture_->getSize().x - HERO_WIDTH;
            else
                left = texture_->getSize().x - HERO_WIDTH - left;
        }

        // Move sprite
        sprite_->setTextureRect(sf::IntRect(left, 63 * (offset.x < 0), HERO_WIDTH, HERO_HEIGHT));

        // Remember movement
        if(offset.x > 0)
            lastMove_.x = 1;

        else if(offset.x < 0)
            lastMove_.x = -1;

    }

    return offset;

}

void Hero::Intersect(GrElem &elem, sf::Vector2u windowSize) {
    if(dynamic_cast<Boundary*>(&elem) != nullptr) {
        int side = getPushSide(*this, elem, windowSize);
        pushToSide(*this, elem, side);
        if(side == UP) {
            if(speedX_ > 0 && speedX_ != defSpeedX_)
                speedX_ = defSpeedX_;

            if(speedX_ < 0 && speedX_ != -defSpeedX_)
                speedX_ = -defSpeedX_;
        }
    }
}

// Stop hero
void Hero::Stop() {
    //std::cout << "Stop" << std::endl;
    // Set sprite stay area
    int left = 0;
    int top  = 0;

    // If she run into another side
    if(lastMove_.x < 0) {
        left = texture_->getSize().x - HERO_WIDTH;
        top = 63;
    }

    sprite_->setTextureRect(sf::IntRect(left, top, HERO_WIDTH, HERO_HEIGHT));
}

void Hero::eventHendler(const sf::Event &event, const sf::Vector2f &mousePos) {
    switch (event.type) {
//    case sf::Event::KeyPressed:
//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !block_.bot_) {
//            std::cout << "S" << std::endl;

//            this->Stop();
//            speedX_ = 0;
//        }

//        if(sf::Keyboard::isKeyPressed (sf::Keyboard::W) && speedY_ == 0
//                && accelY_ == 0 && block_.bot_ && !block_.top_) { // key pressed + no double jump + earth + can jump
//            std::cout << "W" << std::endl;

//            block_ = false;

//            speedY_ = -defSpeedY_;

//        }


//        if(sf::Keyboard::isKeyPressed (sf::Keyboard::D) && !block_.right_) {
//            std::cout << "D" << std::endl;

//            block_ = false;

//            speedX_ = defSpeedX_;
//        }

//        if(sf::Keyboard::isKeyPressed (sf::Keyboard::A) && !block_.left_) {
//            std::cout << "A" << std::endl;

//            block_ = false;

//            speedX_ = -defSpeedX_;
//        }

//        break;
    case sf::Event::KeyReleased:
        if(event.key.code == sf::Keyboard::A && speedX_ < 0) {
            this->Stop();
            speedX_ = 0;
        }
        else if(event.key.code == sf::Keyboard::D && speedX_ > 0) {
            this->Stop();
            speedX_ = 0;
        }
        break;
    default:
        break;
    }
}


///                                                      !!!!!FOR PORTALS!!!!!
//bool Hero::MouseHendler(const sf::Event &event, sf::Vector2f MousePos) {
//    int PortNum = -1;
//    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
//        PortNum = 0;
//    else if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
//        PortNum = 1;
//    else
//        return false;

//    std::cout << "PORT NUM: " << PortNum << std::endl;

//    portals_[PortNum]->SetMove(1);
//    if(portals_[!PortNum]->GetMoveSide() > 0)
//        portals_[!PortNum]->SetMove(-1);

//    for(int i = 0; i < 2; i++)
//        if(portals_[i]->GetMoveSide() != 0)
//            portals_[i]->SetPosition(sf::Vector2f(
//                                         this->GetPosition().x + this->GetGlobalBounds().width / 2,
//                                         this->GetPosition().y + this->GetGlobalBounds().height / 3 - 5)
//                                     );

//    for(int i = 0; i < 2; i++)
//        portals_[i]->SetSpeed(0, 0);
//    return false;
//}

//bool Hero::KeyPressedHandler(const sf::Event& event) {
//    if(event.type != sf::Event::KeyPressed)
//        return false;

//    if(event.key.code == sf::Keyboard::W)
//        std::cout << "W" << std::endl;
//    if(event.key.code == sf::Keyboard::S)
//        std::cout << "S" << std::endl;
//    if(event.key.code == sf::Keyboard::A)
//        std::cout << "A" << std::endl;
//    if(event.key.code == sf::Keyboard::D)
//        std::cout << "D" << std::endl;

//    bool catched = false;


//    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !block_.right_) {
//        std::cout << "D" << std::endl;
//        block_ = false;
//        this->SpriteMove(sf::Vector2f(Speed_, 0), false);
//        catched = true;
//    }

//    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !block_.left_) {
//        std::cout << "A" << std::endl;
//        block_ = false;
//        this->SpriteMove(sf::Vector2f(-Speed_, 0), false);
//        catched = true;
//    }

//    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && inJumping_ == 0 && block_.bot_ && !block_.top_) { // key pressed + no double jump + earth + can jump
//        JumpClock.restart();
//        block_ = false;
//        inJumping_ = 1;
//        //this->SpriteMove(sf::Vector2f(0, -Speed_), false);
//        catched = true;
//    }

//    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !block_.bot_) {
//        block_ = false;
//        this->SpriteMove(sf::Vector2f(0, Speed_), false);
//        catched = true;
//    }


//    return catched;
//}

///                              !!!!FOR PORTALS!!!!!-------------------------------------------------------------------------------
//void Hero::MousePressedHendler() {
//    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
//        portals_[0]->SetPosition(sf::Vector2f(
//                                     this->GetPosition().x + this->GetGlobalBounds().width / 2,
//                                     this->GetPosition().y + this->GetGlobalBounds().height / 3 - 5)
//                                );
//        portals_[0]->SetMove(1);

//        portals_[0]->SetSpeed(0, 0);

//        //portals_[0]->SetTarget(sf::Mouse::getPosition());

////        sf::Vector2i mousePos = sf::Mouse::getPosition();

////        float speedX = mousePos.x - this->GetPosition().x + this->GetGlobalBounds().width / 2;
////        float speedY = mousePos.y - this->GetPosition().y + this->GetGlobalBounds().height / 3 - 5;

////        float Sum = speedX + speedY;

////        // Normalize * speed
////        speedX = (speedX / Sum) * portals_[0]->GetSpeed();
////        speedY = (speedY / Sum) * portals_[0]->GetSpeed();

////        portals_[0]->SetSpeed(speedX, speedY);
//    }
//}

/// When move key not pressed, stop the hero (set proper sprite)
//bool Hero::KeyNotPressedHandler (const sf::Event& event) {
//    if(inJumping_ == 0)
//        this->SpriteStop();
//    return false;
//}

/// Set hero position
//void Hero::SetPosition (const sf::Vector2f &position) {
//    std::cout << __PRETTY_FUNCTION__ << ": " << position.x << " " << position.y << std::endl;
//    sprite_.setPosition(position);
//    block_ = false;

//    //portals_[0]->SetMove(-1);
//    //portals_[1]->SetMove(-1);

//    portals_[0]->SetSpeed(0, 0);
//    portals_[1]->SetSpeed(0, 0);

//    std::cout << __PRETTY_FUNCTION__ << ": " << position.x << " " << position.y << std::endl;
////    portals_[0]->SetPosition(position);
////    portals_[1]->SetPosition(position);
//}

///// Get hero position
//sf::Vector2f Hero::GetPosition() const {
//    return sprite_.getPosition();
//}

///// Get sprite bounds for intersection
//sf::FloatRect Hero::GetGlobalBounds() const {
//    return sprite_.getGlobalBounds();
//}

/// Make some actions
//void Hero::Actions() {
//    //static sf::Clock ActClock;
//    //std::cout << inJumping_ << std::endl;

//    //this->MousePressedHendler();


//    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !block_.right_) {
//        std::cout << "D" << std::endl;
//        block_ = false;

//        if(!inJumping_)
//            this->SpriteMove(sf::Vector2f(Speed_, 0), true, 0.05);
//        else
//            this->HeroMove(sf::Vector2f(Speed_, 0), true, 0.05);

//    }

//    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !block_.left_) {
//        std::cout << "A" << std::endl;
//        block_ = false;

//        if(!inJumping_)
//            this->SpriteMove(sf::Vector2f(-Speed_, 0), true, 0.05);
//        else
//            this->HeroMove(sf::Vector2f(-Speed_, 0), true, 0.05);

//    }

//    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && inJumping_ == 0 && block_.bot_ && !block_.top_) { // key pressed + no double jump + earth + can jump
//        std::cout << "W" << std::endl;
//        JumpClock.restart();
//        block_ = false;
//        inJumping_ = 1;
//        //this->SpriteMove(sf::Vector2f(0, -Speed_), false);
//    }

//    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !block_.bot_) {
//        std::cout << "S" << std::endl;
//        block_ = false;

//        if(inJumping_)
//            inJumping_ = 0;

//        this->SpriteMove(sf::Vector2f(0, Speed_), true, 0.05);
//    }

//    if(inJumping_ > 0) {
//        if(JumpClock.getElapsedTime().asSeconds() > 0.5) {
//            inJumping_--;
//            JumpClock.restart();
//        }
//        if(inJumping_ > 0) {// catch moment of the higher position
//            std::cout << "Jumping" << std::endl;
//            this->SpriteMove(sf::Vector2f(0, -2 * Speed_));
//        }
//        else {
//            this->SpriteStop();
//            block_.bot_ = false;
//        }
//    }
//    else if(!block_.bot_) {
//        std::cout << "Falling" << std::endl;
//        block_.left_  = false;
//        block_.top_   = false;
//        block_.right_ = false;
//        this->HeroMove(sf::Vector2f(0, 2 * Speed_));
//    }

//    portals_[0]->Actions();
//    portals_[1]->Actions();

//    if(portals_[0]->GetGlobalBounds().intersects(this->GetGlobalBounds()))
//        if(portals_[0]->GetMoveSide() == 0 && portals_[1]->GetMoveSide() == 0) {
//            this->SetPosition(portals_[1]->GetPosition());
//            std::cout << __PRETTY_FUNCTION__ << ": portal move, new pos:"
//                      << this->GetPosition().x << " " << this->GetPosition().x << std::endl;
//        }
//}

///// Update hero
//int Hero::Update (sf::RenderWindow &target) {
//    //portals_[0]->Update(target);
//    //portals_[1]->Update(target);
//    return this->Draw(target);
//}

///// Draw hero sprite
//int Hero::Draw (sf::RenderWindow &target) {
//    target.draw(sprite_);
//    return 0;
//}

/// Default hero move (without moving sprite)
//void Hero::Move(sf::Vector2f offset) {
//    if(offset.x > 0 && block_.right_)
//        offset.x = 0;
//    if(offset.x < 0 && block_.left_)
//        offset.x = 0;
//    if(offset.y > 0 && block_.bot_)
//        offset.y = 0;
//    if(offset.y < 0 && block_.top_)
//        offset.y = 0;

//    sprite_.move(offset);
//}

///// Special hero movement
//bool Hero::HeroMove(sf::Vector2f offset, bool withElapsed, float ElapsedSec) {
//    // Set clock for checking elapsed time
//    static sf::Clock moveLeftClock;
//    static sf::Clock moveRightClock;
//    static sf::Clock moveUpClock;
//    static sf::Clock moveDownClock;

//    if(withElapsed) {

//        if(offset.x > 0) {
//            sf::Time elapsed = moveRightClock.getElapsedTime();

//            if(elapsed.asSeconds() < ElapsedSec) {
//                if(offset.y == 0)
//                    return false;
//                else
//                    offset.x = 0;
//            }
//            else
//                moveRightClock.restart();
//        } else if(offset.x < 0) {
//            sf::Time elapsed = moveLeftClock.getElapsedTime();

//            if(elapsed.asSeconds() < ElapsedSec) {
//                if(offset.y == 0)
//                    return false;
//                else
//                    offset.x = 0;
//            }
//            else
//                moveLeftClock.restart();
//        }

//        if(offset.y > 0) {
//            sf::Time elapsed = moveDownClock.getElapsedTime();

//            if(elapsed.asSeconds() < ElapsedSec) {
//                if(offset.x == 0)
//                    return false;
//                else
//                    offset.y = 0;
//            }
//            else
//                moveDownClock.restart();
//        } else if(offset.y < 0) {
//            sf::Time elapsed = moveUpClock.getElapsedTime();

//            if(elapsed.asSeconds() < ElapsedSec) {
//                if(offset.x == 0)
//                    return false;
//                else
//                    offset.y = 0;
//            }
//            else
//                moveUpClock.restart();
//        }

//    }

//    this->Move(offset);
//    return true;
//}

/// Move hero, move his sprite
//void Hero::SpriteMove(const sf::Vector2f& offset, bool withElapsed, float ElapsedSec) { // TODO: Разбить по функциям!!!
//    // Set clock for checking elapsed time

//    if(!this->HeroMove(offset, withElapsed, ElapsedSec))
//        return;

////    if(offset.x > 0 && block_.right_)
////        offset.x = 0;
////    if(offset.x < 0 && block_.left_)
////        offset.x = 0;
////    if(offset.y > 0 && block_.bot_)
////        offset.y = 0;
////    if(offset.y < 0 && block_.top_)
////        offset.y = 0;

////    // Move hero
////    sprite_.move(offset);

//    if(offset.x != 0 || offset.y != 0)
//        block_ = false;
//    else
//        return;

//    // Select next texture rectangle (move sprite)
//    if(offset.y < 0) {
//        std::cout << "Move up" << std::endl;
//        if(!block_.top_) {
//            int left;

//            if(offset.x < 0 || (offset.x == 0 && lastMove_.x < 0))
//                left = texture_.getSize().x - 49 - JUMP_SPRITE_LEFT_OFFSET;
//            else
//                left = JUMP_SPRITE_LEFT_OFFSET;

//            sprite_.setTextureRect(sf::IntRect(left, 63 * (left != 5 * 49 + 30), 49, 63));
//        }
//        else {
//            inJumping_ = 0;
//        }
//        block_.bot_ = false;
//    }

//    if(offset.x != 0) {
//        // Get number of current area in texture
//        int CurrAreaNum;
//        if(sprite_.getTextureRect().top == 0) {
//            CurrAreaNum  = sprite_.getTextureRect().left / 49;
//            CurrAreaNum -= (CurrAreaNum > 7);
//            CurrAreaNum += (CurrAreaNum < 2);
//        }
//        else {
//            CurrAreaNum  = (texture_.getSize().x - sprite_.getTextureRect().left) / 49 - 1;
//            CurrAreaNum -= (CurrAreaNum > 7);
//            CurrAreaNum += (CurrAreaNum < 2);
//        }
////        int left = (
////                    CurrAreaNum * 49 +
////                    (CurrAreaNum >= 4) * 30 + (CurrAreaNum >= 6) * 10 + (CurrAreaNum >= 7) * 10 + (CurrAreaNum >= 8) * 15 + (CurrAreaNum >= 9) * 15
////                    ) % (49*10 + 90);
//        int left;
//        if(CurrAreaNum != 9) {
//            left = (CurrAreaNum + 1) * 49;
//            switch (CurrAreaNum + 1) {
//            case 4:
//                left += 20;
//                break;
//            case 5:
//                left += 30;
//                break;
//            case 6:
//                left += 40;
//                break;
//            case 7:
//                left += 50;
//                break;
//            case 8:
//                left += 75;
//                break;
//            case 9:
//                left += 90;
//                break;
//            }
//        }
//        else {
//            left = 49*3;
//        }

//        if(lastMove_.x < 0 && offset.x > 0)
//            left = 0;

//        if(offset.x < 0) {
//            if(lastMove_.x > 0)
//                left = texture_.getSize().x - 49;
//            else
//                left = texture_.getSize().x - 49 - left;
//        }

//        // Move sprite
//        sprite_.setTextureRect(sf::IntRect(left, 63 * (offset.x < 0), 49, 63));

//        // Remember movement
//        if(offset.x > 0)
//            lastMove_.x = 1;
//        else if(offset.x < 0)
//            lastMove_.x = -1;

//    }


//}

//void Hero::SpriteStop() {
//    std::cout << "Stop" << std::endl;
//    // Set sprite stay area
//    int left = 0;
//    int top  = 0;

//    // If she run into another side
//    if(lastMove_.x < 0) {
//        left = texture_.getSize().x - 49;
//        top = 63;
//    }

//    sprite_.setTextureRect(sf::IntRect(left, top, 49, 63));
//}
