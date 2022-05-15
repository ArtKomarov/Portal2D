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

#include "levels/level1.hpp"
#include "levels/level2.hpp"

int main() {
    std::cout << "Enter level number: 1 or 2." << std::endl;
    int lvl;
    std::cin >> lvl;
    while (lvl != 1 && lvl != 2) {
        std::cout << "Level must be 1 or 2!" << std::endl;
        std::cin >> lvl;
    }

    if(lvl == 1) {
        level1();
    } else {
        level2();
    }

    return 0;
}

