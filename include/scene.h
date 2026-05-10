#ifndef SCENE_H
#define SCENE_H

#include <stdbool.h>

#define MAX_TREES 400
#define MAX_PARTICLES 2000

/**
 * @brief Fa (Tree) struktúra a pálya díszítéséhez.
 * Tartalmazza a fa pozícióját a 3D térben és a méretezését.
 */
typedef struct {
    float x, z;
    float scale;
} Tree;

/**
 * @brief Részecske (Particle) struktúra a tűz/füst effekthez.
 * Tartalmazza a 3D pozíciót, a sebességet, élettartamot és színt.
 */
typedef struct {
    float x, y, z;
    float vx, vy, vz;
    float life, max_life;
    float size;
    float r, g, b, a;
    bool is_smoke;
} Particle;

/**
 * @brief A játékteret (Scene) leíró fő struktúra.
 */
typedef struct {
    Tree trees[MAX_TREES];
    Particle particles[MAX_PARTICLES];
    float fire_x, fire_z;
} Scene;

/**
 * @brief Inicializálja a játékteret és a modelleket.
 */
void init_scene(Scene* scene);

/**
 * @brief Frissíti a játéktér állapotát a fizikai idő alapján.
 */
void update_scene(Scene* scene, double delta_time);

/**
 * @brief Kirajzolja a talajt.
 */
void draw_ground(Scene* scene);

/**
 * @brief Kirajzolja a fákat.
 */
void draw_trees(Scene* scene, bool is_shadow);

/**
 * @brief Kirajzolja a részecskéket.
 */
void draw_particles(Scene* scene);

#endif