#include "app.h"
#include "particle.h"
#include <GL/gl.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// --- SAJÁT MATEMATIKAI FÜGGVÉNYEK A GLU HELYETTESÍTÉSÉRE ---

void my_lookAt(float eyex, float eyey, float eyez,
               float centerx, float centery, float centerz,
               float upx, float upy, float upz) {
    float forward[3], side[3], up[3];
    float matrix[16], inv_len;

    forward[0] = centerx - eyex;
    forward[1] = centery - eyey;
    forward[2] = centerz - eyez;

    inv_len = 1.0f / sqrt(forward[0]*forward[0] + forward[1]*forward[1] + forward[2]*forward[2]);
    forward[0] *= inv_len; forward[1] *= inv_len; forward[2] *= inv_len;

    side[0] = forward[1] * upz - forward[2] * upy;
    side[1] = forward[2] * upx - forward[0] * upz;
    side[2] = forward[0] * upy - forward[1] * upx;

    inv_len = 1.0f / sqrt(side[0]*side[0] + side[1]*side[1] + side[2]*side[2]);
    side[0] *= inv_len; side[1] *= inv_len; side[2] *= inv_len;

    up[0] = side[1] * forward[2] - side[2] * forward[1];
    up[1] = side[2] * forward[0] - side[0] * forward[2];
    up[2] = side[0] * forward[1] - side[1] * forward[0];

    matrix[0] = side[0];  matrix[4] = side[1];  matrix[8] = side[2];   matrix[12] = 0.0f;
    matrix[1] = up[0];    matrix[5] = up[1];    matrix[9] = up[2];     matrix[13] = 0.0f;
    matrix[2] = -forward[0]; matrix[6] = -forward[1]; matrix[10] = -forward[2]; matrix[14] = 0.0f;
    matrix[3] = 0.0f;     matrix[7] = 0.0f;     matrix[11] = 0.0f;     matrix[15] = 1.0f;

    glMultMatrixf(matrix);
    glTranslatef(-eyex, -eyey, -eyez);
}

bool check_collision(Helicopter* heli, Scene* scene) {
    float heli_radius = 2.0f;
    for (int i = 0; i < MAX_TREES; i++) {
        Tree* tree = &scene->trees[i];
        float tree_radius = 1.5f * tree->scale; 
        float tree_height = 10.0f * tree->scale;
        float dx = heli->x - tree->x;
        float dz = heli->z - tree->z;
        float distance = sqrt(dx * dx + dz * dz);
        if (distance < (heli_radius + tree_radius) && heli->y < tree_height) {
            return true;
        }
    }
    return false;
}

// --- APP RENDSZER FÜGGVÉNYEK ---

bool init_app(App* app, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    app->window = SDL_CreateWindow(
        "Helikopter Szimulator",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );
    if (!app->window) return false;

    app->gl_context = SDL_GL_CreateContext(app->window);
    if (!app->gl_context) return false;

    app->is_running = true;
    app->last_time = SDL_GetTicks();
    
    memset(app->keys, 0, sizeof(app->keys));
    memset(app->special_keys, 0, sizeof(app->special_keys));
    
    app->light_intensity = 1.0f;
    app->sun_angle = 0.0f;
    app->show_help = false;
    
    init_scene(&app->scene);
    init_helicopter(&app->helicopter);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glEnable(GL_FOG);
    
    // Kezdeti perspektíva beállítás (GLU MENTES)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double pi = 3.14159265358979323846;
    double fH = tan((60.0 / 2.0) / 180.0 * pi) * 0.1;
    double fW = fH * ((double)width / (double)height);
    glFrustum(-fW, fW, -fH, fH, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);

    init_hud(&app->hud, 1024.0f, 768.0f);
    return true;
}

