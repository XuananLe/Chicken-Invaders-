#ifndef EGGS_H
#define EGGS_H
#include "CommonFunc.h"
#include "BaseObject.h"
#define EGGS_WIDTH 32
#define EGGS_HEIGHT 41
#define EGGS_BROKEN_WIDTH 76
#define EGGS_BROKEN_HEIGHT 57
class Eggs
{
protected:
    SDL_Rect rect_;
    // SDL_Rect src_rect;
    double egg_speed;
    bool is_broken;
    bool can_move= true;
    int width = EGGS_WIDTH;
    int height = EGGS_HEIGHT;
    SDL_Texture *fine_egg = NULL;
    SDL_Texture *broken_egg = NULL;

public:
        void set_can_move(const bool &can_move)
    {
        Eggs::can_move = can_move;
    }

    bool get_can_move() const
    {
        return can_move;
    }
    void destroy_egg()
    {
        if (fine_egg != NULL)
        {
            SDL_DestroyTexture(fine_egg);
            fine_egg = NULL;
            Eggs::rect_.x = 9999;
            Eggs::rect_.y = 9999;
        }
        if (broken_egg != NULL)
        {
            SDL_DestroyTexture(broken_egg);
            broken_egg = NULL;
            Eggs::rect_.x = 9999;
            Eggs::rect_.y = 9999;
        }
    }


    Eggs()
    {
        rect_ = {0, 0, 0, 0};
        // src_rect = {0, 0, 0, 0};
        egg_speed = 5;
        can_move = true;
        is_broken = false;
        fine_egg = Load_IMG("/home/xuananle/Documents/PROJECT_CHICKEN/Assets/image/egg.png"); 
        broken_egg = Load_IMG("Assets/image/egg2.png");
    }
    void set_width_height(const int& width, const int&height)
    {
        rect_.w = width;
        rect_.h = height;
    }
    void set_rect_pos(const int &x, const int &y)
    {
        rect_.x = x;
        rect_.y = y;
    }
    SDL_Rect get_rect() const { return rect_; }

    
    void set_egg_speed(double speed) { egg_speed = speed; }

    double get_egg_speed() { return egg_speed; }

    bool get_is_broken() { return is_broken; }
    void set_is_broken(bool broken) { is_broken = broken; }

    SDL_Texture *get_broken_egg() { return broken_egg; }
    SDL_Texture *get_fine_egg() { return fine_egg; }

    void handle_move(const int &x_border, const int &y_border)
    {
        if(is_broken == false) rect_.y += egg_speed;
        // WARNING MAGIC NUMBER
        if (rect_.y >= 1000 + 31)
        {
            is_broken = true;
        }
    }
    void render()
    {
        if (is_broken == true)
        {
            rect_.w = 76;
            rect_.h = 57;
            SDL_RenderCopy(renderer, broken_egg, NULL, &rect_);
        }
        else
        {
            rect_.w = 32;
            rect_.h = 41;
            SDL_RenderCopy(renderer, fine_egg, NULL, &rect_);
        }
    }
};
#endif