#include "helicopter.h"
#include "loader.h"
#include <math.h>

void init_helicopter(Helicopter* heli) {
    heli->x = 0.0f;
    heli->y = 5.0f;
    heli->z = 0.0f;
    heli->rotation_y = 0.0f;
    heli->base_speed = 30.0f;
    heli->model_id = load_obj("assets/helicopter/10621_CoastGuardHelicopter.obj");
    heli->texture_id = load_texture_sdl("assets/helicopter/HH65C.jpg");
}


void move_helicopter(Helicopter* heli, float speed, float direction) {
    float rad = heli->rotation_y * 3.14159f / 180.0f;
    heli->x += sin(rad) * speed * direction;
    heli->z += cos(rad) * speed * direction;
}

void turn_helicopter(Helicopter* heli, float angle) {
    heli->rotation_y += angle;
}

void elevate_helicopter(Helicopter* heli, float speed) {
    heli->y += speed;
    if (heli->y < 1.0f) heli->y = 1.0f;
}

void draw_helicopter(Helicopter* heli, bool is_shadow) {
    glPushMatrix();
    glTranslatef(heli->x, heli->y, heli->z);
    glRotatef(heli->rotation_y, 0.0f, 1.0f, 0.0f);

    if (heli->model_id != 0) {
        if (!is_shadow) {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, heli->texture_id);
            glColor3f(1.0f, 1.0f, 1.0f);
        } else {
            glColor3f(0.15f, 0.4f, 0.15f); 
        }
        
        glScalef(0.01f, 0.01f, 0.01f); 
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        glCallList(heli->model_id);
        
        if (!is_shadow) {
            glDisable(GL_TEXTURE_2D);
        }
    }
    glPopMatrix();
}

void update_helicopter(Helicopter* heli, double delta_time) {
}