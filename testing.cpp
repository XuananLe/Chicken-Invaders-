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
    Eggs * eggs = new Eggs();
    eggs->set_width_height(32,41);
    eggs->set_rect_pos(100,100);
    eggs->set_is_broken(false);

    Chicken* GA = new Chicken(1);
    GA->init_egg();
    
    g_background->LoadIMG("Assets/image/background(2).jpg");
    g_background->set_width_height(SCREEN_WIDTH, SCREEN_HEIGHT);
    g_background->Set_Rect(0,0,SCREEN_WIDTH, SCREEN_HEIGHT);
    

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
        SDL_RenderPresent(renderer);
    }
}