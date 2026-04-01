#include "scene.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

float randf(float min, float max) {
    return min + (float)rand() / ((float)RAND_MAX / (max - min));
}

void reset_particle(Particle* p, float fire_x, float fire_z) {
    p->x = fire_x + randf(-3.5f, 3.5f); 
    p->z = fire_z + randf(-3.5f, 3.5f);
    p->is_smoke = (rand() % 100) < 60;  

    if (p->is_smoke) {
        p->y = randf(2.0f, 8.0f);       
        p->vx = randf(-1.5f, 1.5f);
        p->vy = randf(4.0f, 9.0f);     
        p->vz = randf(-1.5f, 1.5f);
        p->max_life = randf(4.0f, 7.0f);
        p->size = randf(0.8f, 2.0f);
        p->r = 0.3f; p->g = 0.3f; p->b = 0.3f; p->a = 0.5f;
    } else {
        p->y = randf(0.0f, 2.0f);       
        p->vx = randf(-0.3f, 0.3f);
        p->vy = randf(3.0f, 7.0f);      
        p->vz = randf(-0.3f, 0.3f);
        p->max_life = randf(0.8f, 2.0f); 
        p->size = randf(0.4f, 1.2f);
        p->r = 1.0f; p->g = randf(0.2f, 0.8f); p->b = 0.0f; p->a = 0.8f; 
    }
    p->life = p->max_life;
}


void init_scene(Scene* scene) {
    scene->fire_x = 30.0f;
    scene->fire_z = -50.0f;

    for (int i = 0; i < MAX_TREES; i++) {
        float tx, tz;
        bool valid_position;
        
        do {
            valid_position = true;
            tx = randf(-200.0f, 200.0f);
            tz = randf(-200.0f, 200.0f);
            
            float dist_to_heli = sqrt(tx*tx + tz*tz);
            float dist_to_fire = sqrt((tx - scene->fire_x)*(tx - scene->fire_x) + (tz - scene->fire_z)*(tz - scene->fire_z));
            
            if (dist_to_heli < 15.0f || dist_to_fire < 6.0f) {
                valid_position = false;
            } else {
                for (int j = 0; j < i; j++) {
                    float dx = tx - scene->trees[j].x;
                    float dz = tz - scene->trees[j].z;
                    float dist_to_other_tree = sqrt(dx*dx + dz*dz);
                    
                    if (dist_to_other_tree < 5.0f) {
                        valid_position = false;
                        break;
                    }
                }
            }
            
        } while (!valid_position); 
        
        scene->trees[i].x = tx;
        scene->trees[i].z = tz;
        scene->trees[i].scale = randf(0.8f, 1.6f);
    }

    // Részecskék kezdeti generálása (tűz és füst)
    for (int i = 0; i < MAX_PARTICLES; i++) {
        reset_particle(&scene->particles[i], scene->fire_x, scene->fire_z);
        scene->particles[i].life = randf(0.0f, scene->particles[i].max_life);
    }
}

void update_scene(Scene* scene, double delta_time) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        Particle* p = &scene->particles[i];
        p->life -= delta_time;
        
        if (p->life <= 0.0f) {
            reset_particle(p, scene->fire_x, scene->fire_z);
        } else {
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

void draw_tree() {
    // Törzs
    glColor3f(0.55f, 0.27f, 0.07f); 
    glPushMatrix();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glutSolidCone(0.5, 3.0, 10, 2);
    glPopMatrix();

    // Lombkorona
    glColor3f(0.1f, 0.6f, 0.1f); 
    glPushMatrix();
    glTranslatef(0.0f, 2.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glutSolidCone(1.8, 8.0, 10, 2);
    glPopMatrix();
}

void draw_particles(Scene* scene) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_LIGHTING);
    glDepthMask(GL_FALSE);

    for (int i = 0; i < MAX_PARTICLES; i++) {
        Particle* p = &scene->particles[i];
        glColor4f(p->r, p->g, p->b, p->a);
        
        glPushMatrix();
        glTranslatef(p->x, p->y, p->z);
        glutSolidCube(p->size);
        glPopMatrix();
    }

    glDepthMask(GL_TRUE);
    glEnable(GL_LIGHTING);
    glDisable(GL_BLEND);
}

void draw_scene(Scene* scene) {
    glColor3f(0.3f, 0.8f, 0.3f);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-2000.0f, 0.0f, -2000.0f);
    glVertex3f(-2000.0f, 0.0f,  2000.0f);
    glVertex3f( 2000.0f, 0.0f,  2000.0f);
    glVertex3f( 2000.0f, 0.0f, -2000.0f);
    glEnd();

    for (int i = 0; i < MAX_TREES; i++) {
        glPushMatrix();
        glTranslatef(scene->trees[i].x, 0.0f, scene->trees[i].z);
        glScalef(scene->trees[i].scale, scene->trees[i].scale, scene->trees[i].scale);
        draw_tree();
        glPopMatrix();
    }

    // Tűz és füst kirajzolása
    // draw_particles(scene);
}