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

const char AUDIO_PATH[] = "/home/artem/Main/Games/Portal2D/Portal2-04-The_Courtesy_Call.ogg";

const char GLOBAL_TEXTURE_PATH[] = "/home/artem/Main/Games/Portal2D/Stuff.png";

const char PORT_AND_DOOR_TEXTURE_PATH[] = "/home/artem/Main/Games/Portal2D/Portals_Doors2.png";

const char WINDOW_TEXTURE_PATH[] = "/home/artem/Main/Games/Portal2D/Background2/Background2.png";

const char HERO_TEXTURE_PATH[] = "/home/artem/Main/Games/Portal2D/HeroRunSprite.png";

const char WHITE_WALL_PATH[] = "/home/artem/Main/Games/Portal2D/WhiteWall.png";

const char BLACK_WALL_PATH[] = "/home/artem/Main/Games/Portal2D/BlackWall2.png";

const char BOX_TEXTURE_PATH[] = "/home/artem/Main/Games/Portal2D/BoxTexture.png";

void CreateBoundary(Boundary* b, int type, sf::Sprite* sprite, sf::Texture* texture, int width, int height,
                    float posX, float posY, std::vector<GrElem*>* container);

int main() {// door 330x200
    std::vector<GrElem*>*   GrElems   = new std::vector<GrElem*>();
    std::vector<PhysElem*>* PhysElems = new std::vector<PhysElem*>();

    // Init window
    sf::RenderWindow window (sf::VideoMode(1920, 1080), "Portal 2D", sf::Style::Fullscreen);

    // Init textures
//    sf::Texture GlobalTexture;
//    GlobalTexture.loadFromFile (GLOBAL_TEXTURE_PATH);

    sf::Texture* WindowTexture = new sf::Texture();
    WindowTexture->loadFromFile(WINDOW_TEXTURE_PATH);
    sf::Sprite* WindowSprite = new sf::Sprite(*WindowTexture,
                                              sf::IntRect(0, 0, static_cast<int>(window.getSize().x),
                                                          static_cast<int>(window.getSize().y)));

    // Init global texture, used by many elements
    sf::Texture *globalTexture = new sf::Texture();
    globalTexture->loadFromFile(GLOBAL_TEXTURE_PATH);

    sf::Texture* portAndDoorTexture = new sf::Texture();
    portAndDoorTexture->loadFromFile(PORT_AND_DOOR_TEXTURE_PATH);

    // Init exit
    sf::Sprite* fdoor_sprite = new sf::Sprite(*portAndDoorTexture, sf::IntRect(FDOOR_POS_X, FDOOR_POS_Y, FDOOR_WIDTH, FDOOR_HEIGHT));
    FinalDoor* fdoor = new FinalDoor(portAndDoorTexture, fdoor_sprite);
    fdoor->setPosition(sf::Vector2f(20, 300-10));
    GrElems->push_back(fdoor);

    // Simple object
    sf::Texture* boxTexture = new sf::Texture();
    boxTexture->loadFromFile(BOX_TEXTURE_PATH);
    sf::Sprite* box_sprite = new sf::Sprite(*boxTexture, sf::IntRect(0, 0, 83, 83));
    Box* box = new Box(boxTexture, box_sprite);
    box->setPosition(sf::Vector2f(window.getSize().x / 2 - 200, 600));
    GrElems->push_back(box);
    PhysElems->push_back(box);

    // Simple object 2
    sf::Sprite* box_sprite2 = new sf::Sprite(*boxTexture, sf::IntRect(0, 0, 50, 50));
    Box* box2 = new Box(boxTexture, box_sprite2);
    box2->setPosition(sf::Vector2f(200, 0));
    GrElems->push_back(box2);
    PhysElems->push_back(box2);

    // Init hero
    sf::Texture* HeroTexture = new sf::Texture();
    sf::Sprite*  HeroSprite  = new sf::Sprite();
    if(!HeroTexture->loadFromFile(HERO_TEXTURE_PATH,
                              sf::IntRect(0, 0, 1000, 1000)
                              )) {
        std::cerr << "Error while loading texture" << std::endl;
    } else {
        HeroSprite->setTexture     (*HeroTexture);
        HeroSprite->setTextureRect (sf::IntRect(0, 0, 49, 59));
    }

    Hero *hero = new Hero(HeroTexture, HeroSprite);
    hero->setPosition(sf::Vector2f(window.getSize().x / 5, window.getSize().y - 300));
    // push after portals


    // Create boundaries
    sf::Texture* b_texture = new sf::Texture();
    b_texture->loadFromFile(BLACK_WALL_PATH);
    b_texture->setRepeated(true);

    sf::Texture* w_texture = new sf::Texture();
    w_texture->loadFromFile(WHITE_WALL_PATH);
    w_texture->setRepeated(true);

    Boundary*   b1        = nullptr;
    sf::Sprite* b1_sprite = nullptr;
    CreateBoundary(b1, BLACK_BOUNDARY, b1_sprite, b_texture, window.getSize().x, 100,
                   0, window.getSize().y - 100, GrElems);

    Boundary*   b2        = nullptr;
    sf::Sprite* b2_sprite = nullptr;
    CreateBoundary(b2, BLACK_BOUNDARY, b2_sprite, b_texture, window.getSize().x, 10,
                   0, 0, GrElems);

    Boundary*   b3        = nullptr;
    sf::Sprite* b3_sprite = nullptr;
    CreateBoundary(b3, BLACK_BOUNDARY, b3_sprite, b_texture, 10, window.getSize().y - 50 - 700,
                   0, 50, GrElems);


    Boundary*   b4        = nullptr;
    sf::Sprite* b4_sprite = nullptr;
    CreateBoundary(b4, BLACK_BOUNDARY, b4_sprite, b_texture, 10, window.getSize().y - 500,
                   window.getSize().x - 10, 500, GrElems);

    Boundary*   b4_2        = nullptr;
    sf::Sprite* b4_2_sprite = nullptr;
    CreateBoundary(b4_2, BLACK_BOUNDARY, b4_2_sprite, b_texture, 10, 300,
                   window.getSize().x - 10, 0, GrElems);



    Boundary*   b5        = nullptr;
    sf::Sprite* b5_sprite = nullptr;
    CreateBoundary(b5, WHITE_BOUNDARY, b5_sprite, w_texture, 12, 200,
                   window.getSize().x - 12, 300, GrElems);


    Boundary*   b6        = nullptr;
    sf::Sprite* b6_sprite = nullptr;
    CreateBoundary(b6, WHITE_BOUNDARY, b6_sprite, w_texture, 12, 700 - 100,
                   0, window.getSize().y - 700, GrElems);


    Boundary* b7 = nullptr;
    sf::Sprite* b7_sprite = nullptr;
    CreateBoundary(b7, BLACK_BOUNDARY, b7_sprite, b_texture, 400, 50,
                   window.getSize().x / 2 + 500, window.getSize().y / 2, GrElems);

    Boundary* b8 = nullptr;
    sf::Sprite* b8_sprite = nullptr;
    CreateBoundary(b8, BLACK_BOUNDARY, b8_sprite, b_texture, 1000, 30,
                   0, window.getSize().y / 2 - 200, GrElems);

    Boundary* b9 = nullptr;
    sf::Sprite* b9_sprite = nullptr;
    CreateBoundary(b9, WHITE_BOUNDARY, b9_sprite, w_texture, 12, 40,
                   0, 10, GrElems);

    Boundary* b10 = nullptr;
    sf::Sprite* b10_sprite = nullptr;
    CreateBoundary(b10, BLACK_BOUNDARY, b10_sprite, b_texture, 20, window.getSize().y / 2 - 50,
                   window.getSize().x / 2, window.getSize().y / 2 - 50, GrElems);

    // Init portals
    sf::Sprite* p1_sprite = new sf::Sprite(*globalTexture, sf::IntRect(190, 27, 10, 30));
    Portal* portal1 = new Portal(BLUE, globalTexture, p1_sprite, hero);

    sf::Sprite* p2_sprite = new sf::Sprite(*globalTexture, sf::IntRect(190, 27, 10, 30));
    Portal* portal2 = new Portal(ORANGE, globalTexture, p2_sprite, hero);

    portal1->setPortal2(portal2);
    portal2->setPortal2(portal1);

    PhysElems->push_back(portal1);
    PhysElems->push_back(portal2);

    GrElems->push_back(portal1);
    GrElems->push_back(portal2);

    GrElems->push_back(hero);
    PhysElems->push_back(hero);


//    sf::Sprite b4_sprite(w_texture, sf::IntRect(0, 0, 10, window.getSize().y));
//    Boundary b4(BLACK_BOUNDARY, &w_texture, &b4_sprite);
//    b4.setPosition(sf::Vector2f(window.getSize().x - 10, 0));
//    GrElems->push_back(&b4);

//    sf::Sprite b4_sprite(b_texture, sf::IntRect(0, 0, 10, window.getSize().y));
//    Boundary b4(BLACK_BOUNDARY, &w_texture, &b4_sprite);
//    b4.setPosition(sf::Vector2f(window.getSize().x - 10, 0));
//    GrElems->push_back(&b4);


//    Boundary *b1 = new Boundary(0, new sf::RectangleShape(sf::Vector2f(WINDOW_SIZE, WINDOW_BOUNDS_OFFSET)), nullptr);
//    b1->SetPosition(sf::Vector2f(0, WINDOW_SIZE - WINDOW_BOUNDS_OFFSET));
//    boundaries->insert(std::make_pair("Boundary_1", b1));

//    Boundary *b2 = new Boundary(0, new sf::RectangleShape(sf::Vector2f(WINDOW_BOUNDS_OFFSET, WINDOW_SIZE)), nullptr);
//    b2->SetPosition(sf::Vector2f(0, 0));
//    boundaries->insert(std::make_pair("Boundary_2", b2));

//    Boundary *b3 = new Boundary(0, new sf::RectangleShape(sf::Vector2f(WINDOW_SIZE, WINDOW_BOUNDS_OFFSET)), nullptr);
//    b3->SetPosition(sf::Vector2f(0, 0));
//    boundaries->insert(std::make_pair("Boundary_3", b3));

//    Boundary *b4 = new Boundary(0, new sf::RectangleShape(sf::Vector2f(WINDOW_BOUNDS_OFFSET, WINDOW_SIZE)), nullptr);
//    b4->SetPosition(sf::Vector2f(WINDOW_SIZE - WINDOW_BOUNDS_OFFSET, 0));
//    boundaries->insert(std::make_pair("Boundary_4", b4));


    Manager manager(GrElems, PhysElems, &window, WindowSprite);

    //Manager manager(GlobalTexture, hero, boundaries, GrElements, windowSprite, WINDOW_SIZE);

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(AUDIO_PATH))
        return -1;

    sf::Sound sound(buffer);
    sound.setLoop(true);
    sound.play();

    manager.gameLoop();

    for(auto& elem : *PhysElems) {
        delete elem;
        elem = nullptr;
    }

    delete PhysElems;
    delete GrElems;

    return 0;
}

void CreateBoundary(Boundary* b, int type, sf::Sprite* sprite, sf::Texture* texture, int width, int height,
                    float posX, float posY, std::vector<GrElem*>* container) {

    sprite = new sf::Sprite(*texture, sf::IntRect(0, 0, width, height));

    b = new Boundary(type, texture, sprite);
    b->setPosition(sf::Vector2f(posX, posY));

    container->push_back(b);
}
