#ifndef SCENE_H
#define SCENE_H

#include <stdbool.h>
#include "particle.h"

#define MAX_TREES 400

typedef struct {
    float x, z;
    float scale;
} Tree;

typedef struct {
    Tree trees[MAX_TREES];
    ParticleSystem particle_system;
    float fire_x, fire_z;
} Scene;

void init_scene(Scene* scene);
void update_scene(Scene* scene, double delta_time);
void draw_ground(Scene* scene);
void draw_trees(Scene* scene, bool is_shadow);

#endif