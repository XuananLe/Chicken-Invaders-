#ifndef CHICKEN_H
#define CHICKEN_H
#include "CommonFunc.h"
#include "eggs.h"
#define CHICKEN_WIDTH 127
#define CHICKEN_HEIGHT 98


Uint32 CHICKEN_OBJECT_startTicks = 0;
Uint32 CHICKEN_OBJECT_spriteIndex = 0;
const Uint32 CHICKEN_OBJECT_spritetime = 100;
const int CHICKEN_OBJECT_NUMS_FRAME = 4;
const int WING_WIDTH = 59;
const int WING_HEIGHT = 84;

class Chicken
{
protected:
    bool is_dead;
    int CHICKEN_GOT_HIT_LOOPS = 0;
    std::vector<Eggs *> eggs_list;
    SDL_Texture *chicken = NULL;
    SDL_Texture *chicken_wing = Load_IMG("Assets/image/meat.png");
    SDL_Rect wing_rect;
    SDL_Rect rect_;
    SDL_Rect frame_clip[CHICKEN_OBJECT_NUMS_FRAME];

public:
    void re_init_eggs(const int &x_, const int &y_)
    {
        Eggs *eggs = new Eggs();
        eggs->set_rect_pos(x_, y_);
        eggs_list.push_back(eggs);
    }

    Chicken()
    {
        is_dead = false;
        chicken = Load_IMG("Assets/image/chikin.png");
        chicken_wing = Load_IMG("Assets/image/meat.png");

        wing_rect.x = rect_.x;
        wing_rect.y = rect_.y;
        wing_rect.w = 59;
        wing_rect.h = 84;
        rect_.x = 0;
        rect_.y = 0;
        rect_.w = CHICKEN_WIDTH;
        rect_.h = CHICKEN_HEIGHT;
    }

    void set_clips()
    {
        for (int i = 0; i < CHICKEN_OBJECT_NUMS_FRAME; i++)
        {
            frame_clip[i].x = i * CHICKEN_WIDTH;
            frame_clip[i].y = 0;
            frame_clip[i].w = CHICKEN_WIDTH;
            frame_clip[i].h = CHICKEN_HEIGHT;
        }
    }

    void set_rect(const int &x, const int &y)
    {
        rect_.x = x;
        rect_.y = y;
    }

    SDL_Rect get_rect() const { return rect_; }

    void set_is_dead(bool dead) { is_dead = dead; }
    bool get_is_dead() const { return is_dead; }

    SDL_Texture *get_wing_texture() const { return chicken_wing; }

    void set_wing_rect(const int &x, const int &y)
    {
        rect_.x = x;
        rect_.y = y;
    }

    SDL_Rect get_wing_rect() const { return wing_rect; }

    void moving_LTR(const int &VEL)
    {
        if (rect_.x <= SCREEN_WIDTH)
        {
            rect_.x += VEL;
        }
        else
        {
            rect_.x = 0;
        }
    }

    void show()
    {
        if (is_dead == false)
        {
            wing_rect.y = rect_.y;
            wing_rect.x = rect_.x;
            Uint32 currentTicks = SDL_GetTicks();
            if (currentTicks - CHICKEN_OBJECT_startTicks > CHICKEN_OBJECT_spritetime)
            {
                CHICKEN_OBJECT_spriteIndex = (CHICKEN_OBJECT_spriteIndex + 1) % 4;
                CHICKEN_OBJECT_startTicks = currentTicks;
            }
            SDL_Rect des_rect = {rect_.x, rect_.y, CHICKEN_WIDTH, CHICKEN_HEIGHT};
            // re_init_eggs(rect_.x + 20, rect_.y + 20);
            SDL_RenderCopy(renderer, chicken, &frame_clip[CHICKEN_OBJECT_spriteIndex], &des_rect);
        }
        else
        {
        wing_rect.w = WING_WIDTH;
        wing_rect.h = WING_HEIGHT;
        if (wing_rect.y + wing_rect.h <= SCREEN_HEIGHT)
        wing_rect.y += wing_fall;
        SDL_RenderCopy(renderer, chicken_wing, NULL, &wing_rect);
        }
    }

    void play_sound()
    {
        if (is_dead == true)
        {
            Mix_Chunk *CHICKEN_GOT_HIT = Mix_LoadWAV("Assets/sound/Ci1chickenhit.wav");
            int chanel = Mix_PlayChannel(-1, CHICKEN_GOT_HIT, CHICKEN_GOT_HIT_LOOPS);
            if (CHICKEN_GOT_HIT_LOOPS < 1)
            {
                Mix_PlayChannel(-1, CHICKEN_GOT_HIT, CHICKEN_GOT_HIT_LOOPS);
                CHICKEN_GOT_HIT_LOOPS += 1;
            }
            else
            {
                Mix_HaltChannel(chanel);
                return;
            }
        }
    }

    void set_eggs_list(const std::vector<Eggs *> &eggs_list) { this->eggs_list = eggs_list; }
    std::vector<Eggs *> get_eggs_list() const { return eggs_list; }

    void init_ammo(int num_of_ammo)
    {
        for (int i = 0; i < num_of_ammo; i++)
        {
            Eggs *eggs = new Eggs();
            eggs->set_rect_pos(rect_.x + 50, rect_.y + 50);
            eggs->set_width_height(32, 41);
            eggs_list.push_back(eggs);
        }
    }

    ~Chicken()
    {
        if (eggs_list.size() > 0)
        {
            for (int i = 0; i < eggs_list.size(); i++)
            {
                Eggs *eggs = eggs_list.at(i);
                if (eggs != NULL)
                {
                    delete eggs;
                    eggs = NULL;
                }
                eggs_list.clear();
            }
        }
    }

    void render_ammo(const int &x_limit, const int &y_limit)
    {
        for (int i = 0; i < eggs_list.size(); i++)
        {
            Eggs *eggs = eggs_list.at(i);
            if (eggs != NULL)
            {
                if (eggs->get_is_broken() == false)
                {
                    eggs->handle_move(x_limit, y_limit);
                    eggs->render();
                }
                else
                {
                    eggs->set_rect_pos(rect_.x + 50, rect_.y + 50);
                    eggs->set_is_broken(false);
                }
            }
        }
    }

    void free()
    {
        if (chicken != NULL)
        {
            SDL_DestroyTexture(chicken);
            chicken = NULL;
            rect_.x = 9999;
            rect_.y = 9999;
            rect_.w = 0;
            rect_.h = 0;
            wing_rect.x = 9999;
            wing_rect.w = 0;
            wing_rect.h = 0;
            wing_rect.y = 9999;
        }
    }
    void destroy_chicken()
    {
        if (chicken != NULL)
        {
            SDL_DestroyTexture(chicken);
            chicken = NULL;
            rect_.x = 9999;
            rect_.y = 9999;
        }
    }
    void destroy_wing_rect()
    {
        if (chicken_wing != NULL)
        {
            SDL_DestroyTexture(chicken_wing);
            chicken_wing = NULL;
            wing_rect.x = 9999;
            wing_rect.y = 9999;
        }
    }
};
#endif