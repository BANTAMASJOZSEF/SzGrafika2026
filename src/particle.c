#include "particle.h"
#include <GL/gl.h>
#include <stdlib.h>

static float rand_float(float min, float max) {
    return min + (float)rand() / ((float)RAND_MAX / (max - min));
}

static void reset_particle(Particle* p, float fire_x, float fire_z) {
    p->x = fire_x + rand_float(-3.5f, 3.5f); 
    p->z = fire_z + rand_float(-3.5f, 3.5f);
    p->is_smoke = (rand() % 100) < 60;  
    if (p->is_smoke) {
        p->y = rand_float(2.0f, 8.0f);       
        p->vx = rand_float(-1.5f, 1.5f);
        p->vy = rand_float(4.0f, 9.0f);     
        p->vz = rand_float(-1.5f, 1.5f);
        p->max_life = rand_float(4.0f, 7.0f);
        p->size = rand_float(0.8f, 2.0f);
        p->r = 0.3f; p->g = 0.3f; p->b = 0.3f; p->a = 0.5f;
    } else {
        p->y = rand_float(0.0f, 2.0f);       
        p->vx = rand_float(-0.3f, 0.3f);
        p->vy = rand_float(3.0f, 7.0f);      
        p->vz = rand_float(-0.3f, 0.3f);
        p->max_life = rand_float(0.8f, 2.0f); 
        p->size = rand_float(0.4f, 1.2f);
        p->r = 1.0f; p->g = rand_float(0.2f, 0.8f); p->b = 0.0f; p->a = 0.8f; 
    }
    p->life = p->max_life;
}

void init_particle_system(ParticleSystem* ps, float x, float z) {
    ps->emitter_x = x;
    ps->emitter_z = z;
    for (int i = 0; i < MAX_PARTICLES; i++) {
        reset_particle(&ps->particles[i], ps->emitter_x, ps->emitter_z);
        ps->particles[i].life = rand_float(0.0f, ps->particles[i].max_life);
    }
}

void update_particle_system(ParticleSystem* ps, float delta_time) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        Particle* p = &ps->particles[i];
        p->life -= delta_time;
        if (p->life <= 0.0f) reset_particle(p, ps->emitter_x, ps->emitter_z);
        else {
            p->x += p->vx * delta_time;
            p->y += p->vy * delta_time;
            p->z += p->vz * delta_time;

            if (p->is_smoke) {
                p->size += 1.5f * delta_time;
                p->a = 0.5f * (p->life / p->max_life); 
            } else {
                p->g -= 1.0f * delta_time; 
                if (p->g < 0.0f) p->g = 0.0f; 
                p->a = 0.8f * (p->life / p->max_life);
            }
        }
    }
}

void draw_particle_system(ParticleSystem* ps) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_LIGHTING);
    glDepthMask(GL_FALSE);
    
    for (int i = 0; i < MAX_PARTICLES; i++) {
        Particle* p = &ps->particles[i];
        glColor4f(p->r, p->g, p->b, p->a);
        glPushMatrix();
        glTranslatef(p->x, p->y, p->z);
        
        float h = p->size / 2.0f;
        glBegin(GL_QUADS);
        glVertex3f(-h, -h,  0.0f); glVertex3f( h, -h,  0.0f); 
        glVertex3f( h,  h,  0.0f); glVertex3f(-h,  h,  0.0f);
        glEnd();
        
        glPopMatrix();
    }
    
    glDepthMask(GL_TRUE);
    glEnable(GL_LIGHTING);
    glDisable(GL_BLEND);
}