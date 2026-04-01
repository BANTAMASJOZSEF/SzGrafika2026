#ifndef SCENE_H
#define SCENE_H

#include <stdbool.h>

#define MAX_TREES 400
#define MAX_PARTICLES 2000 

typedef struct {
    float x;
    float z;
    float scale;
} Tree;

typedef struct {
    float x, y, z;
    float vx, vy, vz;
    float life, max_life;
    float r, g, b, a;
    float size;
    bool is_smoke;
} Particle;

typedef struct {
    Tree trees[MAX_TREES];
    Particle particles[MAX_PARTICLES];
    float fire_x;
    float fire_z;
} Scene;

void init_scene(Scene* scene);
void update_scene(Scene* scene, double delta_time);
void draw_scene(Scene* scene);
void draw_particles(Scene* scene);

#endif