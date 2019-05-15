#include "cppsid.h"
#include <string>
#include <iostream>

/*
 * Simple use-example for cppsid c++ wrapper
 */
int main()
{
    CPPSID::Player player;
    if (player.load("Beyond_the_Zero.sid")) {
        player.info();
        player.start();
        std::cin.get();
        player.stop();
    }
}

