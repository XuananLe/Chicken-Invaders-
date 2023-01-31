#include "BaseObject.h"
BaseObject::BaseObject()
{
    p_object_ = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}
BaseObject::~BaseObject()
{
}
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
            if(p_object_ == NULL)
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
    SDL_Surface *surface = NULL;
    SDL_Texture *new_texture = NULL;
    surface = IMG_Load(file);
    if (surface != NULL)
    {
        // ki thuat color key la transparent
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        new_texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (new_texture != NULL)
        {
            // load kich co cua anh vao trong rect
            rect_.w = surface->w;
            rect_.h = surface->h;
            p_object_ = new_texture;
            if(p_object_ == NULL)
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