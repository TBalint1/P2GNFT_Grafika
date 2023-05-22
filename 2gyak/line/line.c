#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

typedef struct Color Color;
struct Color
{
    int red;
    int green;
    int blue;
};

typedef struct Line Line;
struct Line
{
    int x1;
    int y1;
    int x2;
    int y2;
    Color color;
};

int main(int argc, char **argv)
{

    int error_code;
    SDL_Window *window;
    bool need_run;
    SDL_Event event;
    SDL_Renderer *renderer;
    int i;
    int xMouse, yMouse;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0)
    {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return error_code;
    }

    window = SDL_CreateWindow(
        "Draw line",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, 0);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_RenderPresent(renderer);

    need_run = true;

    while (need_run)
    {

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_MOUSEBUTTONDOWN:
                if (counter == 0)
                {
                    Line.x1 = event.button.x;
                    Line.y1 = event.button.y;
                    counter += 1;
                    SDL_GetGlobalMouseState(&xMouse, &yMouse);
                }
                else
                {
                    counter = 0;
                    Line.x2 = event.button.x;
                    Line.y2 = event.button.y;
                    SDL_GetGlobalMouseState(&xMouse, &yMouse);
                    Color.red = rand() % 255;
                    Color.green = rand() % 255;
                    Color.blue = rand() % 255;
                }

                break;
            case SDL_QUIT:
                need_run = false;
                break;

            default:
                break;
            }

            SDL_SetRenderDrawColor(renderer, Color.red, Color.green, Color.blue, SDL_ALPHA_OPAQUE)
                SDL_RenderDrawLine(renderer, Line.x1, Line.y1, Line.x2, Line.y2)
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    return 0;
}
