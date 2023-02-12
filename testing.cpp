#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

bool quit = false;
Mix_Music *music = NULL;

int main(int argc, char* argv[]) {
  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;
  TTF_Font* font = NULL;
  SDL_Surface* option1Surface = NULL;
  SDL_Surface* option2Surface = NULL;
  SDL_Texture* option1Texture = NULL;
  SDL_Texture* option2Texture = NULL;
  SDL_Rect option1Rect = {0, 0, 200, 50};
  SDL_Rect option2Rect = {0, 60, 200, 50};

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  if (TTF_Init() == -1) {
    printf("TTF could not initialize! TTF_Error: %s\n", TTF_GetError());
    return 1;
  }

  window = SDL_CreateWindow("Menu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  font = TTF_OpenFont("Assets/font/arial.ttf", 28);
  if (font == NULL) {
    printf("Failed to load font! TTF_Error: %s\n", TTF_GetError());
    return 1;
  }

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    return 1;
  }

  music = Mix_LoadMUS("Assets/sound/MENU_THEME.mp3");
  if (music == NULL) {
    printf("Failed to load theme music! SDL_mixer Error: %s\n", Mix_GetError());
    return 1;
  }

  option1Surface = TTF_RenderText_Solid(font, "Option 1", {255, 255, 255});
  option1Texture = SDL_CreateTextureFromSurface(renderer, option1Surface);
  SDL_FreeSurface(option1Surface);
  option1Surface = NULL;

    option2Texture = SDL_CreateTextureFromSurface(renderer, option2Surface);
  SDL_FreeSurface(option2Surface);
  option2Surface = NULL;
  std::cout << option2Rect.x << " " << option2Rect.y << " " << option2Rect.w << " " << option2Rect.h << std::endl;
  Mix_PlayMusic(music, -1);

  while (!quit) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          quit = true;
          break;
        case SDL_MOUSEBUTTONUP:
          int x, y;
          SDL_GetMouseState(&x, &y);
          if (x >= option1Rect.x && x <= option1Rect.x + option1Rect.w && y >= option1Rect.y && y <= option1Rect.y + option1Rect.h) {
            // Handle Option 1
          } else if (x >= option2Rect.x && x <= option2Rect.x + option2Rect.w && y >= option2Rect.y && y <= option2Rect.y + option2Rect.h) {
            // Handle Option 2
          }
          break;
        default:
          break;
      }
    }

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, option1Texture, NULL, &option1Rect);
    SDL_RenderCopy(renderer, option2Texture, NULL, &option2Rect);
    SDL_RenderPresent(renderer);
  }

  Mix_FreeMusic(music);
  music = NULL;
  TTF_CloseFont(font);
  font = NULL;
  SDL_DestroyTexture(option1Texture);
  option1Texture = NULL;
  SDL_DestroyTexture(option2Texture);
  option2Texture = NULL;
  SDL_DestroyRenderer(renderer);
  renderer = NULL;
  SDL_DestroyWindow(window);
  window = NULL;
  TTF_Quit();
  Mix_Quit();
  SDL_Quit();

  return 0;
}

