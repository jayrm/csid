#pragma once

#include <string>
#include <memory>

class SDL_AudioSpec;

namespace CPPSID {
    class Player {
        private:
            std::shared_ptr<SDL_AudioSpec> soundspec;
            int samplerate;
            int subtune = 0;
            int sidmodel;
            int tunelength = -1;
            static void sdl_callback(void*, unsigned char*, int);
        public:
            Player();
            bool load(const std::string&);
            void info();
            void play();
            void stop();
    };
}//namespace
