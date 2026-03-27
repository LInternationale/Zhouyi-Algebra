// Environment Yuxi Palace needed

// 离九霄而膺天命
// 情何以堪
// 御四海而哀苍生
// 心为之伤

#include "suangua.h"
#include "zhouyi_algebra.h"

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#ifdef _WIN32
#include <windows.h>
#define SLEEP(x) Sleep((x) * 1000)
#else
#include <unistd.h>
#define SLEEP(x) sleep(x)
#endif

Mix_Chunk *qing_sound = NULL;

void init_audio() {

    if (SDL_WasInit(SDL_INIT_AUDIO) != 0) return;

    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    qing_sound = Mix_LoadWAV("./qing.wav");
    if (!qing_sound) {
        printf("玉磬被严嵩贪没了...\n");
    }
}

void cleanup_audio() {
    if (qing_sound) {
        Mix_FreeChunk(qing_sound);
        qing_sound = NULL;
    }
    Mix_CloseAudio();
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
}


unsigned char divine_half(const char* name) {
    printf("击玉磬，清音起，步罡踏斗演%s...\n", name);
    int duration = (rand() % 8) + 8;

    if (qing_sound) {
        int channel = Mix_PlayChannel(-1, qing_sound, 0);
        if (channel != -1) {
            Mix_FadeOutChannel(channel, duration * 1000 + 500);
        }
    }

    int counter = 0;
    while (counter < duration) {
        counter++;
        printf(".");
        fflush(stdout);
        SLEEP(1);
    }

    Mix_HaltChannel(-1);

    unsigned char tri = counter % 8;
    printf("\n音息，步停于位，得卦%s\n\n", get_trigram_name(tri));
    return tri;
}

gua suan_gua() {
    srand((unsigned int)time(NULL));

    init_audio();

    unsigned char upper = divine_half("上卦");
    unsigned char lower = divine_half("下卦");

    unsigned char val = (upper << 3) | lower;
    printf("天机已现...\n");

    cleanup_audio();

    return make_gua(val);
}