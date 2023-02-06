#include "CommonFunc.h"
#include "MainObject.h"
#include "BaseObject.h"
#include "Present.h"
#include "eggs.h"
#include <emscripten.h>
bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
        return false;
    if (window == NULL)
    {
        std::cout << "Cannot Create Window"
                  << "\n";
        return false;
    }
    if (renderer == NULL)
    {
        std::cout << "Cannot Create Renderer"
                  << "\n";
        return false;
    }
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) && imgFlags))
    {
        return false;
    }
    return success;
}
BaseObject *g_background = new BaseObject();

Present *g_present = new Present();

MainObject *g_player = new MainObject();


int main(int argc, char *argv[])
{
    if (!InitData())
        return -1;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
    g_background->LoadIMG("Assets/image/background(2).jpg");
    
    // g_present init
    g_present->LoadIMG("Assets/image/AtomicPower.png");
    //std::cout << g_present->GetRect().x << "\t" << g_present->GetRect().y << "\t" << g_present->GetRect().w << "\t" << g_present->GetRect().h << "\t" << std::endl;
    g_present->set_width_height(50, 50);
    g_present->Set_Rect(100,0);
    g_present->Set_Can_Move(true);
    

    g_player->LoadIMG("Assets/image/ship1.png");
    g_player->SetRect(MAINOBJECT_WIDTH, MAINOBJECT_HEIGHT);
    g_player->set_clips();
    // chinh lai width va height cua player frame thay vi 512 x 512
    g_player->set_width_frame(MAINOBJECT_WIDTH);
    g_player->set_height_frame(MAINOBJECT_HEIGHT);
    // setting init position
    g_player->SetRect(SCREEN_WIDTH/2, 600);
    
    
    
    bool isRuning = true;
    int bkgn_y = 0;
    int count = 0;
    while (isRuning)
    {
        // make the background moving
        // count++;
        // std::cout << count << "\n";
        //FramePerSecond();
        //std::cout << g_present->GetRect().x << " " << g_present->GetRect().y << std::endl;
        // khien background di chuyen
        SDL_Rect renderquad = {0, bkgn_y, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderCopy(renderer, g_background->GetObject(), NULL, &renderquad);
        renderquad = {0, bkgn_y - SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderCopy(renderer, g_background->GetObject(), NULL, &renderquad);
        bkgn_y += 1;
        if (bkgn_y >= SCREEN_HEIGHT)    bkgn_y = 0;


        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                isRuning = false;
                break;
            }
            // press esc to escape
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    isRuning = false;
                    break;
                }
            }
            g_player->HandleInputAction(event);
        }
        
        g_present->Move();
        g_present->Render();
        //std::cout << g_present->GetRect().x << " " << g_present->GetRect().y << std::endl;
        g_player->Show();
        g_player->render_ammo_main();
        SDL_RenderPresent(renderer);
    }
    // std::cout << g_player->GetRect().x << "\t" << g_player->GetRect().y << "\t" << g_player->GetRect().w << "\t" << g_player->GetRect().h << "\t" << std::endl;
}
