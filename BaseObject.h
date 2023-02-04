#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H
#include "CommonFunc.h"
#pragma once
class BaseObject
{
public:
    BaseObject();
    ~BaseObject();
    void SetRect(const int &x, const int &y)
    {
        rect_.x = x;
        rect_.y = y;
    }
    void SetRect(const int &x, const int &y, const int &width, const int &height)
    {
        rect_.x = x;
        rect_.y = y;
        rect_.w = width;
        rect_.h = height;
    }
    SDL_Rect GetRect() const { return rect_; }
    SDL_Texture *GetObject() const { return p_object_; }
    
    void set_width_height(const int &width, const int &height){ rect_.w = width; rect_.h = height;}
    void Set_Rect(const int &x, const int &y) { rect_.x = x; rect_.y = y; }
    void Set_Rect(const int &x, const int &y, const int &width, const int &height) { rect_.x = x; rect_.y = y; rect_.w = width; rect_.h = height; }
    
    void SetTexture(SDL_Texture *p_object_) { this->p_object_ = p_object_; }
    void Render(const double &angle) { SDL_RenderCopyEx(renderer, p_object_, NULL, &rect_, angle, NULL, SDL_FLIP_NONE); }
    void Render() { SDL_RenderCopy(renderer, p_object_, NULL, &rect_); }
    virtual bool LoadIMG(const char *file, SDL_Renderer *screen);
    virtual bool LoadIMG(const char *file);
    void Render(SDL_Renderer *des, const SDL_Rect *clip);
    void free();

protected:
    SDL_Texture *p_object_;
    SDL_Rect rect_;
};
BaseObject::BaseObject()
{
    p_object_ = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}
BaseObject::~BaseObject(){}
bool BaseObject::LoadIMG(const char *file, SDL_Renderer *screen)
{
    SDL_Surface *surface = NULL;
    SDL_Texture *new_texture = NULL;
    surface = IMG_Load(file);
    if (surface != NULL)
    {
        // ki thuat color key la transparent
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        new_texture = SDL_CreateTextureFromSurface(screen, surface);
        if (new_texture != NULL)
        {
            // load kich co cua anh vao trong rect
            rect_.w = surface->w;
            rect_.h = surface->h;
            p_object_ = new_texture;
            if (p_object_ == NULL)
            {
                std::cout << "Error loading texture" << std::endl;
                exit(0);
                return false;
            }
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(new_texture);
            return (p_object_ != NULL);
        }
        else
        {
            std::cout << SDL_GetError() << std::endl;
            std::cout << "Error at here lmao" << std::endl;
            exit(0);
            return false;
        }
    }
    return false;
}
bool BaseObject::LoadIMG(const char *file)
{
    free();
    SDL_Texture *newTexure = NULL;
    SDL_Surface *surface = IMG_Load(file);
    newTexure = SDL_CreateTextureFromSurface(renderer, surface);
    if (newTexure != NULL)
    {
        p_object_ = newTexure;
        rect_.w = surface->w;
        rect_.h = surface->h;
        // SDL_DestroyTexture(newTexure);
        SDL_FreeSurface(surface);
        return true;
    }
    else
        std::cout << SDL_GetError() << std::endl;
    return false;
}
void BaseObject::Render(SDL_Renderer *des, const SDL_Rect *clip = NULL)
{
    SDL_Rect renderquad;
    renderquad.x = rect_.x;
    renderquad.y = rect_.y;
    renderquad.w = rect_.w;
    renderquad.h = rect_.h;
    SDL_RenderCopy(des, p_object_, clip, &renderquad);
}

void BaseObject::free()
{
    if (p_object_ != NULL)
    {
        SDL_DestroyTexture(p_object_);
        p_object_ = NULL;
        rect_.w = 0;
        rect_.h = 0;
    }
}
bool HasCollision(const BaseObject *A, const BaseObject *B)
{
    SDL_Rect rectA = A->GetRect();
    SDL_Rect rectB = B->GetRect();
    if (SDL_HasIntersection(&rectA, &rectB) == SDL_TRUE)
    {
        return true;
    }
    return false;
}
#endif
