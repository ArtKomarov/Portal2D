#include <iostream>

#include <SFML/Audio.hpp>

#include "portal.h"
#include "boundary.h"

//Portal::Portal(int type, sf::Texture* texture) :
//    Type_(type),
//    MoveSide_(-1),
//    Speed_(70),
//    SpeedX_(0),
//    SpeedY_(0),
//    texture_(texture),
//    sprite_(new sf::Sprite(*texture)) {

//    this->SetPosition(sf::Vector2f(500, 500));
//    MoveAbility_ = PORTAL;
//}

const char BLUE_AUDIO_PATH[] = "Sound/BlueFire.wav";
const char ORANGE_AUDIO_PATH[] = "Sound/OrangeFire.wav";

Portal::Portal(int type, sf::Texture* texture, sf::Sprite* sprite, Hero *hero) :
    PhysElem(texture, sprite),
    Type_        (type),
    portSide_    (0),
    hero_        (hero),
    State_       (-1),
    defSpeed_    (1000) {
//    Target_(sf::Vector2f(-1, -1)) {
    NotExistRect_ = sf::IntRect(190, 27, 10, 30);
    StayRect_     = sf::IntRect(160, 27 + 38 * (Type_ == ORANGE), 10, 30);
    MoveRect_     = sf::IntRect(185, 27 + 38 * (Type_ == ORANGE), 10, 30);

    block_ = false;

    this->setPosition(sf::Vector2f(0, 0));

    char* audioPath = nullptr;

    if(Type_ == BLUE) {
        audioPath = const_cast<char*>(BLUE_AUDIO_PATH);
    }
    else {
        audioPath = const_cast<char*>(ORANGE_AUDIO_PATH);
    }

    soundBuff_.loadFromFile(audioPath);

    fireSound_.setBuffer(soundBuff_);
}

void Portal::setPortal2(Portal *portal2) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    if(portal2->hero_ != hero_ || portal2->Type_ == Type_)
        std::cerr << "Error: This portals have no proper effect! Portals hero equals bit: "
                  << (port2_->hero_ == hero_) << ", different portals types bit: "
                  << (port2_->Type_ == Type_) << std::endl;

    port2_ = portal2;
}

int Portal::getPortSide() const {
    return portSide_;
}

void Portal::Action() {
    accelX_ = 0;
    accelY_ = 0;
    if(State_ <= 0) {
        speedX_ = 0;
        speedY_ = 0;
    }

    switch (State_) {
    case NOTCARYY:
        if(!hero_->getGlobalBounds().intersects(this->getGlobalBounds()))
            State_ = STAY;
        sprite_->setTextureRect(StayRect_);
        break;
    case STAY:
        sprite_->setTextureRect(StayRect_);
        break;
    case NOTEXIST:
        sprite_->setTextureRect(NotExistRect_);
        break;
    case MOVE:
        sprite_->setTextureRect(MoveRect_);
        break;
    default:
        sprite_->setTextureRect(NotExistRect_);
        break;
    }

    if(State_ == MOVE)
        block_ = false;

}

sf::FloatRect Portal::getGlobalBounds() const {
    if(State_ == MOVE) {
        return sf::FloatRect(
                    sprite_->getGlobalBounds().left,
                    sprite_->getGlobalBounds().top + 8,
                    sprite_->getGlobalBounds().width,
                    sprite_->getGlobalBounds().height - 16
                    );
    }
    else
    return sprite_->getGlobalBounds();
}


void Portal::eventHendler(const sf::Event &event, const sf::Vector2f& mousePos) {
    if(event.type == sf::Event::MouseButtonPressed) {
        if((port2_->State_ != MOVE) &&
                ((sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && Type_ == BLUE)
                || (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && Type_ == ORANGE))) {


            float NewPosX = hero_->getPosition().x + hero_->getGlobalBounds().width / 2;
            float NewPosY = hero_->getPosition().y + 1 * hero_->getGlobalBounds().height / 3 - 2;

            float speedX = mousePos.x - NewPosX - this->getGlobalBounds().width / 2;

            float speedY = mousePos.y - NewPosY - this->getGlobalBounds().height / 2;

            sf::Vector2f lastMove = hero_->getLastMove();

            if(speedX * lastMove.x < 0)
                return;

//            if(speedX * lastMove.x < 0) {
//                sf::Vector2f heroSpeed = hero_->getSpeed();

//                hero_->setSpeedX(speedX / std::abs(speedX));
//                hero_->setSpeedY(0);

//                hero_->Move();

//                hero_->setSpeedX(heroSpeed.x);
//                hero_->setSpeedY(heroSpeed.y);
//            }

            //if(State_ == STAY)
            //    sprite_->move(sf::Vector2f(0, -(StayRect_.height - MoveRect_.height) / 2));

            State_    = MOVE;
            portSide_ = STAY;

            fireSound_.play();

            this->setPosition(sf::Vector2f(NewPosX, NewPosY));

            sprite_->setTextureRect(MoveRect_);

            float Sum = std::abs(speedX) + std::abs(speedY);

            // Normalize * speed
            speedX_ = (speedX / Sum) * defSpeed_;
            speedY_ = (speedY / Sum) * defSpeed_;
        }
    }



}



