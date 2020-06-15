#include <iostream>
#include <unistd.h>
#include <assert.h>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "graphics.h"
#include "grelem.h"

const char START_TEXTURE_PATH[] = "/home/artem/Main/Games/Portal2D/StartScreen3.png";
const char FINISH_TEXTURE_PATH[] = "/home/artem/Main/Games/Portal2D/FinishScreen.jpg";

const char FINISH_AUDIO_PATH[] = "/home/artem/Main/Games/Portal2D/DidIt.wav";

//graphics::graphics() :
//    window_(new sf::RenderWindow(sf::VideoMode(800, 800), "SFML works!")),
//    PosChangeMax_(1000),
//    PosChange_(0),
//    hero_(sf::Vector2f(window_->getSize().x / 2, window_->getSize().y / 2)),
//    shape_(100.f) {
//    // Init window
//    window_->setPosition(sf::Vector2i(0, 0));
//    window_->setFramerateLimit(60);         // One of!
//    //window_.setVerticalSyncEnabled(true); // One of!

//    // Init graphical elements
//    elements_.push_back(new Hero(sf::Vector2f(window_->getSize().x / 2 + 100, window_->getSize().y / 2 + 100)));

//    shape_.setFillColor(sf::Color::Green);

//    std::cout << "Here" << std::endl;
//    //hero_.setColor(sf::Color(255, 0, 0));
//    //window_->draw(hero_.GetSprite());
//    this->UpdateWindow();
//}

//graphics::graphics(std::map<std::string, GrElem*> *elements, sf::Texture* GlobalTexture,
//                   sf::Sprite *windowSprite, unsigned int WindowSize) :
//    window_(new sf::RenderWindow(sf::VideoMode(WindowSize, WindowSize), "Portal 2D")), // sf::Style::Fullscreen)),
//    windowSprite_(windowSprite),
//    //PosChangeMax_(1000),
//    //PosChange_(0),
//    GlobalTexture_(GlobalTexture),
//    elements_(elements)
////    hero_(sf::Vector2f(window_->getSize().x / 2, window_->getSize().y / 2)),
//    {

//    std::cout << "Window pos: " << window_->getPosition().x << " " << window_->getPosition().x
//              << ", int coords: " << window_->mapPixelToCoords(window_->getPosition()).x
//              << " " << window_->mapPixelToCoords(window_->getPosition()).y
//              << ", size: " << window_->getSize().x << " " << window_->getSize().y << std::endl;

//    if(elements == nullptr) {
//        std::cout << __PRETTY_FUNCTION__ << ": elements is nullptr!" << std::endl;
//        exit(0);
//    }
//    std::cout << "List of graphical elements:" << std::endl;
//    for(auto &elem : *elements_) {
//        std::cout << elem.first << std::endl;
//    }

//    // Init window
//    window_->setKeyRepeatEnabled(true);
//    window_->setPosition(window_->mapCoordsToPixel(sf::Vector2f(0, 0)));
//    window_->setFramerateLimit(60);         // One of!
//    //window_->setVerticalSyncEnabled(true); // One of!

//    //std::cout << "window pos: " << window_->getPosition().x << " " << window_->getPosition().y << std::endl;

//    // Init graphical elements
//    //elements_->at("Hero")->SetPosition(sf::Vector2f(window_->getSize().x / 2, window_->getSize().y / 2 - 100));
//    //elements_->at("1_Portal")->SetPosition(sf::Vector2f(-100, -100));
//    //elements_->at("2_Portal")->SetPosition(sf::Vector2f(-100, -100));
//    //elements_->at("Boundary_1")->SetPosition(sf::Vector2f(0, window_->getSize().y - 10));
//    //elements_->at("Boundary_2")->SetPosition(sf::Vector2f(window_->getSize().x / 2 - 400, window_->getSize().y / 2 - 200));

//    //hero_.setColor(sf::Color(255, 0, 0));
//    //window_->draw(hero_.GetSprite());
//    this->UpdateWindow();
//}

const float PLACEMENT_MOVE_STEP = 0.5;

graphics::graphics(sf::RenderWindow* window, sf::Sprite* background, std::vector<GrElem*>* elements) :
    window_     (window),
    background_ (background),
    elements_   (elements) {
    //window_ = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Portal 2D", sf::Style::Fullscreen);

    assert(window_ != nullptr);
    assert(elements_ != nullptr);

    // Init window
    window_->setKeyRepeatEnabled(true);
    //window_->setPosition(window_->mapCoordsToPixel(sf::Vector2f(0, 0)));
    window_->setFramerateLimit(60);         // One of!
    //window_->setVerticalSyncEnabled(true); // One of!

}

//graphics::graphics(std::vector<GrElem *> *elements, sf::Sprite *background) :
//    window_(sf::VideoMode(1920, 1080), "Portal 2D", sf::Style::Fullscreen),
//    background_(background),
//    elements_(elements) {

