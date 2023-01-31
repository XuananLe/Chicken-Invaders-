#include "CommonFunc.h"
#include "BaseObject.h"
#ifndef MAINOBJECT_H_
#define MAINOBJECT_H_
class MainObject : public BaseObject
{
public:
    MainObject();
    ~MainObject(){}
    // virtual at this, 
     bool LoadIMG(const char* file_path);
    // SHOW THEO DANG FRAME CHU KHONG CHI RENDER COPY
    void Show();
    void HandleInputAction(SDL_Event events);
    
    // xu li animation
    void set_clips();
protected:
    int x_pos;
    int y_pos;
    int x_val_;
    int y_val_;
    // kich co cua frame
    int width_frame;
    int height_frame;
    SDL_Rect frame_clip_[4];
    Input input_type_;
    // luu frame
    int frame_;
    // luu trang thai
    int status_;
};
bool MainObject::LoadIMG(const char* file_path)
{
    bool ret = BaseObject::LoadIMG(file_path);
    if (ret == true)
    {
        // chieu rong cua frame
        // rect_.w la kich co tam anh load vao
        // chia cho 4 vi co 4 frame
        width_frame = rect_.w / 4;
        height_frame = rect_.h;
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
}
// set xem tung frame co kich co bao nhieu va vi tri bao nhieu
void MainObject::set_clips()
{
    if(width_frame > 0 && height_frame > 0)
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
    rect_.x = x_pos;
    rect_.y = y_pos;
    if(frame_ >= 4)
    {
        frame_ = 0;
    }
    else 
    {
        frame_++;
    }
    // rect gan nhat
    SDL_Rect* current_clip = &frame_clip_[frame_];
    SDL_Rect renderquad = {rect_.x, rect_.y, width_frame, height_frame};
    SDL_RenderCopy(renderer, p_object_, current_clip, &renderquad);
}
#endif