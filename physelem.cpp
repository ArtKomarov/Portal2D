#include <iostream>
#include <limits>

#include "physelem.h"

//------------------ Define support class -------------------//
/*
 * Shows, what sides of physical element are blocked.
 * Element can't move to the blocked side
*/
Blocked::Blocked () :
    left_  (false),
    right_ (false),
    top_   (false),
    bot_   (false) {}

Blocked &Blocked::operator = (bool state) {
    left_  = state;
    right_ = state;
    top_   = state;
    bot_   = state;
    return *this;
}

bool Blocked::operator == (bool state) {
    return ((left_ == state) && (right_ == state)
            && (top_ == state) && (bot_ == state));
}

//-------------------------------------------------------------//

//PhysElem::PhysElem() :
//    PhysElem(nullptr, nullptr) {
//}

PhysElem::PhysElem (sf::Texture *texture, sf::Sprite *sprite) :
    GrElem(texture, sprite),
    block_(),
    speedX_(0),
    speedY_(0),
    accelX_(0),
    accelY_(0) {

    //this->Move(sf::Vector2f(0, 0));
}

PhysElem::~PhysElem() {

}

void PhysElem::setBlock(bool state, int side) {
    switch (side) {
    case LEFT:
        block_.left_ = state;
        break;
    case RIGHT:
        block_.right_ = state;
        break;
    case UP:
        block_.top_ = state;
        break;
    case DOWN:
        block_.bot_ = state;
        break;
    default:
        block_ = state;
        break;
    }
}


//--------------------------Work with speed--------------------------------//
// Setters
void PhysElem::setSpeedX(float speedX) {
    speedX_ = speedX;
}

void PhysElem::setSpeedY(float speedY) {
    speedY_ = speedY;
}

void PhysElem::clockRestart() {
    moveClockX_.restart();
    moveClockY_.restart();

    accelClockX_.restart();
    accelClockY_.restart();
}

void PhysElem::setAccelX(float accelX) {
    accelX_ = accelX;
}

void PhysElem::setAccelY(float accelY) {
    accelY_ = accelY;
}

void PhysElem::incrAccelX(float accelOffset) {
    accelX_ += accelOffset;
}

void PhysElem::incrAccelY(float accelOffset) {
    accelY_ += accelOffset;
}

// Increase the value
void PhysElem::incrSpeedX(float speedOffset) {
    speedX_ += speedOffset;
}

void PhysElem::incrSpeedY(float speedOffset) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    speedY_ += speedOffset;
}

//-------------------------------------------------------------------------//

bool PhysElem::getBlock(int side) {
    switch (side) {
    case LEFT:
        return block_.left_;
        break;
    case RIGHT:
        return block_.right_;
        break;
    case UP:
        return block_.top_;
        break;
    case DOWN:
        return block_.bot_;
        break;
    default:
        std::cerr << __PRETTY_FUNCTION__ << ": Unknown side!" << std::endl;
    }
    return true;
}

//void PhysElem::Intersect(GrElem &elem, sf::Vector2u windowSize) {
//    std::cout << "Move apart:\nPositions:  "
//              << this->getPosition().x << ", " << this->getPosition().y << "; "
//              << elem.getPosition().x << ", " << elem.getPosition().y << std::endl;

//    float LDist, RDist, TDist, BDist;

//    getDistances(elem, windowSize, LDist, RDist, TDist, BDist);

//    float offsetX = 0;
//    float offsetY = 0;

//    std::cout << "LDist = " << LDist << " RDist = " << RDist << " TDist = " << TDist << " BDist = " << BDist << std::endl;