//    window_.setKeyRepeatEnabled(true);
//    //window_->setPosition(window_->mapCoordsToPixel(sf::Vector2f(0, 0)));
//    window_.setFramerateLimit(60);         // One of!
//    //window_->setVerticalSyncEnabled(true); // One of!
//}

graphics::~graphics() {
}

////                       FOR PHYSICS
/*
bool graphics::EventHendler(const sf::Event &event) {
    if(event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f MousePos = window_->mapPixelToCoords(sf::Mouse::getPosition(*window_));
        for(auto& elem : *elements_) {
            if(elem.second->MouseHendler(event, MousePos))
                return true;
        }
    }

    return false;

}
*/
// Accessors
bool graphics::windowIsOpen() const {
    return window_->isOpen();
}

bool graphics::windowPoolEvent(sf::Event &event) {
    return window_->pollEvent(event);
}

sf::Vector2f graphics::getMousePosition() const {
    return window_->mapPixelToCoords(sf::Mouse::getPosition(*window_));
}

//void graphics::clearWindow() {
//    window_->clear();
//    if(background_)
//      window_->draw(*background_);
//}

//void graphics::displayWindow() {
//    window_->display();
//}

void graphics::closeWindow() {
    window_->close();
}

void graphics::Start() {
    sf::Texture startTexture;
    startTexture.loadFromFile(START_TEXTURE_PATH, sf::IntRect(0, 0, static_cast<int>(window_->getSize().x),
                                                              static_cast<int>(window_->getSize().y)));
    sf::Sprite startSprite(startTexture, sf::IntRect((startTexture.getSize().x - window_->getSize().x) / 2,
                                                     (startTexture.getSize().y - window_->getSize().y) / 2 + 30,
                                                     static_cast<int>(window_->getSize().x),
                                                     static_cast<int>(window_->getSize().y)));

    window_->draw(startSprite);
    window_->display();

    sf::Event event;
    while (this->windowIsOpen()) {
        while (window_->pollEvent(event)) {
            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Space)
                    return;
                else if(event.key.code == sf::Keyboard::Escape)
                    window_->close();
            }
        }
    }

}

void graphics::Finish () {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(FINISH_AUDIO_PATH))
        return;

    sf::Sound sound(buffer);
    sound.play();
    sf::Texture finishTexture;
    finishTexture.loadFromFile(FINISH_TEXTURE_PATH, sf::IntRect(0, 0, static_cast<int>(window_->getSize().x),
                                                              static_cast<int>(window_->getSize().y)));
    sf::Sprite stopSprite(finishTexture, sf::IntRect((finishTexture.getSize().x - window_->getSize().x) / 2 * 0,
                                                     (finishTexture.getSize().y - window_->getSize().y) / 2 * 0 + 30 * 0,
                                                     static_cast<int>(window_->getSize().x),
                                                     static_cast<int>(window_->getSize().y)));

    window_->draw(stopSprite);
    window_->display();

    sf::Event event;
    while (this->windowIsOpen()) {
        while (window_->pollEvent(event)) {
            if(event.type == sf::Event::KeyPressed)
                if(event.key.code == sf::Keyboard::Space
                        || event.key.code == sf::Keyboard::Escape
                        || event.key.code == sf::Keyboard::Return)
                    return;
        }
    }

}

void graphics::Placement() {
    // Check, if some element try to fly out the window
    for(auto& elem : *elements_) {

        unsigned maxIters = std::max(window_->getSize().x, window_->getSize().y) *
                static_cast<unsigned>(std::ceil(1 / PLACEMENT_MOVE_STEP));

        if(checkOutOfBound_X(elem, 0, false)) {
            unsigned iter = 0;
            while(checkOutOfBound_X(elem, 0, false)) {
                elem->mustMove(sf::Vector2f(PLACEMENT_MOVE_STEP, 0));
                checkIters(++iter, maxIters);
            }
        }

        if(checkOutOfBound_X(elem, window_->getSize().x, true)) {
            unsigned iter = 0;
            while(checkOutOfBound_X(elem, window_->getSize().x, true)) {
                elem->mustMove(sf::Vector2f(-PLACEMENT_MOVE_STEP, 0));
                checkIters(++iter, maxIters);
            }
        }

        if(checkOutOfBound_Y(elem, 0, false)) {
            unsigned iter = 0;
            while(checkOutOfBound_Y(elem, 0, false)) {
                elem->mustMove(sf::Vector2f(0, PLACEMENT_MOVE_STEP));
                checkIters(++iter, maxIters);
            }
        }

        if(checkOutOfBound_Y(elem, window_->getSize().y, true)) {
            unsigned iter = 0;
            while(checkOutOfBound_Y(elem, window_->getSize().y, true)) {
                elem->mustMove(sf::Vector2f(0, -PLACEMENT_MOVE_STEP));
                checkIters(++iter, maxIters);
            }
        }

    }

    for(auto& elem1 : *elements_) {
        for(auto& elem2 : *elements_) {
            if(&elem1 == &elem2)
                continue;

            if(elem2->getGlobalBounds().intersects(elem1->getGlobalBounds())) {
                elem2->Intersect(*elem1, window_->getSize());
                elem1->Intersect(*elem2, window_->getSize());
            }
        }
    }
}

