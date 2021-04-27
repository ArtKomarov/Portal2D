#ifndef LEVEL2_HPP
#define LEVEL2_HPP

const char AUDIO_PATH[] = "/home/artem/Main/Games/Portal2D/Portal2-04-The_Courtesy_Call.ogg";

const char GLOBAL_TEXTURE_PATH[] = "/home/artem/Main/Games/Portal2D/Stuff.png";

const char PORT_AND_DOOR_TEXTURE_PATH[] = "/home/artem/Main/Games/Portal2D/Portals_Doors2.png";

const char WINDOW_TEXTURE_PATH[] = "/home/artem/Main/Games/Portal2D/Background2/Background2.png";

const char HERO_TEXTURE_PATH[] = "/home/artem/Main/Games/Portal2D/HeroRunSprite.png";

const char WHITE_WALL_PATH[] = "/home/artem/Main/Games/Portal2D/WhiteWall.png";

const char BLACK_WALL_PATH[] = "/home/artem/Main/Games/Portal2D/BlackWall2.png";

const char BOX_TEXTURE_PATH[] = "/home/artem/Main/Games/Portal2D/BoxTexture.png";

std::vector<GrElem*>*   GrElems   = new std::vector<GrElem*>();
std::vector<PhysElem*>* PhysElems = new std::vector<PhysElem*>();

// Init window
sf::RenderWindow window (sf::VideoMode(1920, 1080), "Portal 2D", sf::Style::Fullscreen);

// Init background
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
FinalDoor* fdoor         = new FinalDoor(portAndDoorTexture, fdoor_sprite);
fdoor->setPosition(sf::Vector2f(380, window.getSize().y / 3 + 150));
GrElems->push_back(fdoor);

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
hero->setPosition(sf::Vector2f(window.getSize().x / 5, window.getSize().y - 100));
// push to GrElems, PhysElems after portals


// Create boundaries
std::vector<sf::Sprite*>* boundarySprites = new std::vector<sf::Sprite*>();

sf::Texture* b_texture = new sf::Texture();
b_texture->loadFromFile(BLACK_WALL_PATH);
b_texture->setRepeated(true);

sf::Texture* w_texture = new sf::Texture();
w_texture->loadFromFile(WHITE_WALL_PATH);
w_texture->setRepeated(true);

// Ground
CreateBoundary(BLACK_BOUNDARY, b_texture, window.getSize().x, 100,
               0, window.getSize().y - 100, GrElems, boundarySprites);

// Frame_Down
CreateBoundary(BLACK_BOUNDARY, b_texture, window.getSize().x - 200, 20,
               100, window.getSize().y - 200 - 20, GrElems, boundarySprites);

// Roof
CreateBoundary(BLACK_BOUNDARY, b_texture, window.getSize().x, 10,
               0, 0, GrElems, boundarySprites);

// Frame_Top
CreateBoundary(BLACK_BOUNDARY, b_texture, window.getSize().x - 200, 20,
               100, 100, GrElems, boundarySprites);

// Left wall
CreateBoundary(BLACK_BOUNDARY, b_texture, 10, 10,
               0, 0, GrElems, boundarySprites);

CreateBoundary(WHITE_BOUNDARY, w_texture, 12, 140,
               0, 10, GrElems, boundarySprites);

CreateBoundary(BLACK_BOUNDARY, b_texture, 10, window.getSize().y - 150,
               0, 150, GrElems, boundarySprites);

// Frame_Left
CreateBoundary(WHITE_BOUNDARY, w_texture, 20, window.getSize().y - 300,
               100, 100, GrElems, boundarySprites);

// Right wall
CreateBoundary(BLACK_BOUNDARY, b_texture, 10, window.getSize().y,
               window.getSize().x - 10, 0, GrElems, boundarySprites);

// Frame_Right
CreateBoundary(BLACK_BOUNDARY, b_texture, 20, window.getSize().y - 550,
               window.getSize().x - 110, 100, GrElems, boundarySprites);

CreateBoundary(WHITE_BOUNDARY, w_texture, 20, 100,
               window.getSize().x - 130, 100 + 50, GrElems, boundarySprites);

//CreateBoundary(BLACK_BOUNDARY, b_texture, 20, window.getSize().y - 300 - 200 - 50 - 100,
//               window.getSize().x - 110, 100 + 50 + 100, GrElems, boundarySprites);


CreateBoundary(BLACK_BOUNDARY, b_texture, 20, 220,
               window.getSize().x - 110, window.getSize().y - 300 - 200 + 30 + 50, GrElems, boundarySprites);