//    // In case of all blacked element, move up
//    if(     TDist <= LDist && TDist <= RDist && TDist <= BDist)
//        offsetY = -1;
//    else if(RDist <= LDist && RDist <= TDist && RDist <= BDist)
//        offsetX = 1;
//    else if(LDist <= RDist && LDist <= TDist && LDist <= BDist)
//        offsetX = -1;
//    else if(BDist <= LDist && BDist <= RDist && BDist <= TDist)
//        offsetY = 1;
//    else {
//        std::cerr << __PRETTY_FUNCTION__ << ": I do not know what happened!!!" << std::endl;
//        exit(0);
//    }

//    while (this->getGlobalBounds().intersects(elem.getGlobalBounds())) {
//        //std::cout << "Intersect!" << std::endl;
//        this->mustMove(sf::Vector2f(offsetX, offsetY));
//    }

//    if(offsetX > 0)
//        block_.left_  = true;

//    if(offsetX < 0)
//        block_.right_ = true;

//    if(offsetY > 0)
//        block_.top_   = true;

//    if(offsetY < 0)
//        block_.bot_   = true;

//    //this->Stop();

//}

void pushOff(PhysElem &this_elem, GrElem &elem, sf::Vector2u windowSize) {
    std::cout << "Move apart:\nPositions:  "
              << this_elem.getPosition().x << ", " << this_elem.getPosition().y << "; "
              << elem.getPosition().x << ", " << elem.getPosition().y << std::endl;

    //float LDist, RDist, TDist, BDist;

    int side = getPushSide(this_elem, elem, windowSize);

    switch (side) {
    case LEFT:
        while (this_elem.getGlobalBounds().intersects(elem.getGlobalBounds()))
            this_elem.mustMove(sf::Vector2f(-1, 0));

        this_elem.setBlock(true, RIGHT);
        break;
    case RIGHT:
        while (this_elem.getGlobalBounds().intersects(elem.getGlobalBounds()))
            this_elem.mustMove(sf::Vector2f(1, 0));

        this_elem.setBlock(true, LEFT);
        break;
    case UP:
        while (this_elem.getGlobalBounds().intersects(elem.getGlobalBounds()))
            this_elem.mustMove(sf::Vector2f(0, -1));
        this_elem.setBlock(true, DOWN);
        break;
    case DOWN:
        while (this_elem.getGlobalBounds().intersects(elem.getGlobalBounds()))
            this_elem.mustMove(sf::Vector2f(0, 1));
        this_elem.setBlock(true, UP);
        break;
    default: {
        PhysElem* pe = nullptr;
        IF_CLASS(PhysElem, pe, elem) {
            switch (side) {
            case -LEFT:
                while (pe->getGlobalBounds().intersects(this_elem.getGlobalBounds()))
                    pe->mustMove(sf::Vector2f(-1, 0));

                pe->setBlock(true, RIGHT);
                break;
            case -RIGHT:
                while (pe->getGlobalBounds().intersects(this_elem.getGlobalBounds()))
                    pe->mustMove(sf::Vector2f(1, 0));

                pe->setBlock(true, LEFT);
                break;
            case -UP:
                while (pe->getGlobalBounds().intersects(this_elem.getGlobalBounds()))
                    pe->mustMove(sf::Vector2f(0, -1));
                pe->setBlock(true, DOWN);
                break;
            case -DOWN:
                while (pe->getGlobalBounds().intersects(this_elem.getGlobalBounds()))
                    pe->mustMove(sf::Vector2f(0, 1));
                pe->setBlock(true, UP);
                break;
            default:
                std::cout << __PRETTY_FUNCTION__ << " error. Unknown push side!" << std::endl;
                break;
            }
        }
    }
    }

    //getDistances(elem, windowSize, LDist, RDist, TDist, BDist);


//    float offsetX = 0;
//    float offsetY = 0;

//    std::cout << "LDist = " << LDist << " RDist = " << RDist << " TDist = " << TDist << " BDist = " << BDist << std::endl;

//    // In case of all blacked element, move up
//    if(     TDist <= LDist && TDist <= RDist && TDist <= BDist)
//        offsetY = -1;
//    else if(RDist <= LDist && RDist <= TDist && RDist <= BDist)
//        offsetX = 1;
//    else if(LDist <= RDist && LDist <= TDist && LDist <= BDist)
//        offsetX = -1;
//    else if(BDist <= LDist && BDist <= RDist && BDist <= TDist)
//        offsetY = 1;
//    else {
//        std::cerr << __PRETTY_FUNCTION__ << ": I do not know what happened!!!" << std::endl;
//        exit(0);
//    }

//    while (this->getGlobalBounds().intersects(elem.getGlobalBounds())) {
//        //std::cout << "Intersect!" << std::endl;
//        this->mustMove(sf::Vector2f(offsetX, offsetY));
//    }

//    if(offsetX > 0)
//        block_.left_  = true;

//    if(offsetX < 0)
//        block_.right_ = true;

//    if(offsetY > 0)
//        block_.top_   = true;

//    if(offsetY < 0)
//        block_.bot_   = true;

    //this->Stop();
}

