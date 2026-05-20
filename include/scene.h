#ifndef SCENE_H
#define SCENE_H

#include <stdbool.h>
#include "particle.h"

#define MAX_TREES 400

/**
 * @brief Egy fát reprezentáló adatszerkezet a pályán.
 */
typedef struct {
    float x, z;   /**< A fa térbeli pozíciója (az Y mindig 0, a talajon áll) */
    float scale;  /**< A fa méretezése (véletlenszerű nagyság) */
} Tree;

/**
 * @brief A teljes 3D-s környezetet (tájat, fákat, tüzet) összefogó osztály.
 */
typedef struct {
    Tree trees[MAX_TREES];             /**< A pályán lévő fák tömbje */
    ParticleSystem particle_system;    /**< A tájhoz tartozó részecskerendszer (tűz/füst) */
    float fire_x;                      /**< A tábortűz (és a részecskeforrás) X koordinátája */
    float fire_z;                      /**< A tábortűz (és a részecskeforrás) Z koordinátája */
} Scene;

/**
 * @brief Inicializálja a játékteret.
 * Generálja a fák véletlenszerű, de érvényes pozícióit (nem lóghatnak a tűzbe vagy a helikopterbe),
 * és beállítja a részecskerendszert.
 * @param scene Mutató a Scene struktúrára.
 */
void init_scene(Scene* scene);

/**
 * @brief Frissíti a játéktér animált elemeit (pl. a részecskerendszert).
 * @param scene Mutató a Scene struktúrára.
 * @param delta_time Eltelt idő másodpercben.
 */
void update_scene(Scene* scene, double delta_time);

/**
 * @brief Kirajzolja a végtelennek tűnő talajt (zöld sík) normálvektorokkal a megvilágításhoz.
 * @param scene Mutató a Scene struktúrára.
 */
void draw_ground(Scene* scene);

/**
 * @brief Kirajzolja a pályán lévő összes fát.
 * @param scene Mutató a Scene struktúrára.
 * @param is_shadow Ha true, akkor a fákat textúra és fény nélkül, sötét árnyékként rajzolja a talajra.
 */
void draw_trees(Scene* scene, bool is_shadow);

#endif