void handle_app_events(App* app) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            app->is_running = false;
        }
        else if (event.type == SDL_WINDOWEVENT) {
            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                int width = event.window.data1;
                int height = event.window.data2;
                if (height == 0) height = 1;
                glViewport(0, 0, width, height);
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                double pi = 3.14159265358979323846;
                double fH = tan((60.0 / 2.0) / 180.0 * pi) * 0.1;
                double fW = fH * ((double)width / (double)height);
                glFrustum(-fW, fW, -fH, fH, 0.1, 1000.0);
                glMatrixMode(GL_MODELVIEW);
            }
        }
        else if (event.type == SDL_KEYDOWN) {
            SDL_Keycode key = event.key.keysym.sym;
            if (key == SDLK_ESCAPE) {
                app->is_running = false;
            }
            if (key < 256) {
                app->keys[key] = true;
            }
            
            // Numpad és speciális gombok
            if (key == SDLK_KP_PLUS) app->keys['+'] = true;
            if (key == SDLK_KP_MINUS) app->keys['-'] = true;
            if (key == SDLK_UP)    app->special_keys[101] = true;
            if (key == SDLK_DOWN)  app->special_keys[103] = true;
            if (key == SDLK_LEFT)  app->special_keys[100] = true;
            if (key == SDLK_RIGHT) app->special_keys[102] = true;
            if (key == SDLK_F1)    app->special_keys[1] = true;
        }
        else if (event.type == SDL_KEYUP) {
            SDL_Keycode key = event.key.keysym.sym;
            if (key < 256) {
                app->keys[key] = false;
            }
            
            // Numpad és speciális gombok
            if (key == SDLK_KP_PLUS) app->keys['+'] = false;
            if (key == SDLK_KP_MINUS) app->keys['-'] = false;
            if (key == SDLK_UP)    app->special_keys[101] = false;
            if (key == SDLK_DOWN)  app->special_keys[103] = false;
            if (key == SDLK_LEFT)  app->special_keys[100] = false;
            if (key == SDLK_RIGHT) app->special_keys[102] = false;
            if (key == SDLK_F1)    app->special_keys[1] = false;
        }
    }
}

void update_app(App* app) {
    Uint32 current_time = SDL_GetTicks();
    float delta_time = (current_time - app->last_time) / 1000.0f;
    app->last_time = current_time;

    if (app->keys['i'] || app->keys['I'] || app->keys['+'] || app->keys[43]) app->light_intensity += 1.0f * delta_time;
    if (app->keys['k'] || app->keys['K'] || app->keys['-'] || app->keys[45]) app->light_intensity -= 1.0f * delta_time;
    if (app->keys['u'] || app->keys['U']) app->sun_angle -= 2.0f * delta_time;
    if (app->keys['o'] || app->keys['O']) app->sun_angle += 2.0f * delta_time;
    if (app->light_intensity < 0.0f) app->light_intensity = 0.0f; // fény min
    if (app->light_intensity > 1.0f) app->light_intensity = 1.0f; // fény max

    if (app->special_keys[1] || app->keys['h'] || app->keys['H']) {
        app->show_help = true;
    } else {
        app->show_help = false;
    }

    if (app->special_keys[101]) {
        app->helicopter.base_speed += 60.0f * delta_time;
        if (app->helicopter.base_speed > 240.0f) app->helicopter.base_speed = 240.0f;
    }
    if (app->special_keys[103]) {
        app->helicopter.base_speed -= 60.0f * delta_time;
        if (app->helicopter.base_speed < 0.0f) app->helicopter.base_speed = 0.0f;
    }
    
    float min_speed = 30.0f;
    float max_speed = 240.0f;
    if (app->helicopter.base_speed < min_speed) app->helicopter.base_speed = min_speed;
    if (app->helicopter.base_speed > max_speed) app->helicopter.base_speed = max_speed;
    
    float forward_speed = app->helicopter.base_speed * delta_time;
    float turn_speed = 90.0f * delta_time;
    float vertical_speed = 40.0f * delta_time;
    float old_x = app->helicopter.x;
    float old_y = app->helicopter.y;
    float old_z = app->helicopter.z;
    
    if (app->keys['w'] || app->keys['W']) move_helicopter(&app->helicopter, forward_speed, 1.0f);
    if (app->keys['s'] || app->keys['S']) move_helicopter(&app->helicopter, forward_speed, -1.0f);
    if (app->keys['a'] || app->keys['A']) turn_helicopter(&app->helicopter, turn_speed);
    if (app->keys['d'] || app->keys['D']) turn_helicopter(&app->helicopter, -turn_speed);
    if (app->keys['e'] || app->keys['E']) elevate_helicopter(&app->helicopter, vertical_speed);
    if (app->keys['q'] || app->keys['Q']) elevate_helicopter(&app->helicopter, -vertical_speed);
    
    update_helicopter(&app->helicopter, delta_time);
    update_scene(&app->scene, delta_time);
    
    float min_height = 2.5f; 
    if (app->helicopter.y < min_height) app->helicopter.y = min_height;
    
    if (check_collision(&app->helicopter, &app->scene)) {
        app->helicopter.x = old_x;
        app->helicopter.y = old_y;
        app->helicopter.z = old_z;
    }
}

