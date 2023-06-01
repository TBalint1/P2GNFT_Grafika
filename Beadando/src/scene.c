#include "scene.h"

#include <obj/load.h>
#include <obj/draw.h>
#include <math.h>
#include <GL/gl.h>

static double cursor_x = 0.0;
static double cursor_y = 0.0;

// A darts nyíl pozíciója
static double dart_x = 0.0;
static double dart_y = 0.0;

// Az animációhoz szükséges változók
static double animation_time = 0.0;
static double dart_rotation = 0.0;
static double dart_translate_x = 0.0;
static double dart_translate_y = 0.0;
static double dart_translate_z = 0.0;

void init_scene(Scene *Scene)
{
    load_models(Scene);
    load_textures(Scene);

    scene->material.ambient.red = 1.0;
    scene->material.ambient.green = 1.0;
    scene->material.ambient.blue = 1.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 1.0;
    scene->material.specular.green = 1.0;
    scene->material.specular.blue = 1.0;

    scene->material.shiness = 0.0;
    scene->angel = 0.0;

    scene->visible_help = false;
    scene->equip_darts = false;
    scene->free_roam = true;
    scene->throw_view = false;
    scene->throw_animation = false;
}

void set_lighting()
{
    float ambient_light[] = {0.0f, 0.0f, 0.0f, 1.0f};
    float diffuse_light[] = {1.0f, 1.0f, 1.0, 1.0f};
    float specular_light[] = {0.0f, 0.0f, 0.0f, 1.0f};
    float position[] = {0.0f, 0.0f, 50.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material *material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue};

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue};

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void load_models(Scene *scene)
{

    load_model(&(scene->board), "assets/models/board.obj");
    load_model(&(scene->darts), "assets/models/darts.obj");
}

void load_textures(Scene *scene)
{

    scene->floor = load_texture("assets/textures/floor.jpg");
    scene->wall = load_texture("assets/textures/wall.jpg");
    scene->board = load_texture("assets/textures/board.png");
    scene->darts = load_texture("assets/textures/darts.png");
}

void draw_floor(Scene *scene)
{

    glDisable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, scene.floor);
    glPushMatrix();

    glRotatef(90, 1, 0, 0);
    glTranslatef(0, -3, 0);
    glScaled(4.0, 4.0, 4.0);
    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);

    glTexCoord2d(1.0, 0);
    glVertex3f(-40.0, -1, 100.0);

    glTexCoord2d(0, 0);
    glVertex3f(80.0, -1, 100.0);

    glTexCoord2d(0, 1);
    glVertex3f(40.0, 0.80, -100.0);

    glTexCoord2d(1.0, 1.0);
    glVertex3f(-80.0, 0.80, -100.0);
    glEnd();

    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void draw_skybox(Scene *scene)
{

    glDisable(GL_LIGHTING);

    glBindTexture(GL_TEXTURE_2D, scene.wall);

    double theta, phi1, phi2;
    double x1, y1, z1;
    double x2, y2, z2;
    double u, v1, v2;
    int n_slices, n_stacks;
    double radius;
    int i, k;
    n_slices = 15;
    n_stacks = 15;
    radius = 200;

    glPushMatrix();

    glScaled(radius, radius, radius);

    glColor3f(1, 1, 1);

    glBegin(GL_TRIANGLE_STRIP);

    for (i = 0; i < n_stacks; ++i)
    {
        v1 = (double)i / n_stacks;
        v2 = (double)(i + 1) / n_stacks;
        phi1 = v1 * M_PI / 2.0;
        phi2 = v2 * M_PI / 2.0;
        for (k = 0; k <= n_slices; ++k)
        {
            u = (double)k / n_slices;
            theta = u * 2.0 * M_PI;
            x1 = cos(theta) * cos(phi1);
            y1 = sin(theta) * cos(phi1);
            z1 = sin(phi1) - 0.25;
            x2 = cos(theta) * cos(phi2);
            y2 = sin(theta) * cos(phi2);
            z2 = sin(phi2) - 0.25;
            glTexCoord2d(u, 1.0 - v1);
            glVertex3d(x1, y1, z1);
            glTexCoord2d(u, 1.0 - v2);
            glVertex3d(x2, y2, z2);
        }
    }

    glEnd();

    glPopMatrix();

    glEnable(GL_LIGHTING);
}

