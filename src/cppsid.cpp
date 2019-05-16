#include <iostream>
#include <fstream>
#include <SDL.h>
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

        sdl_device = SDL_OpenAudioDevice(nullptr, 0, soundspec.get(), nullptr, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
        if (not sdl_device)
            throw std::runtime_error("could not open SDL audio");

        libcsid_init(samplerate, sidmodel);
    }

    bool Player::load(const std::string &file, int subtune) {
        stop();
        buffer.clear();
        std::ifstream f(file.c_str(), std::ifstream::ate | std::ios::binary);
        if (f) {
            buffer.resize(f.tellg()); // resize buffer (moves f forward)
            f.seekg(0, f.beg); // go back to beginning of file
            f.read((char*)buffer.data(), buffer.size()); // load sid into buffer
            libcsid_load(buffer.data(), buffer.size(), subtune);
            return true;
        }
        std::cerr << "could not load SID file" << std::endl;
        return false;
    }

    std::string Player::author() { return libcsid_getauthor(); }
    std::string Player::title() { return libcsid_gettitle(); }
    std::string Player::info() { return libcsid_getinfo(); }

    void Player::start() {
        if (not buffer.empty()) {
            SDL_PauseAudioDevice(sdl_device, 0);
            is_playing=true;
        }
    }

    void Player::stop() {
        SDL_PauseAudioDevice(sdl_device, 1);
        is_playing=false;
    }

    Player::~Player() {
        stop();
        SDL_CloseAudioDevice(sdl_device);
    }

}//namespace
