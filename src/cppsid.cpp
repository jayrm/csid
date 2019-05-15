#include <iostream>
#include <fstream>
#include <vector>

#include <fcntl.h>
#include <cstdio>
#include <unistd.h>

#include <SDL_config.h>
#include <SDL.h>
#include <SDL_audio.h>

#include "cppsid.h"

extern "C" {
#include <libcsid.h>
}

namespace CPPSID {
    void Player::sdl_callback(void* userdata, unsigned char *stream, int bytes) {
        libcsid_render((unsigned short *)stream, bytes / 2);
    }

    Player::Player() {
        soundspec = std::make_shared<SDL_AudioSpec>(SDL_AudioSpec({0, }));
        VERBOSE = false;
        int samplerate = DEFAULT_SAMPLERATE;
        int subtune = 0;
        int sidmodel = DEFAULT_SIDMODEL;
        int tunelength = -1;
        if (SDL_Init(SDL_INIT_AUDIO) < 0) {
            throw std::runtime_error("error initializing SDL");
        }

        //SDL_AudioSpec soundspec = {0, };
        soundspec->freq = samplerate;
        soundspec->channels = 1;
        soundspec->format = AUDIO_S16;
        soundspec->samples = 32768;
        soundspec->userdata = nullptr;
        soundspec->callback = sdl_callback;
        if (SDL_OpenAudio(soundspec.get(), nullptr) < 0) {
            throw std::runtime_error("could not open audio");
        }

        libcsid_init(samplerate, sidmodel);
    }

    bool Player::load(const std::string &file) {
        std::ifstream f(file.c_str(), std::ifstream::ate | std::ios::binary);
        if (f) {
            size_t size = f.tellg();
            f.seekg(0, f.beg); // go back to beginning
            std::vector<unsigned char> buffer(size);
            f.read((char*)buffer.data(), size);
            f.close();

            libcsid_load(buffer.data(), size, subtune);
            return true;
        }
        else
            std::cerr << "could not load SID file" << std::endl;
        return false;
    }

    void Player::info() {
        std::cout << "title:  " << libcsid_gettitle() << std::endl
            << "author: " << libcsid_getauthor() << std::endl
            << "info:   " << libcsid_getinfo() << std::endl;
    }

    void Player::play() {
        SDL_PauseAudio(0);
    }

    void Player::stop() {
        SDL_PauseAudio(1);
        SDL_CloseAudio();
    }
}//namespace
