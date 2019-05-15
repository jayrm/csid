#include <iostream>
#include <fstream>

#include <SDL_config.h>
#include <SDL.h>
#include <SDL_audio.h>

#include <cppsid.h>

extern "C" {
#include <libcsid.h>
}

namespace CPPSID {
    void Player::sdl_callback(void* userdata, unsigned char *stream, int bytes) {
        libcsid_render((unsigned short *)stream, bytes / 2);
    }

    Player::Player() {
        VERBOSE = false;
        is_playing = false;
        samplerate = DEFAULT_SAMPLERATE;
        sidmodel = DEFAULT_SIDMODEL;
        if (SDL_Init(SDL_INIT_AUDIO) < 0)
            throw std::runtime_error("error initializing SDL");

        soundspec = std::make_shared<SDL_AudioSpec>(SDL_AudioSpec({0, }));
        soundspec->freq = samplerate;
        soundspec->channels = 1;
        soundspec->format = AUDIO_S16;
        soundspec->samples = 32768;
        soundspec->userdata = nullptr;
        soundspec->callback = sdl_callback;

        if (SDL_OpenAudio(soundspec.get(), nullptr) < 0)
            throw std::runtime_error("could not open SDL audio");

        libcsid_init(samplerate, sidmodel);
    }

    bool Player::load(const std::string &file, int subtune) {
        stop();
        std::ifstream f(file.c_str(), std::ifstream::ate | std::ios::binary);
        if (f) {
            size = f.tellg(); // get SID size
            buffer.resize(size); // resize buffer
            f.seekg(0, f.beg); // go back to beginning of file
            f.read((char*)buffer.data(), size); // load sid into buffer
            libcsid_load(buffer.data(), size, subtune);
            return true;
        }
        std::cerr << "could not load SID file" << std::endl;
        return false;
    }

    void Player::info() {
        if (not buffer.empty())
            std::cout << "title:  " << libcsid_gettitle() << std::endl
                << "author: " << libcsid_getauthor() << std::endl
                << "info:   " << libcsid_getinfo() << std::endl;
    }

    void Player::start() {
        if (!buffer.empty() and is_playing==false) {
            SDL_PauseAudio(0);
            is_playing=true;
        }
    }

    void Player::stop() {
        if (is_playing) {
            SDL_PauseAudio(1);
            is_playing=false;
        }
    }

    Player::~Player() {
        stop();
        SDL_CloseAudio();
    }

}//namespace
