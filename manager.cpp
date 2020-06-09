#include <iostream>
#include <utility>

#include "manager.h"
#include "graphics.h"

Manager::Manager() :
    hero_(),
    gr_(nullptr),
    clock_() {

    // Create boundaries
    Boundary *b1 = new Boundary(0, new sf::RectangleShape(sf::Vector2f(100, 100)), nullptr);
    boundaries_.insert(std::make_pair("Boundary_1", b1));

    // Set graphical elements
    std::map <std::string, GrElem*> *GrElements = new std::map<std::string, GrElem*>();
    GrElements->insert(std::make_pair("Hero", &hero_));

    for(auto &elem : boundaries_) {
        GrElements->insert(std::make_pair(elem.first, static_cast<GrElem*>(elem.second)));
    }

    // Create graphics module
    gr_ = new graphics(*GrElements);

}

Manager::~Manager() {
    delete gr_;
}

void Manager::GameLoop() {
    sf::Time elapsed;
    //bool HeroRun; // Did hero run in this loop?

    while (gr_->WindowOpen()) {
        sf::Event event;

        while (gr_->WindowPoolEvent(event)) {
//            switch (event.type) {
//            case sf::Event::Closed:
//                gr_.CloseWindow();
//                break;
//            case sf::Event::KeyPressed:
//                KeyPressedHandler(event);
//                break;
//            case sf::Event::KeyReleased:
//                KeyNotPressedHandler();
//                break;
//            default:
//                break;
//            }
            if(hero_.EventHendler(event))
                continue;
            if(event.type == sf::Event::Closed) {
                gr_->CloseWindow();
            }

        }

        elapsed += clock_.restart();
        gr_->UpdateWindow(); //elapsed);
    }
}

//void Manager::KeyPressedHandler(const sf::Event& event) {
//    switch (event.key.code) {
//    case sf::Keyboard::D:
//        gr_.HeroMove(sf::Vector2f(5, 0));
//        break;
//    case sf::Keyboard::A:
//        gr_.HeroMove(sf::Vector2f(-5, 0));
//        break;
//    case sf::Keyboard::W:
//        gr_.HeroMove(sf::Vector2f(0, -10));
//        break;
//    case sf::Keyboard::S:
//        gr_.HeroMove(sf::Vector2f(0, 2));
//        break;
//    case sf::Keyboard::Escape:
//        gr_.CloseWindow();
//        break;
//    default:
//        break;
//    }
//}

//void Manager::KeyNotPressedHandler() {
//    gr_.HeroStop();
//}