void Portal::Intersect(GrElem &elem, sf::Vector2u windowSize) {
    switch(State_) {
    case MOVE: {
        Boundary* b = nullptr;
        IF_CLASS(Boundary, b, elem) {
            if(b->getType() == WHITE_BOUNDARY) {

                //float LDist, RDist, TDist, BDist;

                //this->getDistances(elem, windowSize, LDist, RDist, TDist, BDist);

                //int MoveSide = 0;

                //if(     TDist <= LDist && TDist <= RDist && TDist <= BDist)
                //    MoveSide = UP;
                //else if(RDist <= LDist && RDist <= TDist && RDist <= BDist)
                //    MoveSide = RIGHT;
                //else if(LDist <= RDist && LDist <= TDist && LDist <= BDist)
                //    MoveSide = LEFT;
                //else if(BDist <= LDist && BDist <= RDist && BDist <= TDist)
                //    MoveSide = DOWN;

                portSide_ = getPushSide(*this, elem, windowSize);

                State_ = STAY;
            }
            else {
                State_ = NOTEXIST;
                sprite_->setTextureRect(NotExistRect_);
            }

            speedX_ = 0;
            speedY_ = 0;

            accelX_ = 0;
            speedY_ = 0;


            pushOff(*this, elem, windowSize);

            //sprite_->move(sf::Vector2f(0, (StayRect_.height - MoveRect_.height) / 2));

        }
        else {
            Hero* hero = nullptr;
            IF_CLASS(Hero, hero, elem) {
            }
            else {
                PhysElem* pe = nullptr;
                IF_CLASS(PhysElem, pe, elem) {
                    State_ = NOTEXIST;

                    speedX_ = 0;
                    speedY_ = 0;

                    accelX_ = 0;
                    speedY_ = 0;
                }
            }
        }
        break;
    }
    case STAY: {
        Hero* hero;
        IF_CLASS(Hero, hero, elem) {
            if(port2_->State_ == STAY && static_cast<GrElem*>(hero_) == &elem) {
                sf::Vector2f newPosition(port2_->getGlobalBounds().left + port2_->getGlobalBounds().width / 2 - hero_->getGlobalBounds().width / 2,
                                         port2_->getGlobalBounds().top + port2_->getGlobalBounds().height / 2 - hero_->getGlobalBounds().height / 2);
                switch (port2_->portSide_) {
                case LEFT:
                    newPosition.x = port2_->getPosition().x - (hero_->getGlobalBounds().width - port2_->getGlobalBounds().width);
                    break;
                case RIGHT:
                    newPosition.x = port2_->getPosition().x;
                    break;
                case UP:
                    newPosition.y = port2_->getPosition().y - (hero_->getGlobalBounds().height - port2_->getGlobalBounds().height);
                    break;
                case DOWN:
                    newPosition.y = port2_->getPosition().y;
                default:
                    break;
                }

                //hero_->setPosition(sf::Vector2f(port2_->getGlobalBounds().left + port2_->getGlobalBounds().width / 2 - hero_->getGlobalBounds().width / 2,
                //                              port2_->getGlobalBounds().top + port2_->getGlobalBounds().height / 2 - hero_->getGlobalBounds().height / 2));

                hero_->setPosition(newPosition);

                hero_->setAccelX(0);
                hero_->setAccelY(0);

                float enterSpeed;
                if(portSide_ == LEFT || portSide_ == RIGHT)
                    enterSpeed = std::abs(hero_->getSpeed().x);
                else
                    enterSpeed = std::abs(hero_->getSpeed().y);

                hero_->setSpeedX(0);
                hero_->setSpeedY(0);

                switch (port2_->portSide_) {
                case LEFT:
                    hero_->setSpeedX(-enterSpeed);
                    break;
                case RIGHT:
                    hero_->setSpeedX(enterSpeed);
                    break;
                case UP:
                    hero_->setSpeedY(-enterSpeed);
                    break;
                case DOWN:
                    hero_->setSpeedY(enterSpeed);
                    break;
                default:
                    break;
                }


                port2_->State_ = NOTCARYY;
            }
        }
        else {
            Boundary* b = nullptr;
            IF_CLASS(Boundary, b, elem) {
                PhysElem::Intersect(elem, windowSize);
            }
        }
        break;

    }
    }
}