void getDistances (PhysElem& this_elem, GrElem &elem, sf::Vector2u& windowSize, float& LDist, float& RDist, float& TDist, float& BDist) {
    LDist = this_elem.getGlobalBounds().left - elem.getGlobalBounds().left      + this_elem.getGlobalBounds().width;
    RDist = elem.getGlobalBounds().left      - this_elem.getGlobalBounds().left + elem.getGlobalBounds().width;
    TDist = this_elem.getGlobalBounds().top  - elem.getGlobalBounds().top       + this_elem.getGlobalBounds().height;
    BDist = elem.getGlobalBounds().top       - this_elem.getGlobalBounds().top  + elem.getGlobalBounds().height;

    std::cout << "LDist = " << LDist << " RDist = " << RDist << " TDist = " << TDist << " BDist = " << BDist << std::endl;


//    if(block_ == true) {
//        std::cerr << "Error: Full blocked element!!! Set top as non blocked!" << std::endl;
//        block_.top_ = false;
//    }


}

int getPushSide(PhysElem& this_elem, GrElem &elem, sf::Vector2u &windowSize) {
    float LDist, RDist, TDist, BDist;

    getDistances(this_elem, elem, windowSize, LDist, RDist, TDist, BDist);

//    if(this_elem.getBlock(LEFT) || elem.getPosition().x <= 0)
//        LDist = std::numeric_limits<float>::max();

//    if(this_elem.getBlock(RIGHT) || elem.getPosition().x + elem.getGlobalBounds().width >= windowSize.x)
//        RDist = std::numeric_limits<float>::max();

//    if(this_elem.getBlock(UP) || elem.getPosition().y <= 0)
//        TDist = std::numeric_limits<float>::max();

//    if(this_elem.getBlock(DOWN) || elem.getPosition().y + elem.getGlobalBounds().height >= windowSize.y)
//        BDist = std::numeric_limits<float>::max();

//    std::cout << "LDist = " << LDist << " RDist = " << RDist << " TDist = " << TDist << " BDist = " << BDist << std::endl;

    // In case of all blacked element, move up
    if(TDist <= LDist && TDist <= RDist && TDist <= BDist) {
        if(elem.getPosition().y >= 0) {
            if(!this_elem.getBlock(UP))
                return UP;
            else
                return -DOWN;
        }
        else
            TDist = std::numeric_limits<float>::max(); // for future comparsion
    }

    if(RDist <= LDist && RDist <= TDist && RDist <= BDist) {
        if(elem.getPosition().x + elem.getGlobalBounds().width <= windowSize.x) {
            if(!this_elem.getBlock(RIGHT))
                return RIGHT;
            else
                return -LEFT;
        }
        else
            RDist = std::numeric_limits<float>::max(); // for future comparsion
    }

    if(LDist <= RDist && LDist <= TDist && LDist <= BDist) {
        if(elem.getPosition().x >= 0) {
            if(!this_elem.getBlock(LEFT))
                return LEFT;
            else
                return -RIGHT;
        }
        else
            LDist = std::numeric_limits<float>::max(); // for future comparsion
    }

    if(BDist <= LDist && BDist <= RDist && BDist <= TDist) {
        if(elem.getPosition().y + elem.getGlobalBounds().height <= windowSize.y) {
            if(!this_elem.getBlock(DOWN))
                return DOWN;
            else
                return -UP;
        }
    }


//    else {
//        std::cerr << __PRETTY_FUNCTION__ << ": I do not know what happened!!!" << std::endl;
//        exit(0);
//    }
    return UP;
}

