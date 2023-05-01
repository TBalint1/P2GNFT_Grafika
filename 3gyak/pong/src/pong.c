#include "pong.h"
int score[] = {0, 0};

void init_pong(Pong *pong, int width, int height)
{
    pong->width = width;
    pong->height = height;
    init_pad(&(pong->left_pad), 0, height, RED_THEME);
    init_pad(&(pong->right_pad), width - 50, height, GREEN_THEME);
    init_ball(&(pong->ball), width / 2, height / 2);
}

void update_pong(Pong *pong, double time)
{
    update_pad(&(pong->left_pad), time);
    update_pad(&(pong->right_pad), time);
    update_ball(&(pong->ball), time);
    bounce_ball(pong);
}

void render_pong(Pong *pong)
{
    render_pad(&(pong->left_pad));
    render_pad(&(pong->right_pad));
    render_ball(&(pong->ball));
}

void set_left_pad_position(Pong *pong, float position)
{
    set_pad_position(&(pong->left_pad), position);
}

void set_left_pad_speed(Pong *pong, float speed)
{
    set_pad_speed(&(pong->left_pad), speed);
}

void set_right_pad_position(Pong *pong, float position)
{
    set_pad_position(&(pong->right_pad), position);
}

void set_right_pad_speed(Pong *pong, float speed)
{
    set_pad_speed(&(pong->right_pad), speed);
}

int check_score()
{

    int i;

    for (i = 0; i < 2; i++)
    {

        if (score[i] == 10)
        {

            score[0] = 0;
            score[1] = 0;

            if (i == 0)
            {

                return 1;
            }
            else
            {

                return 2;
            }
        }
    }

    return 0;
}

void bounce_ball(Pong *pong)
{
    if ((pong->left_pad.y + pong->left_pad.height) >= pong->ball.y)
    {
        if (pong->ball.x > pong->left_pad.x)
        {

            if (pong->ball.x - pong->ball.radius < 50)
            {
                pong->ball.x = pong->ball.radius + 50;
                pong->ball.speed_x *= -1;
            }
        }
    }

    else
    {
        pong->ball.speed_x *= -1;
        pong->ball.speed_y *= -1;
        score[0] += 1;
    }

    if ((pong->right_pad.y + pong->right_pad.height) >= pong->ball.y)
    {
        if (pong->ball.x < pong->right_pad.x)
        {

            if (pong->ball.x + pong->ball.radius > pong->width - 50)
            {
                pong->ball.x = pong->width - pong->ball.radius - 50;
                pong->ball.speed_x *= -1;
            }
        }

        else
        {
            pong->ball.speed_x *= -1;
            pong->ball.speed_y *= -1;
            score[1] += 1;
        }
    }

    if (pong->ball.y - pong->ball.radius < 0)
    {
        pong->ball.y = pong->ball.radius;
        pong->ball.speed_y *= -1;
    }

    if (pong->ball.y + pong->ball.radius > pong->height)
    {
        pong->ball.y = pong->height - pong->ball.radius;
        pong->ball.speed_y *= -1;
    }
}

static void draw_player_1_score()
{

    SDL_Rect src;
    SDL_Rect dest;

    src.x = 0;
    src.y = 0;
    src.w = 64;
    src.h = 64;

    dest.x = (screen->w / 2) + 12;
    dest.y = 0;
    dest.w = 64;
    dest.h = 64;

    if (score[1] > 0 && score[1] < 10)
    {

        src.x += src.w * score[1];
    }

    SDL_BlitSurface(numbermap, &src, screen, &dest);
}

static void draw_player_0_score()
{

    SDL_Rect src;
    SDL_Rect dest;

    src.x = 0;
    src.y = 0;
    src.w = 64;
    src.h = 64;

    dest.x = (screen->w / 2) - src.w - 12;
    dest.y = 0;
    dest.w = 64;
    dest.h = 64;

    if (score[0] > 0 && score[0] < 10)
    {

        src.x += src.w * score[0];
    }

    SDL_BlitSurface(numbermap, &src, screen, &dest);
}
