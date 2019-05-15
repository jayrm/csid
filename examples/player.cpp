#include "cppsid.h"
#include <string>
#include <iostream>

/*
 * Simple use-example for cppsid c++ wrapper
 */
int main()
{
    CPPSID::Player player;
    int subsong = 0;
    std::string file = "Beyond_the_Zero.sid";

    if (player.load(file, subsong)) {

        std::cout << "title:  " << player.title() << std::endl
            << "author: " << player.author() << std::endl
            << "info:   " << player.info() << std::endl;

        player.start();
        std::cin.get();
        player.stop();
    }
}

