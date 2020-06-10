#include <iostream>

#include <SFML/Audio.hpp>

#include "graphics.h"
#include "manager.h"
#include "hero.h"

const char* AUDIO_PATH = "/home/artem/Main/Games/Portal2-04-The_Courtesy_Call.ogg";
const char* GLOBAL_TEXTURE_PATH = "/home/artem/Main/Games/Stuff.png";
const char* WINDOW_TEXTURE_PATH = "/home/artem/Main/Games/Background.png";

int main() {

    //Init textures
    sf::Texture* GlobalTexture = new sf::Texture();
    GlobalTexture->loadFromFile(GLOBAL_TEXTURE_PATH);
    sf::Texture windowTexture;
    windowTexture.loadFromFile(WINDOW_TEXTURE_PATH);
    sf::Sprite* windowSprite = new sf::Sprite(windowTexture, sf::IntRect(0, 0, WINDOW_SIZE, WINDOW_SIZE));

    // Init hero + portals
    Hero* hero = new Hero(GlobalTexture);
    hero->SetPosition(sf::Vector2f(WINDOW_SIZE / 2, WINDOW_SIZE / 2));
    hero->GetPortals()[0]->SetPosition(hero->GetPosition());
    hero->GetPortals()[1]->SetPosition(hero->GetPosition());

    std::map<const char*, Boundary*>* boundaries = new std::map<const char*, Boundary*>();

    // Create boundaries
    Boundary *b1 = new Boundary(0, new sf::RectangleShape(sf::Vector2f(WINDOW_SIZE, WINDOW_BOUNDS_OFFSET)), nullptr);
    b1->SetPosition(sf::Vector2f(0, WINDOW_SIZE - WINDOW_BOUNDS_OFFSET));
    boundaries->insert(std::make_pair("Boundary_1", b1));

    Boundary *b2 = new Boundary(0, new sf::RectangleShape(sf::Vector2f(WINDOW_BOUNDS_OFFSET, WINDOW_SIZE)), nullptr);
    b2->SetPosition(sf::Vector2f(0, 0));
    boundaries->insert(std::make_pair("Boundary_2", b2));

    Boundary *b3 = new Boundary(0, new sf::RectangleShape(sf::Vector2f(WINDOW_SIZE, WINDOW_BOUNDS_OFFSET)), nullptr);
    b3->SetPosition(sf::Vector2f(0, 0));
    boundaries->insert(std::make_pair("Boundary_3", b3));

    Boundary *b4 = new Boundary(0, new sf::RectangleShape(sf::Vector2f(WINDOW_BOUNDS_OFFSET, WINDOW_SIZE)), nullptr);
    b4->SetPosition(sf::Vector2f(WINDOW_SIZE - WINDOW_BOUNDS_OFFSET, 0));
    boundaries->insert(std::make_pair("Boundary_4", b4));

    // Set graphical elements
    std::map <std::string, GrElem*> *GrElements = new std::map<std::string, GrElem*>();
    GrElements->insert(std::make_pair("Hero", hero));
    GrElements->insert(std::make_pair("1_Portal", hero->GetPortals()[0]));
    GrElements->insert(std::make_pair("2_Portal", hero->GetPortals()[1]));

    for(auto &elem : *boundaries) {
        GrElements->insert(std::make_pair(elem.first, elem.second));
    }

    Manager manager(GlobalTexture, hero, boundaries, GrElements, windowSprite, WINDOW_SIZE);

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(AUDIO_PATH))
        return -1;

    sf::Sound sound(buffer);
    sound.setLoop(true);
    sound.play();

    manager.GameLoop();
    return 0;
}
