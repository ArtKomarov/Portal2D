#include "boundary.h"

Boundary::Boundary (int type, sf::Texture* texture, sf::Sprite* sprite) :
    GrElem(texture, sprite),
    type_(type) {
}

Boundary::~Boundary() {

}

int Boundary::getType() const {
    return type_;
}

//void Boundary::setPosition(const sf::Vector2f &position) {
//    sprite_->setPosition(position);
//}

//const sf::Vector2f &Boundary::getPosition() const {
//    return sprite_->getPosition();
//}

//sf::FloatRect Boundary::getGlobalBounds() const {
//    return sprite_->getGlobalBounds();
//}


//void Boundary::Update(sf::RenderWindow &target) {
//    target.draw(*shape_);
//    return 0;
//}


//void Boundary::mustMove(sf::Vector2f offset) {
//    sprite_->move(offset);
//}

//void Boundary::Stop() {
//}

