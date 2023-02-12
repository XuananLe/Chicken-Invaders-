#include "CommonFunc.h"
#include "MainObject.h"
#include "BaseObject.h"
#include "Present.h"
#include "Chicken.h"
#include "eggs.h"
// #include <emscripten.h>
BaseObject *g_background = new BaseObject();

Present *g_present = new Present();

MainObject *g_player = new MainObject();

Eggs *eggs = new Eggs[1000];

Chicken *chicken = new Chicken[NUM_THREAT];

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

int main(int argc, char *argv[])
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    
    
    Mix_Music *MENU_MUSIC = Mix_LoadMUS("Assets/sound/MENU_THEME.mp3");
    Mix_PlayMusic(MENU_MUSIC, -1);
    
    Mix_Chunk *CHICKEN_GOT_HIT = Mix_LoadWAV("Assets/sound/Ci1chickenhit.wav");

    srand(time(NULL));
    if (!InitData())
        return -1;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");

    int x_pos = 100;
    int ypos = 0;
    for (int i = 0; i < NUM_THREAT; i++)
    {
        chicken[i].set_clips();
        chicken[i].set_rect(x_pos, 300);
        x_pos += 200;
    }

    for (int i = 0; i < NUM_THREAT; i++)
    {
        chicken[i].init_ammo(1);
    }

    g_background->LoadIMG("Assets/image/background(2).jpg");


    g_player->LoadIMG("Assets/image/ship1.png");
    g_player->SetRect(MAINOBJECT_WIDTH, MAINOBJECT_HEIGHT);
    g_player->set_clips();
    g_player->set_width_frame(MAINOBJECT_WIDTH);
    g_player->set_height_frame(MAINOBJECT_HEIGHT);

    bool isRuning = true;
    int bkgn_y = 0;
    int count = 0;
    while (isRuning)
    {
        /// BACKGROUND MOVING  //
        SDL_Rect renderquad = {0, bkgn_y, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderCopy(renderer, g_background->GetObject(), NULL, &renderquad);
        renderquad = {0, bkgn_y - SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderCopy(renderer, g_background->GetObject(), NULL, &renderquad);
        bkgn_y += 1;
        if (bkgn_y >= SCREEN_HEIGHT)
            bkgn_y = 0;



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
        for (int i = 0; i < NUM_THREAT; i++)
        {
            if (chicken[i].get_is_dead() == false)
            {
                // chicken[i].moving_LTR(1);
                chicken[i].render_ammo(SCREEN_WIDTH, SCREEN_HEIGHT);
            }
            chicken[i].play_sound();
            chicken[i].show();
        }
        Mix_ResumeMusic();
        //Mix_PlayChannel(-1, CHICKEN_GOT_HIT, 100);
        g_player->Show();
        g_player->process_collision(chicken);
        g_player->render_ammo_main();
        g_player->make_sound_when_get_food(chicken);

        SDL_RenderPresent(renderer);
    }
}
