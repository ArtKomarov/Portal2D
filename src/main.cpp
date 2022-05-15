#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "graphics.h"
#include "manager.h"
#include "hero.h"
#include "boundary.h"
#include "portal.h"
#include "finaldoor.h"
#include "box.h"

void CreateBoundary(int type, sf::Texture* texture, int width, int height,
                    float posX, float posY, std::vector<GrElem*>* container, std::vector<sf::Sprite*>* boundarySprites);

int main() {
    std::cout << "Enter level number: 1 or 2." << std::endl;
    int lvl;
    std::cin >> lvl;
    while (lvl != 1 && lvl != 2) {
        std::cout << "Level must be 1 or 2!" << std::endl;
        std::cin >> lvl;
    }

    if(lvl == 1) {
#include "level1.hpp"
    }
        else {
#include "level2.hpp"
    }

    return 0;
}

void CreateBoundary(int type, sf::Texture* texture, int width, int height,
                    float posX, float posY, std::vector<GrElem*>* container, std::vector<sf::Sprite*>* boundarySprites) {

    sf::Sprite* sprite = new sf::Sprite(*texture, sf::IntRect(0, 0, width, height));
    boundarySprites->push_back(sprite);

    Boundary* b = new Boundary(type, texture, sprite);
    b->setPosition(sf::Vector2f(posX, posY));

    container->push_back(b);
}