void render_app(App* app) {
    float sky_r = 0.5f * app->light_intensity;
    float sky_g = 0.7f * app->light_intensity;
    float sky_b = 1.0f * app->light_intensity;
    glClearColor(sky_r, sky_g, sky_b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    GLfloat fog_color[] = {sky_r, sky_g, sky_b, 1.0f};
    glFogfv(GL_FOG_COLOR, fog_color);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, 60.0f);
    glFogf(GL_FOG_END, 180.0f);

    float rad = app->helicopter.rotation_y * 3.14159f / 180.0f;
    float cam_dist = 15.0f, cam_height = 8.0f;
    float cam_x = app->helicopter.x - sin(rad) * cam_dist;
    float cam_z = app->helicopter.z - cos(rad) * cam_dist;
    float cam_y = app->helicopter.y + cam_height;
    
    // GLU HELYETT A SAJÁT KAMERA
    my_lookAt(cam_x, cam_y, cam_z, app->helicopter.x, app->helicopter.y, app->helicopter.z, 0.0f, 1.0f, 0.0f);
    
    // --- FÉNY ÉS SÖTÉTEDÉS BEÁLLÍTÁSA ---
    float sun_x = cos(app->sun_angle) * 3.0f;
    float sun_z = sin(app->sun_angle) * 3.0f;
    GLfloat light_dir[] = { sun_x, 2.0f, sun_z, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_dir);

    float intensity = app->light_intensity;
    float amb = 0.2f * intensity;
    if (amb < 0.1f) amb = 0.1f; // A holdfény minimuma

    // A GL_LIGHT0 beállításai
    GLfloat current_ambient[] = {amb, amb, amb, 1.0f};
    GLfloat current_diffuse[] = {0.8f * intensity, 0.8f * intensity, 0.8f * intensity, 1.0f};
    GLfloat current_specular[] = {0.5f * intensity, 0.5f * intensity, 0.5f * intensity, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, current_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, current_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, current_specular);

    GLfloat global_ambient[] = {amb, amb, amb, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    draw_ground(&app->scene);

    if (app->light_intensity > 0.6f) {
        glDisable(GL_LIGHTING); 
        glPushMatrix();
        glTranslatef(0.0f, 0.05f, 0.0f); 
        
        float shadow_matrix[16] = {
            1.0f, 0.0f, 0.0f, 0.0f,
            -light_dir[0]/light_dir[1], 0.0f, -light_dir[2]/light_dir[1], 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
        glMultMatrixf(shadow_matrix);
        
        draw_trees(&app->scene, true); 
        draw_helicopter(&app->helicopter, true);
        glPopMatrix();
    }

    glEnable(GL_LIGHTING);

    draw_trees(&app->scene, false); 

    glColor3f(1.0f, 1.0f, 1.0f);
    GLfloat black_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black_emission);
    GLfloat mat_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    
    draw_helicopter(&app->helicopter, false);
    draw_particle_system(&app->scene.particle_system);

    render_hud(&app->hud, &app->helicopter, &app->scene, app->show_help);
    SDL_GL_SwapWindow(app->window);
}

void destroy_app(App* app) {
    if (app->gl_context) {
        SDL_GL_DeleteContext(app->gl_context);
    }
    if (app->window) {
        SDL_DestroyWindow(app->window);
    }
    SDL_Quit();
}