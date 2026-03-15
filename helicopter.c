#include "helicopter.h"
#include <GL/glut.h>
#include <math.h>

void init_helicopter(Helicopter* heli) {
    heli->x = 0.0f;
    heli->y = 5.0f;
    heli->z = 0.0f;
    heli->rotation_y = 0.0f;
    heli->rotor_angle = 0.0f;
    heli->base_speed = 20.0f;
}

void update_helicopter(Helicopter* heli, double delta_time) {
    heli->rotor_angle += 700.0f * delta_time;
    if (heli->rotor_angle > 360.0f) heli->rotor_angle -= 360.0f;
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

void draw_helicopter(Helicopter* heli) {
    glPushMatrix();
    
    glTranslatef(heli->x, heli->y, heli->z);
    glRotatef(heli->rotation_y, 0.0f, 1.0f, 0.0f);

    glColor3f(0.8f, 0.1f, 0.1f);
    glPushMatrix();
    glScalef(1.0f, 1.0f, 3.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -2.0f);
    glScalef(0.3f, 0.3f, 2.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
    glTranslatef(0.0f, 0.6f, 0.0f);
    glRotatef(heli->rotor_angle, 0.0f, 1.0f, 0.0f);
    glScalef(4.0f, 0.1f, 0.3f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPopMatrix();
}