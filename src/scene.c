#include "scene.h"
#include <GL/gl.h>
#include <stdlib.h>
#include <math.h>

static float randf(float min, float max) {
    return min + (float)rand() / ((float)RAND_MAX / (max - min));
}

void init_scene(Scene* scene) {
    scene->fire_x = 30.0f;
    scene->fire_z = -50.0f;

    for (int i = 0; i < MAX_TREES; i++) {
        float tx, tz;
        bool valid_pos;
        int attempts = 0;
        do {
            valid_pos = true;
            tx = randf(-200.0f, 200.0f);
            tz = randf(-200.0f, 200.0f);
            float dist_heli = sqrt(tx*tx + tz*tz);
            float dist_fire = sqrt((tx - scene->fire_x)*(tx - scene->fire_x) + (tz - scene->fire_z)*(tz - scene->fire_z));
            if (dist_heli < 15.0f || dist_fire < 6.0f) valid_pos = false;
            else {
                for (int j = 0; j < i; j++) {
                    float dx = tx - scene->trees[j].x;
                    float dz = tz - scene->trees[j].z;
                    if (sqrt(dx*dx + dz*dz) < 5.0f) { valid_pos = false; break; }
                }
            }
            attempts++;
            if (attempts > 50) valid_pos = true;
        } while (!valid_pos); 
        scene->trees[i].x = tx;
        scene->trees[i].z = tz;
        scene->trees[i].scale = randf(1.0f, 2.0f);
    }
    init_particle_system(&scene->particle_system, scene->fire_x, scene->fire_z);
}

void update_scene(Scene* scene, double delta_time) {
    update_particle_system(&scene->particle_system, delta_time);
}

void draw_my_shape(float base_radius, float top_radius, float height, int slices) {
    const float PI = 3.1415926f;
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= slices; i++) {
        float angle = (2.0f * PI * i) / slices;
        float nx = cos(angle); float nz = sin(angle);
        glNormal3f(nx, 0.2f, nz); 
        glVertex3f(base_radius * nx, 0.0f, base_radius * nz);
        glVertex3f(top_radius * nx, height, top_radius * nz);
    }
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, -1.0f, 0.0f); 
    glVertex3f(0.0f, 0.0f, 0.0f);  
    for (int i = slices; i >= 0; i--) {
        float angle = (2.0f * PI * i) / slices;
        glVertex3f(base_radius * cos(angle), 0.0f, base_radius * sin(angle));
    }
    glEnd();
}

void draw_tree(bool is_shadow) {
    if (is_shadow) glColor3f(0.15f, 0.4f, 0.15f); 
    else glColor3f(0.55f, 0.27f, 0.07f); 
    glPushMatrix();
    draw_my_shape(0.5f, 0.5f, 3.0f, 10);
    glPopMatrix();

    if (!is_shadow) glColor3f(0.1f, 0.6f, 0.1f); 
    glPushMatrix();
    glTranslatef(0.0f, 2.0f, 0.0f);
    draw_my_shape(1.8f, 0.0f, 8.0f, 10);
    glPopMatrix();
}

void draw_ground(Scene* scene) {
    glColor3f(0.3f, 0.8f, 0.3f);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1000.0f, 0.0f, -1000.0f);
    glVertex3f(-1000.0f, 0.0f,  1000.0f);
    glVertex3f( 1000.0f, 0.0f,  1000.0f);
    glVertex3f( 1000.0f, 0.0f, -1000.0f);
    glEnd();
}

void draw_trees(Scene* scene, bool is_shadow) {
    for (int i = 0; i < MAX_TREES; i++) {
        glPushMatrix();
        glTranslatef(scene->trees[i].x, 0.0f, scene->trees[i].z);
        glScalef(scene->trees[i].scale, scene->trees[i].scale, scene->trees[i].scale);
        draw_tree(is_shadow);
        glPopMatrix();
    }
}