// Update window and graphical elements
void graphics::Update() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    // Set background
    if(background_)
        window_->draw(*background_);

    // Update graphical elements
    for(auto& elem : *elements_) {
        elem->Update(*window_);
    }

    // Display all actions
    window_->display();
}

bool graphics::Clean() {
    // Clear window
    window_->clear();

    bool Continue = true;

    while(Continue) {
        Continue = false;

        for(auto elem = elements_->begin(); elem != elements_->end(); ++elem) {
            if(!(*elem)->getActive()) {
                if((*elem)->getEssential()) {
                    return false;
                }
                else {
                    elements_->erase(elem);

                    Continue = true;

                    break;
                }
            }
        }
    }

    return true;
}


//void graphics::SetElements(std::map<std::string, GrElem *> *elems) {
//    delete elements_;
//    elements_ = elems;
//}

// Update
//void graphics::UpdateWindow() { //sf::Time& elapsed) {
////    window_.setPosition(
////                sf::Vector2i(
////                    window_.getPosition().x + rand() % 10,
////                    window_.getPosition().y + rand() % 10
////                    )
////                );
////    window_.setSize(sf::Vector2u(100 + rand() % 500, 100 + rand() % 500));
////    shape_.setPosition(sf::Vector2f(window_.getPosition().x, window_.getPosition().y));

//    //std::cout << window_->getPosition().x << " " << window_->getPosition().y << std::endl;
////    hero_.move(1, 0);
////    if(elapsed.asMilliseconds() > 200) {
////        hero_.setTextureRect(sf::IntRect((hero_.getTextureRect().left + 50) % (50*6), hero_.getTextureRect().top, 50, 60));
////        elapsed = elapsed.Zero;
////        std::cout << "gg";
////    }

//    window_->clear(sf::Color::Cyan);
//    window_->draw(*windowSprite_);

//    for(auto& elem : *elements_) {
//        elem.second->Actions();
//    }

//    for(auto& elem : *elements_) {

//        while(elem.second->GetPosition().x + elem.second->GetGlobalBounds().width < 0)
//            elem.second->Move(sf::Vector2f(1, 0));

//        while(elem.second->GetPosition().x + elem.second->GetGlobalBounds().width > WINDOW_SIZE)
//            elem.second->Move(sf::Vector2f(-1, 0));

//        while(elem.second->GetPosition().y + elem.second->GetGlobalBounds().height < 0)
//            elem.second->Move(sf::Vector2f(0, 1));

//        while(elem.second->GetPosition().y + elem.second->GetGlobalBounds().height > WINDOW_SIZE)
//            elem.second->Move(sf::Vector2f(0, -1));

//    }

//    for(auto& elem1 : *elements_) {
//        for(auto& elem2 : *elements_) {
//            if(&elem1 == &elem2)
//                continue;

//            if(Intersect(*elem1.second, *elem2.second))
//                MoveApart(*elem1.second, *elem2.second);
//        }
//    }

//    // Updating elements
//    for(auto& elem : *elements_) {
//        elem.second->Update(*window_);
//    }


//    window_->display();
////    texture_.update(window_);
//    //sleep(0.1);
//}


//bool Intersect(const GrElem &elem1, const GrElem &elem2) {
//    return elem1.GetGlobalBounds().intersects(elem2.GetGlobalBounds());
//}


///// Move apart two elements, which intersect (may not, if you want)
//void MoveApart(GrElem &elem1, GrElem &elem2) {
//    if(elem1.GetMoveAbility() == BOUNDARY && elem2.GetMoveAbility() == BOUNDARY) // Support, may be deleted
//        return;
//    if(elem1.GetMoveAbility() + elem2.GetMoveAbility() == PORTAL + HERO)
//        return;
//    if(elem1.GetMoveAbility() == elem2.GetMoveAbility())
//        return;

//    std::cout << "Move apart: " << elem1.GetMoveAbility() << ", " << elem2.GetMoveAbility() << std::endl;
//    std::cout << "Positions:  " << elem1.GetPosition().x << ", " << elem1.GetPosition().y << "; "
//                                << elem2.GetPosition().x << ", " << elem2.GetPosition().y << std::endl;

