#include <iostream>
#include <utility>

#include "manager.h"
#include "graphics.h"


Manager::Manager(sf::Texture* GlobalTexture, Hero* hero,
                 std::map<const char*, Boundary*>* boundaries, std::map<std::string, GrElem *> *grElements,
                 sf::Sprite *windowSprite, unsigned int WindowSize) :
    hero_(hero),
    boundaries_(boundaries),
    gr_(new graphics(grElements, GlobalTexture, windowSprite, WindowSize)),
    clock_() {
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
            if(hero_->EventHendler(event))
                continue;
            if(gr_->EventHendler(event))
                continue;
            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Escape)
                    gr_->CloseWindow();
            }
            else if(event.type == sf::Event::Closed) {
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
