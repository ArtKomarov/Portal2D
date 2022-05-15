#ifndef LEVELS_COMMON_H
#define LEVELS_COMMON_H

#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "graphics.h"
#include "boundary.h"

void CreateBoundary(int type, sf::Texture* texture, int width, int height,
                    float posX, float posY, std::vector<GrElem*>* container, std::vector<sf::Sprite*>* boundarySprites);

#endif // LEVELS_COMMON_H
