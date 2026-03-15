#include "scene.h"
#include <GL/glut.h>
#include <stdlib.h>

void init_scene(Scene* scene) {
    for (int i = 0; i < MAX_TREES; i++) {
        scene->trees[i].x = (rand() % 200) - 100;
        scene->trees[i].z = (rand() % 200) - 100;
        scene->trees[i].scale = 0.8f + ((rand() % 40) / 100.0f);
    }
}

void draw_tree() {
    // Fa törzse
    glColor3f(0.55f, 0.27f, 0.07f); // Barna
    glPushMatrix();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glutSolidCone(0.5, 2.0, 10, 2);
    glPopMatrix();

    // Fa lombkoronája
    glColor3f(0.1f, 0.6f, 0.1f); // Zöld
    glPushMatrix();
    glTranslatef(0.0f, 1.5f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glutSolidCone(1.5, 4.0, 10, 2);
    glPopMatrix();
}

void draw_scene(Scene* scene) {
    // Talaj kirajzolása
    glColor3f(0.3f, 0.8f, 0.3f);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-2000.0f, 0.0f, -2000.0f);
    glVertex3f(-2000.0f, 0.0f,  2000.0f);
    glVertex3f( 2000.0f, 0.0f,  2000.0f);
    glVertex3f( 2000.0f, 0.0f, -2000.0f);
    glEnd();

    // Fák kirajzolása
    for (int i = 0; i < MAX_TREES; i++) {
        glPushMatrix();
        glTranslatef(scene->trees[i].x, 0.0f, scene->trees[i].z);
        glScalef(scene->trees[i].scale, scene->trees[i].scale, scene->trees[i].scale);
        draw_tree();
        glPopMatrix();
    }
}