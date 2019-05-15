#include <iostream>
#include <fstream>
#include <vector>

#include <fcntl.h>
#include <cstdio>
#include <unistd.h>

#include <SDL_config.h>
#include <SDL.h>
#include <SDL_audio.h>

extern "C" {
#include <libcsid.h>
}

int supress_stdout() {
    std::cout << std::flush;
    fflush(stdout);

    int ret = dup(1);
    int nullfd = open("/dev/null", O_WRONLY);
    // check nullfd for error omitted
    dup2(nullfd, 1);
    close(nullfd);

    return ret;
}

void resume_stdout(int fd) {
    fflush(stdout);
    dup2(fd, 1);
    close(fd);
}

void sdl_callback(void* userdata, unsigned char *stream, int bytes) {
    libcsid_render((unsigned short *)stream, bytes / 2);
}

int main()
{
    VERBOSE = false;
    int samplerate = DEFAULT_SAMPLERATE;
    int subtune = 0;
    int sidmodel = DEFAULT_SIDMODEL;
    int tunelength = -1;
    unsigned char filedata[MAX_DATA_LEN] = {0, };

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        throw std::runtime_error("error initializing SDL");
    }

    SDL_AudioSpec soundspec = {0, };
    soundspec.freq = samplerate;
    soundspec.channels = 1;
    soundspec.format = AUDIO_S16;
    soundspec.samples = 32768;
    soundspec.userdata = NULL;
    soundspec.callback = sdl_callback;
    if (SDL_OpenAudio(&soundspec, NULL) < 0) {
        throw std::runtime_error("could not open audio");
    }

    libcsid_init(samplerate, sidmodel);

    std::ifstream f("Beyond_the_Zero.sid", std::ifstream::ate | std::ios::binary);
    if (f) {
        size_t size = f.tellg();
        f.seekg(0, f.beg); // go back to beginning
        std::vector<unsigned char> buffer(size);
        f.read((char*)buffer.data(), size);
        f.close();

        libcsid_load(buffer.data(), size, subtune);

        std::cout << "title:  " << libcsid_gettitle() << std::endl
            << "author: " << libcsid_getauthor() << std::endl
            << "info:   " << libcsid_getinfo() << std::endl;

        SDL_PauseAudio(0);
        std::cin.get();
        SDL_PauseAudio(1);
        SDL_CloseAudio();
    }
}

