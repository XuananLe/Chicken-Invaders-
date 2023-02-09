#ifndef CHICKEN_H
#define CHICKEN_H
#include "CommonFunc.h"
#include "eggs.h"
#define CHICKEN_WIDTH 127
#define CHICKEN_HEIGHT 98
class Chicken
{
public:
Chicken()
{
    is_dead = false;
    chicken = Load_IMG("Assets/image/chicken1.png");
    chicken_wing = Load_IMG("Assets/image/meat.png");
    wing_rect.x = rect_.x;
    wing_rect.y = 0;
    wing_rect.w = 59;
    wing_rect.h = 84;
    rect_.x = rand() % SCREEN_WIDTH + CHICKEN_WIDTH;
    rect_.y = 0;
    rect_.w = CHICKEN_WIDTH;
    rect_.h = CHICKEN_HEIGHT;
}

void set_rect(const int &x, const int &y){rect_.x = x; rect_.y = y;}
SDL_Rect get_rect() const {return rect_;}

void set_is_dead(bool dead){is_dead = dead;}
bool get_is_dead() const {return is_dead;}

SDL_Texture* get_wing_texture() const {return chicken_wing;}
void set_wing_rect(const int &x, const int&y)
{
    rect_.x = x;
    rect_.y = y;
}
SDL_Rect get_wing_rect() const {return wing_rect;}

void moving_LTR(const int& VEL)
{
    if(rect_.x <= SCREEN_WIDTH)
    {
        rect_.x += VEL;
    }
    else
    {
        rect_.x = 0;   
    }
}

void render()
{
    if(is_dead == false)
    {
        SDL_RenderCopy(renderer, chicken, NULL, &rect_);
    }
    else 
    {
        wing_rect.w = 59;
        wing_rect.h = 84;
        wing_rect.x = rect_.x;
        if(wing_rect.y + wing_rect.h <= SCREEN_HEIGHT)
        wing_rect.y += wing_fall;
        std::cout << "Chicken.h " << wing_rect.x << " " << wing_rect.y << std::endl;
        SDL_RenderCopy(renderer, chicken_wing, NULL, &wing_rect);
    }
}

void set_eggs_list(const std::vector<Eggs*>& eggs_list){this->eggs_list = eggs_list;}
std::vector<Eggs*> get_eggs_list() const {return eggs_list;}

void init_ammo(int num_of_ammo)
{
    for(int i = 0; i < num_of_ammo; i++)
    {
        Eggs* eggs = new Eggs();
        eggs->set_rect_pos(rect_.x + 50, rect_.y + 50);
        eggs->set_width_height(32, 41);
        eggs_list.push_back(eggs);
    }
}

~Chicken()
{
    if(eggs_list.size() > 0)
    {
        for(int i = 0; i < eggs_list.size(); i++)
        {
            Eggs* eggs = eggs_list.at(i);
            if(eggs != NULL)
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
    for(int i = 0; i < eggs_list.size(); i++)
    {
        Eggs* eggs = eggs_list.at(i);
        if(eggs != NULL)
        {
            if(eggs->get_is_broken() == false)
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
    if(chicken != NULL)
    {
        SDL_DestroyTexture(chicken);
        chicken = NULL;
        rect_.x = -9999;
        rect_.y = -9999;
        rect_.w = 0;
        rect_.h = 0;
        wing_rect.x = 0;
        wing_rect.w = 59;
        wing_rect.h = 84;
        wing_rect.y = 0;
    }
}

protected:
bool is_dead;
std::vector<Eggs*> eggs_list;
SDL_Texture *chicken = NULL;
SDL_Texture* chicken_wing = Load_IMG("Assets/image/meat.png");
SDL_Rect wing_rect;
SDL_Rect rect_;
};
#endif