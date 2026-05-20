#ifndef PARTICLE_H
#define PARTICLE_H

#include <stdbool.h>

#define MAX_PARTICLES 2000

typedef struct {
    float x, y, z;
    float vx, vy, vz;
    float life, max_life;
    float size;
    float r, g, b, a;
    bool is_smoke;
} Particle;

typedef struct {
    Particle particles[MAX_PARTICLES];
    float emitter_x; // A tűz forrásának X koordinátája
    float emitter_z; // A tűz forrásának Z koordinátája
} ParticleSystem;

void init_particle_system(ParticleSystem* ps, float x, float z);
void update_particle_system(ParticleSystem* ps, float delta_time);
void draw_particle_system(ParticleSystem* ps);

#endif