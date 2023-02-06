#ifndef THREAT_OBJECT_H
#define THREAT_OBJECT_H

#include "CommonFunc.h"
#include "BaseObject.h"
#include "AmmoObject.hpp"
#include "eggs.h"

const int THREAT_FRAME_CLIPS = 4;
Uint32 THREAT_OBJECT_startTicks = 0;
Uint32 THREAT_OBJECT_spriteIndex = 0;
// 100 miliseconds
Uint32 THREAT_OBJECT_spritetime= 100;


class Chicken
{
public:
~Chicken();
Chicken(int _level);
Chicken();

void render();

void set_eggs_list(std::vector<Eggs*> _eggs_list) {eggs_list = _eggs_list;}
std::vector<Eggs*> get_eggs_list() const {return eggs_list;}

void set_rect(const int &x, const int &y, const int &w, const int &h){Rect_.x = x; Rect_.y = y; Rect_.w = w; Rect_.h = h;}
SDL_Rect get_rect() const {return Rect_;}
void set_rect(const int&x, const int&y) {Rect_.x = x; Rect_.y = y;}

void set_level(int _level) {level = _level;}
int get_level() const {return level;}

void set_health(int _health) {health = _health;}
int get_health() const {return health;}

void set_has_key(bool _has_key) {has_key = _has_key;}
bool get_has_key() const {return has_key;}

void set_dead(bool _dead) {dead = _dead;}
bool get_dead() const {return dead;}

void set_just_dead(bool _just_dead) {just_dead = _just_dead;}
bool get_just_dead() const {return just_dead;}

void init_egg();
void handle_and_render_egg(int _level);

void moving_LTR(const int &VEL);

protected:
SDL_Rect  Rect_;
SDL_Texture *chicken = NULL;
std::vector<Eggs*> eggs_list;
int level;
int health;
bool has_key;
bool dead;
bool just_dead;
};
Chicken::Chicken()
{
    Rect_.x = 0;
    Rect_.y = 0;
    Rect_.w = 0;
    Rect_.h = 0;
    level = 1;
    health = 0;
    has_key = false;
    dead = false;
    just_dead = false;       
}
Chicken::Chicken(int _level)
{
    Rect_.x = 0;
    Rect_.y = 0;
    Rect_.w = 127;
    Rect_.h = 98;
    level = _level;
    if(Chicken::level == 1)
    {
        chicken = Load_IMG("Assets/image/chicken1.png");
        // init ammo for this 
        Eggs* eggs_ = new Eggs();
    }
    else if(Chicken::level == 2)
    {
        chicken = Load_IMG("Assets/image/chicken2.png");
    }
    else if(Chicken::level == 3)
    {
        chicken = Load_IMG("Assets/image/chicken3.png");
    }
    else if(Chicken::level == 4)
    {
        chicken = Load_IMG("Assets/image/chicken4.png");
    }
}
Chicken::~Chicken()
{
    SDL_DestroyTexture(chicken);
    chicken = NULL;
}

void Chicken::init_egg()
{
    // eggs da duoc load image
    Eggs* eggs_ = new Eggs();
    eggs_->set_rect_pos(Rect_.x + Rect_.w/2, Rect_.y + Rect_.h/2);
    eggs_->set_width_height(32, 41);
    eggs_->set_egg_speed(5);
    eggs_list.push_back(eggs_);
}

void Chicken::moving_LTR(const int &Chicken_vel)
{
    Rect_.x += Chicken_vel;
    if(Rect_.x >= SCREEN_WIDTH)
    {
        Rect_.x = 0;
    }
} 


void Chicken::handle_and_render_egg(int level)
{
    if(eggs_list.size() > 0)
    {
        for(int i = 0; i < eggs_list.size(); i++)
        {
            Eggs* eggs_ = eggs_list.at(i);
            if(eggs_ != NULL)
            {
                if(eggs_->get_is_broken() == true)
                {
                eggs_->handle_move(SCREEN_WIDTH, SCREEN_HEIGHT);
                eggs_->render();
                }
                else
                {
                   init_egg();
                }
            }
        }
    }
    else
    {
        init_egg();
    }
}
void Chicken::render()
{
    SDL_RenderCopy(renderer,chicken, NULL, &Rect_);
}


#endif
