//#include <SFML/Window.hpp>
#include <iostream>
//#include "eggs.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
// #include "CommonFunc.h"
// #include "BaseObject.h"
// #include "MainObject.h"
// #include "Present.h"
// #include "Chicken.h"

int main(int argc, char *argv[])
{
    //BaseObject* g_background = new BaseObject();
    // while(true)
    // std::cout << SDL_GetTicks64() << std::endl;
    
    // g_background->LoadIMG("Assets/image/background(2).jpg");
    // g_background->set_width_height(SCREEN_WIDTH, SCREEN_HEIGHT);
    // g_background->Set_Rect(0,0,SCREEN_WIDTH, SCREEN_HEIGHT);
    
    // Chicken *ga = new Chicken();
    // ga->set_clips();

    // bool isRuninng = true;
    // while(isRuninng)
    // {
    //     FramePerSecond();
    //     while(SDL_PollEvent(&event))
    //     {
    //         if(event.type == SDL_QUIT)
    //         {
    //             isRuninng = false;
    //         }
    //     }
    //     g_background->Render();
    //     ga->show();
    //     SDL_RenderPresent(renderer);
    // }
    // int result = Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 );
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 );
    int SCREEN_WIDTH = 800;
    int SCREEN_HEIGHT = 600;
    SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    Mix_Music* music = Mix_LoadMUS("Assets/sound/THEME.mp3");
    Mix_PlayMusic(music, -1);
    SDL_Event event;
    bool isRunning = true;
    while(isRunning)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                isRunning = false;
            }
            Mix_ResumeMusic();
        }
    }
}