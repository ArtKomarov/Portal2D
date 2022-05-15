#include <iostream>

#include "grelem.h"

//GrElem::GrElem () :
//    GrElem(nullptr, nullptr) {
//}

GrElem::GrElem (sf::Texture *texture, sf::Sprite *sprite) :
    active_(true),
    essential_(false),
    texture_(texture),
    sprite_(sprite) {
    // this->mustMove(sf::Vector2f(0, 0));
}

void GrElem::setPosition(const sf::Vector2f &position) {
    sprite_->setPosition(position);
}

void GrElem::setActive(bool state) {
    active_ = state;
}

bool GrElem::getActive() const {
    return active_;
}

bool GrElem::getEssential() const {
    return essential_;
}

const sf::Vector2f &GrElem::getPosition() const {
    return sprite_->getPosition();
}

sf::FloatRect GrElem::getGlobalBounds() const {
    return sprite_->getGlobalBounds();
}


void GrElem::Update(sf::RenderWindow &target) {
    target.draw(*sprite_);
}


void GrElem::mustMove(sf::Vector2f offset) {
    sprite_->move(offset);
}

void GrElem::Intersect(GrElem &elem, sf::Vector2u windowSize) {
    // for other elements
}

//void GrElem::Stop() {
//}

GrElem::~GrElem () {
}