// Frame_Central_Wall
CreateBoundary(BLACK_BOUNDARY, b_texture, 20, 80,
               window.getSize().x / 2, 120, GrElems, boundarySprites);

CreateBoundary(BLACK_BOUNDARY, b_texture, 20, window.getSize().y - 340 - 340 - 180,
               window.getSize().x / 2, 300, GrElems, boundarySprites);

CreateBoundary(WHITE_BOUNDARY, w_texture, 24, 220,
               window.getSize().x / 2 - 2, 120 + window.getSize().y - 340 - 340, GrElems, boundarySprites);

CreateBoundary(BLACK_BOUNDARY, b_texture, 20, 120,
               window.getSize().x / 2, 120 + window.getSize().y - 340 - 200 + 80, GrElems, boundarySprites);

// Parkour
CreateBoundary(BLACK_BOUNDARY, b_texture, 60, 20,
               window.getSize().x - 150 - 20, 250, GrElems, boundarySprites);

//    CreateBoundary(BLACK_BOUNDARY, b_texture, 20, 20,
//                   window.getSize().x - 200, 250, GrElems, boundarySprites);

CreateBoundary(BLACK_BOUNDARY, b_texture, 20, 20,
               window.getSize().x - 300, 250, GrElems, boundarySprites);

CreateBoundary(BLACK_BOUNDARY, b_texture, 20, 20,
               window.getSize().x - 450, 230, GrElems, boundarySprites);

CreateBoundary(BLACK_BOUNDARY, b_texture, 20, 20,
               window.getSize().x - 620, 250, GrElems, boundarySprites);

CreateBoundary(BLACK_BOUNDARY, b_texture, 20, 20,
               window.getSize().x - 750, 220, GrElems, boundarySprites);

CreateBoundary(BLACK_BOUNDARY, b_texture, 20, 20,
               window.getSize().x - 900, 300, GrElems, boundarySprites);

// Finish box
// Box_Ground
CreateBoundary(BLACK_BOUNDARY, b_texture, 200, 20,
               300, window.getSize().y / 3 + 200, GrElems, boundarySprites);

// Box_Top
CreateBoundary(BLACK_BOUNDARY, b_texture, 200, 20,
               300, window.getSize().y / 3, GrElems, boundarySprites);

// Box_Left
CreateBoundary(BLACK_BOUNDARY, b_texture, 20, 60,
               300, window.getSize().y / 3 + 20, GrElems, boundarySprites);

CreateBoundary(BLACK_BOUNDARY, b_texture, 20, 60,
               300, window.getSize().y / 3 + 20 + 140, GrElems, boundarySprites);

sf::Sprite* box_sprite = new sf::Sprite(*b_texture, sf::IntRect(0, 0, 20, 79));
Box* box = new Box(b_texture, box_sprite);
box->setPosition(sf::Vector2f(300, window.getSize().y / 3 + 20 + 60));
GrElems->push_back(box);
PhysElems->push_back(box);

// Box_Right
//CreateBoundary(BLACK_BOUNDARY, b_texture, 20, 220,
//               500, window.getSize().y / 3, GrElems, boundarySprites);

CreateBoundary(BLACK_BOUNDARY, b_texture, 20, 80,
               500, window.getSize().y / 3, GrElems, boundarySprites);

CreateBoundary(BLACK_BOUNDARY, b_texture, 20, 80,
               500, window.getSize().y / 3 + 20 + 60, GrElems, boundarySprites);

CreateBoundary(BLACK_BOUNDARY, b_texture, 20, 60,
               500, window.getSize().y / 3 + 20 + 140, GrElems, boundarySprites);

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

Manager manager(GrElems, PhysElems, &window, WindowSprite);

sf::SoundBuffer buffer;
if (!buffer.loadFromFile(AUDIO_PATH))
    return -1;

sf::Sound sound(buffer);
sound.setLoop(true);
sound.play();

manager.gameLoop();


// FREE MEMORY

// Delete textures
delete WindowTexture;
delete globalTexture;
delete portAndDoorTexture;
//delete boxTexture;
delete HeroTexture;
delete b_texture;
delete w_texture;

// Delete sprites
delete WindowSprite;
delete fdoor_sprite;
//delete box_sprite;
//delete box_sprite2;
delete HeroSprite;
delete p1_sprite;
delete p2_sprite;

for(auto& elem : *GrElems) {
    delete elem;
}

for(auto& b : *boundarySprites) {
    delete b;
}

delete boundarySprites;
delete PhysElems;
delete GrElems;

#endif // LEVEL2_HPP
