#include <SFML/Window.hpp>
#include <iostream>
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include "CommonFunc.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "Present.h"
int main(int argc, char*argv[])
{
    BaseObject* base = new BaseObject();
    base->LoadIMG("Assets/image/background(2).jpg");
    BaseObject* something = new BaseObject();
    something->LoadIMG("Assets/image/gift.png");
    something->set_width_height(100, 100);
    something->Set_Rect(100, 0);
    int count = 0;

    bool isRunning = true;
    while(isRunning)
    {
        FramePerSecond();
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    isRunning = false;
                    break;
            }
        }
        base->Render();
        something->Render(count);
        SDL_RenderPresent(renderer);
    }    
}