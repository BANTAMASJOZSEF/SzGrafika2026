#include "app.h"
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

void init_app(App* app) {
    for (int i = 0; i < 256; i++) {
        app->keys[i] = false;
        app->special_keys[i] = false;
    }
    app->last_update_time = 0.0;
    
    init_scene(&app->scene);
    init_helicopter(&app->helicopter);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
}

void update_app(App* app, double delta_time) {
    if (app->special_keys[GLUT_KEY_UP]) {
        app->helicopter.base_speed += 60.0f * delta_time; // Gyorsítás
        if (app->helicopter.base_speed > 240.0f) app->helicopter.base_speed = 240.0f; // Max sebesség
    }
    if (app->special_keys[GLUT_KEY_DOWN]) {
        app->helicopter.base_speed -= 60.0f * delta_time; // Lassítás
        if (app->helicopter.base_speed < 0.0f) app->helicopter.base_speed = 0.0f;
    }

    float speed = app->helicopter.base_speed * delta_time;
    float turn_speed = 90.0f * delta_time;

    if (app->keys['w']) move_helicopter(&app->helicopter, speed, 1.0f);
    if (app->keys['s']) move_helicopter(&app->helicopter, speed, -1.0f);
    if (app->keys['a']) turn_helicopter(&app->helicopter, turn_speed);
    if (app->keys['d']) turn_helicopter(&app->helicopter, -turn_speed);
    if (app->keys['e']) elevate_helicopter(&app->helicopter, speed);
    if (app->keys['q']) elevate_helicopter(&app->helicopter, -speed);

    update_helicopter(&app->helicopter, delta_time);
}

void render_app(App* app) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5f, 0.7f, 1.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float cam_dist = 15.0f;
    float cam_height = 8.0f;
    float rad = app->helicopter.rotation_y * 3.14159f / 180.0f;
    
    float cam_x = app->helicopter.x - sin(rad) * cam_dist;
    float cam_z = app->helicopter.z - cos(rad) * cam_dist;
    float cam_y = app->helicopter.y + cam_height;

    gluLookAt(
        cam_x, cam_y, cam_z,
        app->helicopter.x, app->helicopter.y, app->helicopter.z,
        0.0f, 1.0f, 0.0f
    );

    GLfloat light_pos[] = { 50.0f, 100.0f, 50.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    draw_scene(&app->scene);
    draw_helicopter(&app->helicopter);


    // --- HUD (Szöveges felület) rajzolása 2D-ben ---
    glMatrixMode(GL_PROJECTION);
    glPushMatrix(); // Eltesszük a 3D-s kamerát
    glLoadIdentity();
    // Átváltunk 2D-re (0,0 a bal felső sarok)
    gluOrtho2D(0, app->window_width, app->window_height, 0); 

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    // sebesség szöveg szine
    glColor3f(1.0f, 1.0f, 1.0f); 
    // sebesség jobb felso sarokba
    glRasterPos2i(app->window_width - 150, 30);
    // sebesség szövege
    char speed_text[50];
    sprintf(speed_text, "Sebesseg: %.0f", app->helicopter.base_speed);
    // sebesseg kiiras
    for (int i = 0; speed_text[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, speed_text[i]);
    }
    // magasagg pozicio
    glRasterPos2i(app->window_width - 150, 55);
    // magassag szovege
    char height_text[50];
    sprintf(height_text, "Magassag: %.1f", app->helicopter.y);
    // magasabb kiiras
    for (int i = 0; height_text[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, height_text[i]);
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glutSwapBuffers();
}