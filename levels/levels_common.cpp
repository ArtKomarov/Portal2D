#include "levels/levels_common.h"

//const char* PROJECT_PATH = "../Potal2D";

void CreateBoundary(int type, sf::Texture* texture, int width, int height,
                    float posX, float posY, std::vector<GrElem*>* container, std::vector<sf::Sprite*>* boundarySprites) {

    sf::Sprite* sprite = new sf::Sprite(*texture, sf::IntRect(0, 0, width, height));
    boundarySprites->push_back(sprite);

    Boundary* b = new Boundary(type, texture, sprite);
    b->setPosition(sf::Vector2f(posX, posY));

    container->push_back(b);
}
