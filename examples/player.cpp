#include <iostream>
#include <string>
#include "cppsid.h"

int main()
{
    CPPSID::Player player;
    if (player.load("Beyond_the_Zero.sid")) {
        player.info();
        player.play();
        std::cin.get();
        player.stop();
    }
}

