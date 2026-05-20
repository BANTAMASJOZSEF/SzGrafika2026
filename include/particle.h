#ifndef PARTICLE_H
#define PARTICLE_H

#include <stdbool.h>

#define MAX_PARTICLES 2000

/**
 * @brief Egyetlen részecske (tűz vagy füst) állapotát leíró adatszerkezet.
 */
typedef struct {
    float x, y, z;       /**< A részecske aktuális térbeli pozíciója */
    float vx, vy, vz;    /**< A részecske sebességvektora (mozgás iránya és sebessége) */
    float life;          /**< A részecske hátralévő élettartama (másodpercben) */
    float max_life;      /**< A részecske teljes élettartama (a kifakulás számításához) */
    float size;          /**< A részecske mérete (kiterjedése) */
    float r, g, b, a;    /**< A részecske RGBA színe és átlátszósága */
    bool is_smoke;       /**< Igaz, ha a részecske füstöt reprezentál, Hamis, ha tüzet */
} Particle;

/**
 * @brief A részecskéket összefogó és menedzselő rendszer (Particle System).
 */
typedef struct {
    Particle particles[MAX_PARTICLES]; /**< A rendszerhez tartozó részecskék tömbje */
    float emitter_x;                   /**< A kibocsátó (forrás) X koordinátája */
    float emitter_z;                   /**< A kibocsátó (forrás) Z koordinátája */
} ParticleSystem;

/**
 * @brief Inicializálja a részecskerendszert és feltölti a részecskéket alapértékekkel.
 * @param ps Mutató a ParticleSystem struktúrára.
 * @param x A kibocsátó forrás X koordinátája a térben.
 * @param z A kibocsátó forrás Z koordinátája a térben.
 */
void init_particle_system(ParticleSystem* ps, float x, float z);

/**
 * @brief Frissíti az összes részecske pozícióját, színét és élettartamát a delta time alapján.
 * Ha egy részecske "meghal", újraéleszti azt a forrásnál.
 * @param ps Mutató a ParticleSystem struktúrára.
 * @param delta_time Az előző képkocka óta eltelt idő másodpercben.
 */
void update_particle_system(ParticleSystem* ps, float delta_time);

/**
 * @brief Kirajzolja az összes aktív részecskét a 3D térbe (Blendelés használatával).
 * @param ps Mutató a ParticleSystem struktúrára.
 */
void draw_particle_system(ParticleSystem* ps);

#endif