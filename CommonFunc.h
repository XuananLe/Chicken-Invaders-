#ifndef COMMON_FUNC_H
#define COMMON_FUNC_H
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_ttf.h>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;
const Uint64 FrameStart = SDL_GetTicks64();
const int frameTime = SDL_GetTicks64() - FrameStart;
static SDL_Window *window = SDL_CreateWindow("Welcome to my first game",
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        SCREEN_WIDTH, 
        SCREEN_HEIGHT,
        SDL_WINDOW_FULLSCREEN_DESKTOP);
const int FPS = 60;
const int frameDelay = 1000 / FPS;
static void FramePerSecond()
{
    if (frameDelay > FrameStart)
    {
        SDL_Delay(frameDelay - FrameStart);
    }
}
static SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
static SDL_Event event;
typedef struct Input
{
    int left_;
    int right_;
    int up_;
    int down_;
    bool is_Moving = true;
} Input; 

#endif