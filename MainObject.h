#include "CommonFunc.h"
#include "BaseObject.h"
#include "AmmoObject.hpp"
#ifndef MAINOBJECT_H_
#define MAINOBJECT_H_

class MainObject : public BaseObject
{
public:
    MainObject();
    ~MainObject() {}
    // virtual at this,
    bool LoadIMG(const char *file_path);
    // SHOW THEO DANG FRAME CHU KHONG CHI RENDER COPY
    void Show();
    void HandleInputAction(SDL_Event event);

    // xu li animation
    void set_clips();
    // get width frame and height frame
    int get_width_frame() const { return width_frame; }
    int get_height_frame() const { return height_frame; }
    // set width frame and height frame
    void set_width_frame(const int &width) { width_frame = width; }
    void set_height_frame(const int &height) { height_frame = height; }

    void render_ammo_main();

    void set_bullet_list(std::vector<AmmoObject *> bullet_list) { p_bullet_list_ = bullet_list; }
    std::vector<AmmoObject *> get_bullet_list() const { return p_bullet_list_; }

protected:
    int x_pos;
    int y_pos;
    int x_val_;
    int y_val_;
    // kich co cua frame
    int width_frame;
    int height_frame;
    SDL_Rect frame_clip_[MAIN_OBJECT_NUMS_FRAME];

    // input type
    // Input input_type_;
    // luu frame
    //int frame_;
    // luu trang thai
    int status_;

    std::vector<AmmoObject *> p_bullet_list_;
};

bool MainObject::LoadIMG(const char *file_path)
{
    bool ret = BaseObject::LoadIMG(file_path);
    if (ret == true)
    {
        // chieu rong cua fram e
        // rect_.w la kich co tam anh load vao
        // chia cho 4 vi co 4 frame
        std::cout << "rect_.w: " << rect_.w << std::endl;
        std::cout << "rect_.h: " << rect_.h << std::endl;
        width_frame = rect_.w / MAIN_OBJECT_NUMS_FRAME;
        height_frame = rect_.h;
        std::cout << "width_frame: " << width_frame << std::endl;
        std::cout << "height_frame: " << height_frame << std::endl;
    }
    return ret;
}
MainObject::MainObject()
{
    x_val_ = 0;
    y_val_ = 0;
    x_pos = 0;
    y_pos = 0;

    width_frame = 0;
    height_frame = 0;

    //frame_ = 0;
    status_ = -1;
    p_bullet_list_.clear();
}
// set xem tung frame co kich co bao nhieu va vi tri bao nhieu
void MainObject::set_clips()
{
    if (width_frame >= 0 && height_frame >= 0)
    {
        for(int i = 0; i < MAIN_OBJECT_NUMS_FRAME; i++)
        {
            frame_clip_[i].x = i * width_frame;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = width_frame;
            frame_clip_[i].h = height_frame;
        }
    }
}
// hien thi animation
void MainObject::Show()
{
    Uint32 currentTicks = SDL_GetTicks();
    if (currentTicks - MAIN_OBJECT_startTicks > MAIN_OBJECT_spritetime)
    {
        MAIN_OBJECT_spriteIndex = (MAIN_OBJECT_spriteIndex + 1) % 4;
        MAIN_OBJECT_startTicks = currentTicks;
    }
    SDL_Rect destRect = {rect_.x, rect_.y, width_frame, height_frame};

    // Render the current sprite
    SDL_RenderCopy(renderer,p_object_, &frame_clip_[MAIN_OBJECT_spriteIndex], &destRect);
}

void MainObject::HandleInputAction(SDL_Event event)
{
    if (event.type == SDL_MOUSEMOTION)
    {
        int x = 0;
        int y = 0;
        SDL_GetMouseState(&x, &y);
        rect_.x = x - MAINOBJECT_WIDTH / 2;
        rect_.y = y - MAINOBJECT_HEIGHT;
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        AmmoObject *p_bullet = new AmmoObject();
        p_bullet->Set_AmmoType(LASER);
        p_bullet->Set_Can_Move(true);
        p_bullet->set_width_height(LASER_WIDTH, LASER_HEIGHT);
        p_bullet->Set_AMMO_VEL(LASER_VEL);
        p_bullet->Set_Rect(MainObject::rect_.x + MAINOBJECT_WIDTH / 2, MainObject::rect_.y);
        p_bullet->LoadIMG("Assets/image/arrow.png");
        p_bullet_list_.push_back(p_bullet);
    }
    else if (event.type == SDL_KEYDOWN)
    {
        
    }
}

void MainObject::render_ammo_main()
{
    if (p_bullet_list_.size() > 0)
    {
        for (int i = 0; i < p_bullet_list_.size(); i++)
        {
            // std::cout << "Come here" << std::endl;
            std::vector<AmmoObject *> BULLET = p_bullet_list_;
            AmmoObject *p_bullet = BULLET.at(i);
            if (p_bullet != NULL)
            {
                if (p_bullet->Get_Can_Move() == true)
                {
                    p_bullet->Handle_Input_Action_BTU(SCREEN_WIDTH, SCREEN_HEIGHT);
                    p_bullet->Render();
                }
                else
                {
                    if (p_bullet != NULL)
                        BULLET.erase(BULLET.begin() + i);
                    p_bullet_list_ = BULLET;
                }
            }
        }
    }
}
#endif