//void Portal::SetPosition(const sf::Vector2f &position) {
//    std::cout << __PRETTY_FUNCTION__ << ": " << position.x << " " << position.y << std::endl;
//    sprite_->setPosition(position);
//}

//sf::Vector2f Portal::GetPosition() const {
//    return sprite_->getPosition();
//}




//void Portal::Actions() {
//    if(MoveSide_ > 0)
//        this->PortalMove(sf::Vector2f(SpeedX_, SpeedY_));
////    switch (MoveSide_) {
////    case -1:
////        break;
////    case 0:
////        break;
////    case LEFT:
////        this->PortalMove(sf::Vector2f(-Speed_, 0));
////        break;
////    case RIGHT:
////        this->PortalMove(sf::Vector2f(Speed_, 0));
////        break;
////    case UP:
////        this->PortalMove(sf::Vector2f(Speed_, -1));
////        break;
////    case DOWN:
////        this->PortalMove(sf::Vector2f(Speed_, 1));
////        break;
////    default:
////        break;
////    }
//}

//int Portal::Update(sf::RenderWindow &target) {

//    if(MoveSide_ > 0)
//        block_ = false;

//    if(SpeedX_ == 0 && SpeedY_ == 0 && MoveSide_ > 0) {

//        float speedX = Target_.x - this->GetPosition().x - this->GetGlobalBounds().width / 2; //+ target.mapPixelToCoords(target.getPosition()).x; // BAD POSITION!!! BAG!
//        float speedY = Target_.y - this->GetPosition().y - this->GetGlobalBounds().height / 2; //+ target.mapPixelToCoords(target.getPosition()).y;

//        std::cout << "window: " << target.mapPixelToCoords(target.getPosition()).x << " " << target.mapPixelToCoords(target.getPosition()).y << std::endl;
//        std::cout << "target: " << Target_.x << " " << Target_.y << std::endl;
//        std::cout << "Portal pos: " << this->GetPosition().x << " " << this->GetPosition().y << std::endl;

//        float Sum = std::abs(speedX) + std::abs(speedY);

//        // Normalize * speed
//        speedX = (speedX / Sum) * this->GetSpeed();
//        speedY = (speedY / Sum) * this->GetSpeed();

//        this->SetSpeed(speedX, speedY);
//    }


//    if(MoveSide_ > 0)
//        sprite_->setTextureRect(sf::IntRect(185, 27 + 38 * (Type_ == ORANGE), 10, 30));
//    else if(MoveSide_ == 0)
//        sprite_->setTextureRect(sf::IntRect(160, 27 + 38 * (Type_ == ORANGE), 10, 30));
//    else
//        sprite_->setTextureRect(sf::IntRect(190, 27, 10, 30));


//    return this->Draw(target);
//}

//int Portal::Draw(sf::RenderWindow &target) {
//    target.draw(*sprite_);
//    return 0;
//}

//void Portal::Move(sf::Vector2f offset) {
//    std::cout << __PRETTY_FUNCTION__ << ": " << Type_ << std::endl;
//    sprite_->move(offset);
//}

//void Portal::Stop() {
//    std::cout << __PRETTY_FUNCTION__ << ": " << this->GetPosition().x << " " << this->GetPosition().y << std::endl;
//    if(MoveSide_ > 0)
//        MoveSide_ = 0;
//    SpeedX_   = 0;
//    SpeedY_   = 0;
//}

//bool Portal::MouseHendler(const sf::Event &event, sf::Vector2f MousePos) {
//    Target_.x = MousePos.x;
//    Target_.y = MousePos.y;
//    return false;
//}

//void Portal::SetMove(int MoveSide) {
//    MoveSide_ = MoveSide;
//}

//void Portal::SetSpeed(float speedX, float speedY) {
//    SpeedX_ = speedX;
//    SpeedY_ = speedY;
//}

//void Portal::SetTarget(sf::Vector2i mousePos) {
//    Target_ = mousePos;
//}

//float Portal::GetSpeed() {
//    return Speed_;
//}

//int Portal::GetMoveSide() {
//    return this->MoveSide_;
//}

//bool Portal::PortalMove(sf::Vector2f offset, bool withElapsed, float ElapsedSec) {
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

//void Portal::SpriteMove(const sf::Vector2f &offset, bool withElapsed, float ElapsedSec) {
//    this->PortalMove(offset, withElapsed, ElapsedSec);
//}