//    GrElem &el1 = elem1.GetMoveAbility() > elem2.GetMoveAbility() ? elem1 : elem2;
//    GrElem &el2 = elem1.GetMoveAbility() > elem2.GetMoveAbility() ? elem2 : elem1;

//    float LDist = el1.GetGlobalBounds().left - el2.GetGlobalBounds().left + el1.GetGlobalBounds().width;
//    float RDist = el2.GetGlobalBounds().left - el1.GetGlobalBounds().left + el2.GetGlobalBounds().width;
//    float TDist = el1.GetGlobalBounds().top  - el2.GetGlobalBounds().top  + el1.GetGlobalBounds().height;
//    float BDist = el2.GetGlobalBounds().top  - el1.GetGlobalBounds().top  + el2.GetGlobalBounds().height;

//    std::cout << "LDist = " << LDist << " RDist = " << RDist << " TDist = " << TDist << " BDist = " << BDist << std::endl;


//    if(el1.block_ == true) {
//        std::cerr << "Error: Full blocked element!!! Set top as non blocked!" << std::endl;
//        el1.block_.top_ = false;
//    }

//    if(el1.block_.left_  || el2.GetPosition().x <= 0)
//        LDist = std::numeric_limits<float>::max();

//    if(el1.block_.right_ || el2.GetPosition().x >= WINDOW_SIZE - WINDOW_BOUNDS_OFFSET)
//        RDist = std::numeric_limits<float>::max();

//    if(el1.block_.top_   || el2.GetPosition().y <= 0)
//        TDist = std::numeric_limits<float>::max();

//    if(el1.block_.bot_   || el2.GetPosition().y >= WINDOW_SIZE - WINDOW_BOUNDS_OFFSET)
//        BDist = std::numeric_limits<float>::max();


//    float offsetX = 0;
//    float offsetY = 0;

//    std::cout << "LDist = " << LDist << " RDist = " << RDist << " TDist = " << TDist << " BDist = " << BDist << std::endl;

//    if(     LDist <= RDist && LDist <= TDist && LDist <= BDist)
//        offsetX = -1;
//    else if(RDist <= LDist && RDist <= TDist && RDist <= BDist)
//        offsetX = 1;
//    else if(TDist <= LDist && TDist <= RDist && TDist <= BDist)
//        offsetY = -1;
//    else if(BDist <= LDist && BDist <= RDist && BDist <= TDist)
//        offsetY = 1;
//    else {
//        std::cerr << "I do not know what happened!!!" << std::endl;
//        exit(0);
//    }

//    //std::cout << "offset: " << offsetX << " " << offsetY << std::endl;

////    bool XMove = std::abs(XDist) > std::abs(YDist);

////    for(int i = 0; i < 2; i++) {
////        if(XMove) {
////            offsetY = 0;

////            if(XDist > 0 && !el1.block_.right_) {
////                offsetX = 1;
////                break;
////            }
////            else if(!el1.block_.left_) {
////                offsetX = -1;
////                break;
////            }
////            else {
////                XMove = false;
////            }
////        }

////        if(!XMove) {
////            offsetX = 0;
////            if(YDist > 0 && !el1.block_.bot_) {
////                offsetY = 1;
////                break;
////            }
////            else if(!el1.block_.top_){
////                offsetY = -1;
////                break;
////            }
////            else if(i == 1) { // Can't move!
////                std::cerr << "Error: Full blocked element!!! Set top as non blocked!" << std::endl;
////                el1.block_.top_ = false;
////                offsetY = -1;
////            }
////            else
////                XMove = true;
////        }
////    }

//    while (Intersect(el1, el2)) {
//        //std::cout << "Intersect!" << std::endl;
//        el1.Move(sf::Vector2f(offsetX, offsetY));
//    }

//    if(offsetX > 0)
//        el1.block_.left_  = true;
//    if(offsetX < 0)
//        el1.block_.right_ = true;
//    if(offsetY > 0)
//        el1.block_.top_   = true;
//    if(offsetY < 0)
//        el1.block_.bot_   = true;

//    el1.Stop();


//}

void checkIters (unsigned iter, unsigned maxIters) {
    if(iter > maxIters) {
        std::cerr << "Some object is lost (out of window bounds)!" << std::endl;
        exit(0);
    }
}

bool checkOutOfBound_X (GrElem* elem, int bound, bool bigger) {
    int elemCenter = elem->getPosition().x + elem->getGlobalBounds().width / 2;
    if(elemCenter > bound)
        return bigger;
    return !bigger && (elemCenter != bound);
}

bool checkOutOfBound_Y (GrElem* elem, int bound, bool bigger) {
    int elemCenter = elem->getPosition().y + elem->getGlobalBounds().height / 2;
    if(elemCenter > bound)
        return bigger;
    return !bigger && (elemCenter != bound);
}
