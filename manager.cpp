#include <iostream>
#include <utility>

#include "manager.h"
#include "graphics.h"


//Manager::Manager(sf::Texture* GlobalTexture, Hero* hero,
//                 std::map<const char*, Boundary*>* boundaries, std::map<std::string, GrElem *> *grElements,
//                 sf::Sprite *windowSprite, unsigned int WindowSize) :
//    hero_(hero),
//    boundaries_(boundaries),
//    gr_(new graphics(grElements, GlobalTexture, windowSprite, WindowSize)),
//    clock_() {
//}

Manager::Manager (std::vector<GrElem*>* graphicalElems, std::vector<PhysElem*>* physicalElems, sf::RenderWindow *window, sf::Sprite* background) :
    graphics_(window, background, graphicalElems),
    physics_ (physicalElems) {
}

Manager::~Manager() {
//    delete graphics_;
//    delete physics_;
}

void Manager::gameLoop() {
    //sf::Time elapsed;
    //bool HeroRun; // Did hero run in this loop?

    graphics_.Start();

    physics_.Start();

    while (graphics_.windowIsOpen()) {
        // Make activites, set speed, other
        physics_.Activities();

        // Make all movement
        physics_.Movement();

        // Event handling
        this->eventHandling();

        // place objects in ptoper places + handle intercepting
        graphics_.Placement();

        // Clear windowm erase inactive elements
        if(graphics_.Clean()) {
            // Update (draw) all graphical elements
            graphics_.Update();
        }
        else {
            // Close, if some elements are essential, and can't be cleaned
            //graphics_.closeWindow();
            break;
        }
    }

    graphics_.Finish();
}

void Manager::eventHandling() {
    sf::Event event;

    while (graphics_.windowPoolEvent(event)) {
        switch (event.type) {

        case sf::Event::Closed:
            graphics_.closeWindow();
            return;

        case sf::Event::KeyPressed:
            if(event.key.code == sf::Keyboard::Escape) {
                graphics_.closeWindow();
                return;
            }
            break;

        default:
            physics_.eventHandling(event, graphics_.getMousePosition());
        }
    }
}



//        while (graphics_.windowPoolEvent(event)) {
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
//            if(hero_->EventHendler(event))
//                continue;
//            if(gr_->EventHendler(event))
//                continue;
//            if(event.type == sf::Event::KeyPressed) {
//                if(event.key.code == sf::Keyboard::Escape)
//                    gr_->CloseWindow();
//            }
//            else if(event.type == sf::Event::Closed) {
//                gr_->CloseWindow();
//            }

//        }

//        elapsed += clock_.restart();
//        gr_->UpdateWindow(); //elapsed);
//    }
//}

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
