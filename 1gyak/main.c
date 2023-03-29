#include "brick.h"

#include <stdio.h>

int main(int argc, char *argv[])
{
    Brick brick;
    double volume;
    double surface;

    set_brick_data(&brick, 10, 10, 8);
    volume = calc_volume(&brick);
    surface = calc_surface(&brick);

    printf("Brick volume: %lf\n", volume);
    printf("Brick surface: %lf\n", surface);

    check_side(&brick);

    return 0;
}
