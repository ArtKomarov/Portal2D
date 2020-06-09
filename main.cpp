#include <iostream>

#include <SFML/Audio.hpp>

#include "graphics.h"
#include "manager.h"

const char* AUDIO_PATH = "/home/artem/Main/Games/Portal2-04-The_Courtesy_Call.ogg";

int main() {
    Manager manager;

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(AUDIO_PATH))
        return -1;

    sf::Sound sound(buffer);
    sound.setLoop(true);
    sound.play();

    manager.GameLoop();
    return 0;
}
