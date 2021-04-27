#include <unistd.h>

#include "finaldoor.h"
#include "hero.h"


FinalDoor::FinalDoor(sf::Texture *texture, sf::Sprite *sprite) :
    GrElem(texture, sprite),
    State_(0),
    openSpeed_(DEFAULT_OPEN_SPEED) {

    essential_ = true;
}

void FinalDoor::Update(sf::RenderWindow &target) {
    if(toClose_.getElapsedTime().asSeconds() > 1 / openSpeed_) {
        if(State_ > 0) {
            --State_;

            sprite_->setTextureRect(sf::IntRect(FDOOR_POS_X + State_ * FDOOR_WIDTH, FDOOR_POS_Y, FDOOR_WIDTH, FDOOR_HEIGHT));

            toClose_.restart();
        }
    }

    GrElem::Update(target);
}

void FinalDoor::Intersect(GrElem &elem, sf::Vector2u windowSize) {
    if(toOpen_.getElapsedTime().asSeconds() > 1 / openSpeed_) {
        Hero* hero = nullptr;
        IF_CLASS(Hero, hero, elem) {
            if(State_ == OPEN) {
                this->setActive(false);
            }
            else {
                toOpen_.restart();
                toClose_.restart();

                State_++;
                sprite_->setTextureRect(sf::IntRect(FDOOR_POS_X + State_ * FDOOR_WIDTH, FDOOR_POS_Y, FDOOR_WIDTH, FDOOR_HEIGHT));
            }
        }
    }
}
