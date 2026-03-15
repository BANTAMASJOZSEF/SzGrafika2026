#ifndef SCENE_H
#define SCENE_H

#define MAX_TREES 100

typedef struct {
    float x;
    float z;
    float scale;
} Tree;

typedef struct {
    Tree trees[MAX_TREES];
} Scene;

void init_scene(Scene* scene);
void draw_scene(Scene* scene);

#endif