void PhysElem::Action () {
    if(block_.left_ && speedX_ < 0) {
        speedX_ = 0;
        if(accelX_ < 0)
            accelX_ = 0;
    }

    if(block_.right_ && speedX_ > 0) {
        speedX_ = 0;
        if(accelX_ > 0)
            accelX_ = 0;
    }

    if(block_.top_ && speedY_ < 0) {
        speedY_ = 0;
        if(accelY_ < 0)
            accelY_ = 0;
    }

    if(block_.bot_ && speedY_ > 0) {
        speedY_ = 0;
        if(accelY_ > 0)
            accelY_ = 0;
    }

    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << "SpeedX = " << speedX_ << ", SpeedY = " << speedY_ << std::endl;
    std::cout << "AccelX = " << accelX_ << ", AccelY = " << accelY_ << std::endl;

    if(accelX_ != 0) {
        if(1 / std::abs(accelX_) < accelClockX_.getElapsedTime().asSeconds())
            this->incrSpeedX(accelX_ * accelClockX_.restart().asSeconds());
    }
    else
        accelClockX_.restart();

    if(accelY_ != 0) {
        if(1 / std::abs(accelY_) < accelClockY_.getElapsedTime().asSeconds())
        this->incrSpeedY(accelY_ * accelClockY_.restart().asSeconds());
    }
    else
        accelClockY_.restart();

}

sf::Vector2i PhysElem::Move() {

    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << "SpeedX = " << speedX_ << ", SpeedY = " << speedY_ << std::endl;
    std::cout << "AccelX = " << accelX_ << ", AccelY = " << accelY_ << std::endl;

    sf::Vector2i offset;
    offset.x = 0;
    offset.y = 0;

    float elapsedTimeX = moveClockX_.getElapsedTime().asSeconds();
    float elapsedTimeY = moveClockY_.getElapsedTime().asSeconds();

    if(speedX_ != 0) {
        if((1 / std::abs(speedX_)) < elapsedTimeX) { // вложенный, чтобы не обновлять всегда clock
            if((speedX_ < 0 && !block_.left_) || (speedX_ > 0 && !block_.right_)) {
                offset.x = speedX_ > 0 ? 1 : -1;
                this->mustMove(sf::Vector2f(speedX_ * elapsedTimeX, 0));
                block_ = false;
            }
            else {
                speedX_ = 0;
            }


            moveClockX_.restart();
        }
    }
    else {
        moveClockX_.restart();
    }

    if(speedY_ != 0) {
        if((1 / std::abs(speedY_)) < elapsedTimeY) {
            if((speedY_ < 0 && !block_.top_) || (speedY_ > 0 && !block_.bot_)) {
                offset.y = speedY_ > 0 ? 1 : -1;
                this->mustMove(sf::Vector2f(0, speedY_ * elapsedTimeY));
                block_ = false;
            }
            else {
                speedY_ = 0;
            }

            moveClockY_.restart();
        }
    }
    else {
        moveClockY_.restart();
    }


    return offset;


}

//void PhysElem::Stop() {
//    speedX_ = 0;
//    speedY_ = 0;
//}

void PhysElem::eventHendler(const sf::Event &event, const sf::Vector2f &mousePos) {
}

