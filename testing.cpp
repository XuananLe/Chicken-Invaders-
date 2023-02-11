//#include <SFML/Window.hpp>
#include <iostream>
//#include "eggs.h"
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include "CommonFunc.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "Present.h"
#include "Chicken.h"

int main(int argc, char *argv[])
{
    BaseObject* g_background = new BaseObject();
    
    
    g_background->LoadIMG("Assets/image/background(2).jpg");
    g_background->set_width_height(SCREEN_WIDTH, SCREEN_HEIGHT);
    g_background->Set_Rect(0,0,SCREEN_WIDTH, SCREEN_HEIGHT);
    
    Chicken *ga = new Chicken();
    ga->set_clips();

    bool isRuninng = true;
    while(isRuninng)
    {
        FramePerSecond();
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                isRuninng = false;
            }
        }
        g_background->Render();
        ga->show();
        SDL_RenderPresent(renderer);
    }
}