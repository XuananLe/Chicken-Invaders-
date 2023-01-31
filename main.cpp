#include "CommonFunc.h"
#include "MainObject.h"
#include "BaseObject.h"
// bool InitData()
// {
//     bool success = true;
//     int ret = SDL_Init(SDL_INIT_VIDEO);
//     if(ret < 0) return false;
//     if(window == NULL)
//     {
//     std::cout << "Cannot Create Window" << "\n";
//     return false;
//     }
//     if(renderer == NULL)
//     {
//     std::cout << "Cannot Create Renderer" << "\n";
//     return false;
//     }
//     int imgFlags = IMG_INIT_PNG;
//     if(!(IMG_Init(imgFlags) && imgFlags)){return false;}
//     return success;
// }
BaseObject* g_background = new BaseObject();
MainObject* g_player = new MainObject();
int main(int argc, char* argv[])
{
    std::cout << "Hello World" << "\n";
    //if(!InitData()) return -1;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
    g_background->LoadIMG("Assets/image/background.jpg");
    g_player->LoadIMG("Assets/image/ship1.png");
    g_player->set_clips();
    bool isRuning = true;
    int bkgn_y = 0;
    int count = 0;
    while(isRuning)
    {
        // make the background moving
        count++;
        SDL_Rect renderquad = {0, bkgn_y, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderCopy(renderer, g_background->GetObject(), NULL, &renderquad);
        renderquad = {0, bkgn_y - SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderCopy(renderer, g_background->GetObject(), NULL, &renderquad);
        bkgn_y += 2;
        if(bkgn_y >= SCREEN_HEIGHT) bkgn_y = 0;
        std::cout << count << "\n";
        while(SDL_PollEvent(&event) != 0)
        {
            if(event.type == SDL_QUIT)
            {
                isRuning = false;
                break;
            }
            // press esc to escape
            if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    isRuning = false;
                    break;
                }
            } 
            else if(event.type == SDL_KEYUP)
            {
                g_player->Show();
                break;
            }
        }
        FramePerSecond();
        SDL_RenderPresent(renderer);
    }
}
 
