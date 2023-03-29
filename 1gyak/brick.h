#ifndef BRICK_H
#define BRICK_H

/**
 * Data of a circle object in Descartes coordinate system
 */

typedef struct Brick
{
    double x;
    double y;
    double z;

} Brick;

/**
 * Set the data of the brick
 */
void set_brick_data(Brick *brick, double x, double y, double z);

/**
 * Calculate the volume and the surface of the brick.
 */
double calc_volume(const Brick *brick);
double calc_surface(const Brick *brick);

void check_side(const Brick *brick);

#endif // CIRCLE_H