void draw_board(Scene *scene)
{

    // glEnable(GL_BLEND);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene.board_texture)

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTranslatef(-20, 0, 2.5);
    glScaled(4.0, 4.0, 4.0);
    glRotatef(0, 1.0, 0.0, 0.0);
    draw_model(&(scene.board));

    glPopMatrix();
    // glDisable(GL_BLEND);
}

void draw_darts(Scene *scene)
{
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene.darts_texture)

        glTranslatef(dart_x, dart_y, 0.0);
    glRotatef(dart_rotation, 0.0, 0.0, 1.0);
    glTranslatef(dart_translate_x, dart_translate_y, dart_translate_z);
    draw_model(&(scene.darts));

    glPopMatrix();
}

void update_darts_position(double cursor_x, double cursor_y)
{
    // Kiszámítjuk az egér pozícióját az ablak relatív koordinátáiból
    int window_width = glutGet(GLUT_WINDOW_WIDTH);
    int window_height = glutGet(GLUT_WINDOW_HEIGHT);
    double normalized_x = cursor_x / window_width;
    double normalized_y = cursor_y / window_height;

    // Átalakítjuk az ablak relatív koordinátákat a színpadtér koordinátáira
    double scene_width = 40.0;
    double scene_height = 20.0;
    double scene_x = normalized_x * scene_width - scene_width / 2.0;
    double scene_y = (1.0 - normalized_y) * scene_height - scene_height / 2.0;

    // Frissítjük a darts pozícióját
    dart_x = scene_x;
    dart_y = scene_y;
}

void update_scene(Scene *scene)
{
    scene->darts.x = x;
    scene->darts.y = y;

    // Frissítjük a kamerát az új darts pozícióhoz igazítva
    gluLookAt(0.0, 0.0, 50.0, x, y, 0.0, 0.0, 1.0, 0.0);

    // Frissítjük a képernyőt
    glutPostRedisplay();

    // Az animáció lejátszása
    if (scene->throw_animation)
    {
        // Animációs idő növelése
        animation_time += 0.01;

        // Darts forgatása
        dart_rotation += 10.0;

        // Darts mozgatása a levegőben
        double t = animation_time * 2.0;
        dart_translate_x = 4.0 * cos(t);
        dart_translate_y = 4.0 * sin(t);
        dart_translate_z = 2.0 * sin(t);

        // Darts találata a táblába (a kattintás helyére)
        if (animation_time >= 1.0)
        {
            dart_translate_x = dart_x;
            dart_translate_y = dart_y;
            dart_translate_z = 0.0;
        }

        // Animáció vége
        if (animation_time >= 2.0)
        {
            scene->throw_animation = false;
            animation_time = 0.0;
            dart_rotation = 0.0;
            dart_translate_x = 0.0;
            dart_translate_y = 0.0;
            dart_translate_z = 0.0;
        }
    }
}

// A játék állapotának frissítése az egér kattintására
void handle_mouse_click(int button, int state, int x, int y)
{
    // Csak az egér bal gombjának lenyomására reagálunk
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && scene->free_roam == false)
    {
        // A darts animációjának indítása
        scene->throw_animation = true;
    }
}

// Az egér mozgásának figyelése
void handle_mouse_motion(int x, int y)
{
    // Frissítjük az egér pozícióját
    cursor_x = x;
    cursor_y = y;

    if (scene->free_roam = false)
    {
        // Frissítjük a darts pozícióját
        update_darts_position(cursor_x, cursor_y);
    }
}

void show_help(GLuint help_texture)
{
    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, help_texture);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3d(-2, 1.5, -3);
    glTexCoord2f(1, 0);
    glVertex3d(2, 1.5, -3);
    glTexCoord2f(1, 1);
    glVertex3d(2, -1.5, -3);
    glTexCoord2f(0, 1);
    glVertex3d(-2, -1.5, -3);
    glEnd();

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}

void render_scene(const Scene *scene)
{

    set_material(&(scene->material));
    set_lighting();
    draw_origin();
    draw_skybox(*scene);
    draw_floor(*scene);
    draw_board(*scene);
    draw_darts(*scene);
}