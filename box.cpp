#include "box.h"
#include "boundary.h"

Box::Box(sf::Texture *texture, sf::Sprite *sprite) :
    PhysElem(texture, sprite) {
    block_ = false;
}

void Box::Intersect(GrElem &elem, sf::Vector2u windowSize) {
    Boundary *b = nullptr;
    IF_CLASS(Boundary, b, elem) {
        pushOff(*this, elem, windowSize);
    }
    else {
        PhysElem* p = nullptr;
        IF_CLASS(PhysElem, p, elem) {
            pushOff(*this, elem, windowSize);
            block_ = false;
        }
    }
}



sf::FloatRect Box::getGlobalBounds() const {
    if(sprite_->getGlobalBounds().width > 10)
        return sf::FloatRect(sprite_->getGlobalBounds().left + 5,
                             sprite_->getGlobalBounds().top,
                             sprite_->getGlobalBounds().width - 10,
                             sprite_->getGlobalBounds().height);
    else
        return PhysElem::getGlobalBounds();
}

