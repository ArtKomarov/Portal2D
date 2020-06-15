#include <cassert>
#include <iostream>

#include "physics.h"


physics::physics(std::vector<PhysElem *> *elements) :
    elements_(elements) {
    assert(elements != nullptr);
}

void physics::Start() {
    for(auto& elem : *elements_) {
        elem->clockRestart();
    }
}

void physics::Activities() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    int counter = 0;

    for(auto& elem : *elements_) {
        if(elem->getActive()) {
            std::cout << "in gravity for, iter " << counter << std::endl;
            if(!elem->getBlock()) {
                elem->setAccelY(accelOfGravity_); // a = g
                std::cout << "in if, iter " << counter << std::endl << std::endl;
            }
            else {
                elem->setAccelY(0); // ground, ma = sum(F) = F - N = 0 => a = 0
            }
        }
    }

    counter = 0;

    // Main elements actions
    bool Continue = true;

    while(Continue) {
        Continue = false;

        for(auto elem = elements_->begin(); elem != elements_->end(); ++elem) {
            if((*elem)->getActive()) {
                (*elem)->Action();
            }
            else {
                elements_->erase(elem);

                Continue = true;

                break;
            }
        }
    }

}

void physics::Movement() {
    for(auto& elem : *elements_)
        elem->Move();
}

void physics::eventHandling(const sf::Event &event, const sf::Vector2f& mousePosition) {
    int i = 0;
    for(auto& elem : *elements_) {
        std::cout << __PRETTY_FUNCTION__ << i << std::endl;
        elem->eventHendler(event, mousePosition);
    }
}

