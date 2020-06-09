#include "graphics.h"
#include "hero.h"

#include <iostream>
#include <unistd.h>

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

graphics::graphics(std::map<std::string, GrElem*> &elements) :
    window_(new sf::RenderWindow(sf::VideoMode(800, 800), "SFML works!")),
    PosChangeMax_(1000),
    PosChange_(0),
    elements_(elements)
//    hero_(sf::Vector2f(window_->getSize().x / 2, window_->getSize().y / 2)),
    {

    std::cout << "List of graphical elements:" << std::endl;
    for(auto &elem : elements_) {
        std::cout << elem.first << std::endl;
    }

    // Init window
    window_->setPosition(sf::Vector2i(0, 0));
    window_->setFramerateLimit(60);         // One of!
    //window_.setVerticalSyncEnabled(true); // One of!

    // Init graphical elements
    elements_.at("Hero")->SetPosition(sf::Vector2f(window_->getSize().x / 2, window_->getSize().y / 2));
    elements_.at("Boundary_1")->SetPosition(sf::Vector2f(window_->getSize().x / 2, window_->getSize().y / 2 + 100));

    //hero_.setColor(sf::Color(255, 0, 0));
    //window_->draw(hero_.GetSprite());
    this->UpdateWindow();
}

graphics::~graphics() {
    delete window_;
}

// Accessors
bool graphics::WindowOpen() const {
    return window_->isOpen();
}

bool graphics::WindowPoolEvent(sf::Event &event) {
    return window_->pollEvent(event);
}

//void graphics::HeroMove(const sf::Vector2f& offset) {
//    hero_.SpriteMove(offset);
//}

//void graphics::HeroStop() {
//    hero_.SpriteStop();
//}

void graphics::CloseWindow() {
    window_->close();
}

// Update
void graphics::UpdateWindow() { //sf::Time& elapsed) {
//    window_.setPosition(
//                sf::Vector2i(
//                    window_.getPosition().x + rand() % 10,
//                    window_.getPosition().y + rand() % 10
//                    )
//                );
//    window_.setSize(sf::Vector2u(100 + rand() % 500, 100 + rand() % 500));
//    shape_.setPosition(sf::Vector2f(window_.getPosition().x, window_.getPosition().y));

    //std::cout << window_->getPosition().x << " " << window_->getPosition().y << std::endl;
//    hero_.move(1, 0);
//    if(elapsed.asMilliseconds() > 200) {
//        hero_.setTextureRect(sf::IntRect((hero_.getTextureRect().left + 50) % (50*6), hero_.getTextureRect().top, 50, 60));
//        elapsed = elapsed.Zero;
//        std::cout << "gg";
//    }

    window_->clear(sf::Color::Cyan);

    for(auto& elem1 : elements_) {
        for(auto& elem2 : elements_) {
            if(&elem1 == &elem2)
                continue;

            if(Intercepts(elem1, elem2))
                PushOff(elem1, elem2);
        }
    }

    // Updating elements
    for(auto& elem : elements_) {
        elem.second->Update(*window_);
    }


    window_->display();
//    texture_.update(window_);
    //sleep(0.1);
}

GrElem::~GrElem() {}

Boundary::Boundary(int type, sf::Shape* shape, sf::Texture* texture) :
    type_(type),
    shape_(shape),
    texture_(texture) {}

void Boundary::SetPosition(const sf::Vector2f &position) {
    shape_->setPosition(position);
}

sf::Vector2f Boundary::GetPosition() const {
    return shape_->getPosition();
}

sf::FloatRect Boundary::GetGlobalBounds() const {
    return shape_->getGlobalBounds();
}

int Boundary::Update(sf::RenderTarget &target) {
    this->Draw(target);
    return 0;
}

int Boundary::Draw(sf::RenderTarget &target) {
    target.draw(*shape_);
    return 0;
}

bool Boundary::EventHendler(const sf::Event &event) {
    return false;
}

//const sf::Vector2f Boundary::is() const {
//    return
//}

bool Intersect(const GrElem &elem1, const GrElem &elem2) {

}
