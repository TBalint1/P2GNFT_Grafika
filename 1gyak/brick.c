#include "brick.h"

#include <math.h>

void set_brick_data(Brick *brick, double x, double y, double z)
{
    brick->x = x;
    brick->y = y;
    brick->z = z;
}

double calc_volume(const Brick *brick)
{

    double volume = brick->x * brick->y * brick->z;
    return volume;
}

double calc_surface(const Brick *brick)
{

    double surface = 2 * (brick->x * brick->y + brick->x * brick->z + brick->y * brick->z);
    return surface;
}

void check_side(const Brick *brick)
{
    if (brick->x == brick->y || brick->x == brick->z || brick->y == brick->z)
    {
        printf("The brick has square sides.\n");
    }

    else
    {
        printf("The brick has no square sides.\n");
    }
}
