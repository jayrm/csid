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
            int sdl_device;
            std::shared_ptr<SDL_AudioSpec> soundspec;
            std::vector<unsigned char> buffer; // buffer for sid data
            int samplerate;
            int sidmodel;
            bool is_playing;
            static void sdl_callback(void*, unsigned char*, int);
        public:
            Player();
            ~Player();
            bool load(const std::string&, int=0); //!< load SID file
            std::string title(); //!< get title
            std::string author(); //!< get author
            std::string info(); //!< get info
            void start(); //!< start playing
            void stop(); //!< stop playing
    };
}//namespace
