#include <SDL2/SDL.h>
// int main()
// {
//     // cho 2 phim chay cung 1 lan 
//     while (SDL_PollEvent(&event))
//     {
//         switch (event.type)
//         {
//         case SDL_QUIT:
//             running = false;
//             break;
//         case SDL_KEYDOWN:
//             SDL_PumpEvents();
//             const Uint8 *keys = SDL_GetKeyboardState(NULL);
//             if (keys[SDL_SCANCODE_ESCAPE])
//             {
//                 running = false;
//             }
//             if (keys[SDL_SCANCODE_W])
//             {
//                 entities[1].move(0, -_MAIN_CHARACTER_VELOCITY_);
//             }
//             if (keys[SDL_SCANCODE_S])
//             {
//                 entities[1].move(0, MAIN_CHARACTER_VELOCITY);
//             }
//             if (keys[SDL_SCANCODE_A])
//             {
//                 entities[1].move(-_MAIN_CHARACTER_VELOCITY_, 0);
//             }
//             if (keys[SDL_SCANCODE_D])
//             {
//                 entities[1].move(MAIN_CHARACTER_VELOCITY, 0);
//             }
//             break;
//         }
//     }
// }