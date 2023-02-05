#ifndef COMMON_FUNC_H
#define COMMON_FUNC_H
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_ttf.h>


#define NONE 1
#define ION 2
#define DOUBLE_ION 3
#define LASER 4

#define LASER_WIDTH 12
#define LASER_HEIGHT 12
#define ION_WIDTH 12
#define ION_HEIGHT 12


//const int MAGIC_NUMBER = 100;
 
Uint32 MAIN_OBJECT_startTicks = 0;
Uint32 MAIN_OBJECT_spriteIndex = 0;
Uint32 MAIN_OBJECT_spritetime= 100;
const int MAIN_OBJECT_NUMS_FRAME = 4;

const int MAINOBJECT_WIDTH = 200;
const int MAINOBJECT_HEIGHT = 200;
const int MAINOBJECT_VEL = 10;

static const int PRESENT_VEL = 3;
static const int PRESENT_SPIN_VEL = 5;

const int THREAT_OBJECT_WIDTH = 400;
const int THREAT_OBJECT_HEIGHT = 400;

const int LASER_VEL = 12;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const Uint64 FrameStart = SDL_GetTicks64();
const int frameTime = SDL_GetTicks64() - FrameStart;
const int FPS = 30;
const int frameDelay = 1000 / FPS;

static SDL_Window *window = SDL_CreateWindow("Chicken invaders",
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        SCREEN_WIDTH, 
        SCREEN_HEIGHT,
        SDL_WINDOW_RESIZABLE);
static void FramePerSecond()
{
    if (frameDelay > FrameStart)
    {
        SDL_Delay(frameDelay - FrameStart);
    }
}
static SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
static SDL_Event event;

SDL_Texture* Load_IMG(const char* file)
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(file);
    if (loadedSurface == NULL)
    {
        std::cout << "Unable to load image Common func " << file << "! SDL_image Error: " << IMG_GetError() << std::endl;
        exit(0);
    }
    else
    {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL)
        {
            std::cout << "Unable to create texture from Common Func" << file << "! SDL Error: " << SDL_GetError() << std::endl;
            exit(0);
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}


#endif