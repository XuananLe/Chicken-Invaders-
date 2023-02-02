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
    void HandleInputAction();

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
    SDL_Rect frame_clip_[4];

    // input type
    // Input input_type_;
    // luu frame
    int frame_;
    // luu trang thai
    int status_;

    std::vector<AmmoObject *> p_bullet_list_;
};

bool MainObject::LoadIMG(const char *file_path)
{
    bool ret = BaseObject::LoadIMG(file_path);
    if (ret == true)
    {
        // chieu rong cua frame
        // rect_.w la kich co tam anh load vao
        // chia cho 4 vi co 4 frame
        std::cout << "rect_.w: " << rect_.w << std::endl;
        std::cout << "rect_.h: " << rect_.h << std::endl;
        width_frame = rect_.w / 4;
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

    frame_ = 0;
    status_ = -1;
    p_bullet_list_.clear();
}
// set xem tung frame co kich co bao nhieu va vi tri bao nhieu
void MainObject::set_clips()
{
    if (width_frame > 0 && height_frame > 0)
    {
        frame_clip_[0].x = 0;
        frame_clip_[0].y = 0;
        frame_clip_[0].w = width_frame;
        frame_clip_[0].h = height_frame;

        frame_clip_[1].x = width_frame;
        frame_clip_[1].y = 0;
        frame_clip_[1].w = width_frame;
        frame_clip_[1].h = height_frame;

        frame_clip_[2].x = width_frame * 2;
        frame_clip_[2].y = 0;
        frame_clip_[2].w = width_frame;
        frame_clip_[2].h = height_frame;

        frame_clip_[3].x = width_frame * 3;
        frame_clip_[3].y = 0;
        frame_clip_[3].w = width_frame;
        frame_clip_[3].h = height_frame;
    }
}
// hien thi animation
void MainObject::Show()
{
    // rect_.x = x_pos;
    // rect_.y = y_pos;
    if (frame_ >= 3)
    {
        frame_ = 0;
    }
    else
    {
        ++frame_;
    }
    // frame_ = 0;
    //  rect gan nhat
    SDL_Rect *current_clip = &frame_clip_[frame_];
    SDL_Rect renderquad = {rect_.x, rect_.y, width_frame, height_frame};
    SDL_RenderCopy(renderer, p_object_, current_clip, &renderquad);
}

void MainObject::HandleInputAction()
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_MOUSEMOTION)
        {
            int x = 0;
            int y = 0;
            SDL_GetMouseState(&x, &y);
            rect_.x = x - MAINOBJECT_WIDTH / 2;
            rect_.y = y - MAINOBJECT_HEIGHT;
        }
        else if(event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_SPACE:
                std::cout << "Count" << std::endl;
                AmmoObject *p_bullet = new AmmoObject();   
                p_bullet->Set_AmmoType(LASER);
                p_bullet->Set_Can_Move(true);
                p_bullet->Set_AMMO_VEL(12);
                p_bullet->Set_Rect(MainObject::rect_.x + MAINOBJECT_WIDTH / 2, MainObject::rect_.y);
                p_bullet->LoadIMG("/home/xuananle/Documents/PROJECT CHICKEN/Assets/image/arrow.png");
                break;
            }
        }
    }
}

void MainObject::render_ammo_main()
{
    for (int i = 0; i < p_bullet_list_.size(); i++)
    {
        std::cout << "Come here" << std::endl;
        std::vector<AmmoObject *> BULLET;
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
                {
                    BULLET.erase(BULLET.begin() + i);
                    p_bullet_list_ = BULLET;
                }
            }
        }
    }
}
#endif