#pragma once

#include <string>
#include <vector>
#include <memory>

class SDL_AudioSpec;

namespace CPPSID {
    /**
     * @brief C++ wrapper for the csid code by Kermit
     * @author Mikael Lund
     * @date Malmo, 2019
     */
    class Player {
        private:
            std::shared_ptr<SDL_AudioSpec> soundspec;
            std::vector<unsigned char> buffer; // buffer for sid data
            size_t size; // sid size in bytes
            int samplerate;
            int subtune = 0;
            int sidmodel;
            int tunelength = -1;
            bool is_playing = false;
            bool is_loaded = false;
            static void sdl_callback(void*, unsigned char*, int);
        public:
            Player();
            ~Player();
            bool load(const std::string&, int=0); //!< load SID file
            void info(); //!< show info
            void start(); //!< start playing
            void stop(); //!< stop playing
    };
}//namespace
