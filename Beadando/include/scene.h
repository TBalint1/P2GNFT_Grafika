#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

typedef struct Scene
{
    Model board;
    Model darts;
    Material material;
    GLuint floor;
    GLuint wall;
    GLuint board_texture;
    GLuint darts_texture;
    bool help_visible;
    bool equip_darts;
    bool free_roam;
    bool throw_view;
    bool throw_animation;

} scene;

void init_scene(Scene *scene);

void set_lighting();

void set_material(const Material *material);

void load_models(Scene *scene);

void load_textures(Scene *scene);

void draw_floor(Scene *scene);

void draw_skybox(Scene *scene);

void draw_board(Scene *scene);

void draw_darts(Scene *scene);

void update_darts_position(double cursor_x, double cursor_y);

void update_scene(Scene *scene);

void handle_mouse_click(int button, int state, int x, int y);

void handle_mouse_motion(int x, int y);

void draw_origin();

void render_scene(const Scene *scene);