#include "app.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>

// szövegrajzoló (A-Z, 0-9, jelek)
void draw_text(const char* text, float x, float y, float scale) {
    float offset = 0.0f;
    while (*text) {
        char c = *text;
        if (c >= 'a' && c <= 'z') c -= 32; // Nagybetűsítés
        
        if (c == ' ') {
            offset += scale * 1.5f;
            text++;
            continue;
        }
        
        glPushMatrix();
        glTranslatef(x + offset, y, 0.0f);
        glScalef(scale, scale, 1.0f);
        glBegin(GL_LINES);
        
        switch(c) {
            case 'A': glVertex2f(0,1); glVertex2f(0.5f,0); glVertex2f(0.5f,0); glVertex2f(1,1); glVertex2f(0.2f,0.6f); glVertex2f(0.8f,0.6f); break;
            case 'B': glVertex2f(0,0); glVertex2f(0,1); glVertex2f(0,0); glVertex2f(0.8f,0); glVertex2f(0.8f,0); glVertex2f(1,0.25f); glVertex2f(1,0.25f); glVertex2f(0.8f,0.5f); glVertex2f(0.8f,0.5f); glVertex2f(0,0.5f); glVertex2f(0.8f,0.5f); glVertex2f(1,0.75f); glVertex2f(1,0.75f); glVertex2f(0.8f,1); glVertex2f(0.8f,1); glVertex2f(0,1); break;
            case 'C': glVertex2f(1,0); glVertex2f(0,0); glVertex2f(0,0); glVertex2f(0,1); glVertex2f(0,1); glVertex2f(1,1); break;
            case 'D': glVertex2f(0,0); glVertex2f(0,1); glVertex2f(0,0); glVertex2f(0.7f,0); glVertex2f(0.7f,0); glVertex2f(1,0.5f); glVertex2f(1,0.5f); glVertex2f(0.7f,1); glVertex2f(0.7f,1); glVertex2f(0,1); break;
            case 'E': glVertex2f(1,0); glVertex2f(0,0); glVertex2f(0,0); glVertex2f(0,1); glVertex2f(0,1); glVertex2f(1,1); glVertex2f(0,0.5f); glVertex2f(0.8f,0.5f); break;
            case 'F': glVertex2f(1,0); glVertex2f(0,0); glVertex2f(0,0); glVertex2f(0,1); glVertex2f(0,0.5f); glVertex2f(0.8f,0.5f); break;
            case 'G': glVertex2f(1,0); glVertex2f(0,0); glVertex2f(0,0); glVertex2f(0,1); glVertex2f(0,1); glVertex2f(1,1); glVertex2f(1,1); glVertex2f(1,0.5f); glVertex2f(1,0.5f); glVertex2f(0.5f,0.5f); break;
            case 'H': glVertex2f(0,0); glVertex2f(0,1); glVertex2f(1,0); glVertex2f(1,1); glVertex2f(0,0.5f); glVertex2f(1,0.5f); break;
            case 'I': glVertex2f(0.5f,0); glVertex2f(0.5f,1); glVertex2f(0.2f,0); glVertex2f(0.8f,0); glVertex2f(0.2f,1); glVertex2f(0.8f,1); break;
            case 'J': glVertex2f(1,0); glVertex2f(1,1); glVertex2f(1,1); glVertex2f(0,1); glVertex2f(0,1); glVertex2f(0,0.5f); break;
            case 'K': glVertex2f(0,0); glVertex2f(0,1); glVertex2f(1,0); glVertex2f(0,0.5f); glVertex2f(0,0.5f); glVertex2f(1,1); break;
            case 'L': glVertex2f(0,0); glVertex2f(0,1); glVertex2f(0,1); glVertex2f(1,1); break;
            case 'M': glVertex2f(0,1); glVertex2f(0,0); glVertex2f(0,0); glVertex2f(0.5f,0.5f); glVertex2f(0.5f,0.5f); glVertex2f(1,0); glVertex2f(1,0); glVertex2f(1,1); break;
            case 'N': glVertex2f(0,1); glVertex2f(0,0); glVertex2f(0,0); glVertex2f(1,1); glVertex2f(1,1); glVertex2f(1,0); break;
            case 'O': case '0': glVertex2f(0,0); glVertex2f(1,0); glVertex2f(1,0); glVertex2f(1,1); glVertex2f(1,1); glVertex2f(0,1); glVertex2f(0,1); glVertex2f(0,0); break;
            case 'P': glVertex2f(0,1); glVertex2f(0,0); glVertex2f(0,0); glVertex2f(1,0); glVertex2f(1,0); glVertex2f(1,0.5f); glVertex2f(1,0.5f); glVertex2f(0,0.5f); break;
            case 'Q': glVertex2f(0,0); glVertex2f(1,0); glVertex2f(1,0); glVertex2f(1,1); glVertex2f(1,1); glVertex2f(0,1); glVertex2f(0,1); glVertex2f(0,0); glVertex2f(0.5f,0.5f); glVertex2f(1.2f,1.2f); break;
            case 'R': glVertex2f(0,1); glVertex2f(0,0); glVertex2f(0,0); glVertex2f(1,0); glVertex2f(1,0); glVertex2f(1,0.5f); glVertex2f(1,0.5f); glVertex2f(0,0.5f); glVertex2f(0,0.5f); glVertex2f(1,1); break;
            case 'S': case '5': glVertex2f(1,0); glVertex2f(0,0); glVertex2f(0,0); glVertex2f(0,0.5f); glVertex2f(0,0.5f); glVertex2f(1,0.5f); glVertex2f(1,0.5f); glVertex2f(1,1); glVertex2f(1,1); glVertex2f(0,1); break;
            case 'T': glVertex2f(0,0); glVertex2f(1,0); glVertex2f(0.5f,0); glVertex2f(0.5f,1); break;
            case 'U': glVertex2f(0,0); glVertex2f(0,1); glVertex2f(0,1); glVertex2f(1,1); glVertex2f(1,1); glVertex2f(1,0); break;
            case 'V': glVertex2f(0,0); glVertex2f(0.5f,1); glVertex2f(0.5f,1); glVertex2f(1,0); break;
            case 'W': glVertex2f(0,0); glVertex2f(0.2f,1); glVertex2f(0.2f,1); glVertex2f(0.5f,0.5f); glVertex2f(0.5f,0.5f); glVertex2f(0.8f,1); glVertex2f(0.8f,1); glVertex2f(1,0); break;
            case 'X': glVertex2f(0,0); glVertex2f(1,1); glVertex2f(1,0); glVertex2f(0,1); break;
            case 'Y': glVertex2f(0,0); glVertex2f(0.5f,0.5f); glVertex2f(1,0); glVertex2f(0.5f,0.5f); glVertex2f(0.5f,0.5f); glVertex2f(0.5f,1); break;
            case 'Z': glVertex2f(0,0); glVertex2f(1,0); glVertex2f(1,0); glVertex2f(0,1); glVertex2f(0,1); glVertex2f(1,1); break;
            
            case '1': glVertex2f(0.5f,0); glVertex2f(0.5f,1); glVertex2f(0.2f,0.2f); glVertex2f(0.5f,0); break;
            case '2': glVertex2f(0,0); glVertex2f(1,0); glVertex2f(1,0); glVertex2f(1,0.5f); glVertex2f(1,0.5f); glVertex2f(0,0.5f); glVertex2f(0,0.5f); glVertex2f(0,1); glVertex2f(0,1); glVertex2f(1,1); break;
            case '3': glVertex2f(0,0); glVertex2f(1,0); glVertex2f(1,0); glVertex2f(1,1); glVertex2f(1,1); glVertex2f(0,1); glVertex2f(0,0.5f); glVertex2f(1,0.5f); break;
            case '4': glVertex2f(0,0); glVertex2f(0,0.5f); glVertex2f(0,0.5f); glVertex2f(1,0.5f); glVertex2f(1,0); glVertex2f(1,1); break;
            case '6': glVertex2f(1,0); glVertex2f(0,0); glVertex2f(0,0); glVertex2f(0,1); glVertex2f(0,1); glVertex2f(1,1); glVertex2f(1,1); glVertex2f(1,0.5f); glVertex2f(1,0.5f); glVertex2f(0,0.5f); break;
            case '7': glVertex2f(0,0); glVertex2f(1,0); glVertex2f(1,0); glVertex2f(1,1); break;
            case '8': glVertex2f(0,0); glVertex2f(1,0); glVertex2f(1,0); glVertex2f(1,1); glVertex2f(1,1); glVertex2f(0,1); glVertex2f(0,1); glVertex2f(0,0); glVertex2f(0,0.5f); glVertex2f(1,0.5f); break;
            case '9': glVertex2f(0,1); glVertex2f(1,1); glVertex2f(1,1); glVertex2f(1,0); glVertex2f(1,0); glVertex2f(0,0); glVertex2f(0,0); glVertex2f(0,0.5f); glVertex2f(0,0.5f); glVertex2f(1,0.5f); break;
            
            case '-': glVertex2f(0,0.5f); glVertex2f(1,0.5f); break;
            case '+': glVertex2f(0,0.5f); glVertex2f(1,0.5f); glVertex2f(0.5f,0); glVertex2f(0.5f,1); break;
            case '.': glVertex2f(0.4f,0.9f); glVertex2f(0.6f,0.9f); break;
            case ',': glVertex2f(0.4f,0.9f); glVertex2f(0.6f,0.9f); glVertex2f(0.6f,0.9f); glVertex2f(0.4f,1.1f); break;
            case ':': glVertex2f(0.4f,0.2f); glVertex2f(0.6f,0.2f); glVertex2f(0.4f,0.8f); glVertex2f(0.6f,0.8f); break;
            case '/': glVertex2f(0,1); glVertex2f(1,0); break;
            case '(': glVertex2f(0.5f,0); glVertex2f(0,0.5f); glVertex2f(0,0.5f); glVertex2f(0.5f,1); break;
            case ')': glVertex2f(0.5f,0); glVertex2f(1,0.5f); glVertex2f(1,0.5f); glVertex2f(0.5f,1); break;
        }
        
        glEnd();
        glPopMatrix();
        
        offset += scale * 1.5f; 
        text++;
    }
}

bool check_collision(Helicopter* heli, Scene* scene) {
    float heli_radius = 2.0f;
    for (int i = 0; i < MAX_TREES; i++) {
        Tree* tree = &scene->trees[i];
        float tree_radius = 1.5f * tree->scale; 
        float tree_height = 8.0f * tree->scale;
        float dx = heli->x - tree->x;
        float dz = heli->z - tree->z;
        float distance = sqrt(dx * dx + dz * dz);
        if (distance < (heli_radius + tree_radius) && heli->y < tree_height) {
            return true;
        }
    }
    return false;
}

void init_app(App* app) {
    for (int i = 0; i < 256; i++) {
        app->keys[i] = false;
        app->special_keys[i] = false;
    }
    app->last_update_time = 0.0;
    app->light_intensity = 1.0f; 
    app->show_help = false;
    
    init_scene(&app->scene);
    init_helicopter(&app->helicopter);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glEnable(GL_FOG);
}

void update_app(App* app, double delta_time) {
    if (app->keys['i'] || app->keys['I'] || app->keys['+'] || app->keys[43]) app->light_intensity += 1.0f * delta_time;
    if (app->keys['k'] || app->keys['K'] || app->keys['-'] || app->keys[45]) app->light_intensity -= 1.0f * delta_time;
    if (app->light_intensity < 0.0f) app->light_intensity = 0.0f;
    if (app->light_intensity > 2.0f) app->light_intensity = 2.0f;

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
    
    float min_height = 3.0f; 
    if (app->helicopter.y < min_height) app->helicopter.y = min_height;
    
    if (check_collision(&app->helicopter, &app->scene)) {
        app->helicopter.x = old_x;
        app->helicopter.y = old_y;
        app->helicopter.z = old_z;
    }

    float heli_r = 2.0f;
    if (app->helicopter.x + heli_r > app->scene.wall_x - app->scene.wall_width/2.0f &&
        app->helicopter.x - heli_r < app->scene.wall_x + app->scene.wall_width/2.0f &&
        app->helicopter.z + heli_r > app->scene.wall_z - app->scene.wall_depth/2.0f &&
        app->helicopter.z - heli_r < app->scene.wall_z + app->scene.wall_depth/2.0f &&
        app->helicopter.y < app->scene.wall_height) {
        
        app->helicopter.x = old_x;
        app->helicopter.y = old_y;
        app->helicopter.z = old_z;
        
        if (app->helicopter.base_speed > 100.0f) {
            app->helicopter.rotation_y += 180.0f;
            app->helicopter.base_speed *= 0.5f;   
        } else {
            app->helicopter.base_speed = 0.0f;    
        }
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
    gluLookAt(cam_x, cam_y, cam_z, app->helicopter.x, app->helicopter.y, app->helicopter.z, 0.0f, 1.0f, 0.0f);
    
    GLfloat light_dir[] = { 1.5f, 2.0f, 1.0f, 0.0f }; 
    glLightfv(GL_LIGHT0, GL_POSITION, light_dir);

    GLfloat current_ambient[] = {0.2f * app->light_intensity, 0.2f * app->light_intensity, 0.2f * app->light_intensity, 1.0f};
    GLfloat current_diffuse[] = {0.8f * app->light_intensity, 0.8f * app->light_intensity, 0.8f * app->light_intensity, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, current_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, current_diffuse);

    draw_ground(&app->scene);

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

    glEnable(GL_LIGHTING);

    draw_trees(&app->scene, false); 
    draw_wall(&app->scene);
    draw_helicopter(&app->helicopter, false);
    draw_particles(&app->scene);

    // --- VIRTUALIS 2D-S FELULET RAJZOLASA (Meretezes elleni vedelem) ---
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    
    // FIX BELSŐ FELBONTÁS A HUD-HOZ (Így sosem lóg ki semmi!)
    float virtual_w = 1024.0f;
    float virtual_h = 768.0f;
    gluOrtho2D(0, virtual_w, virtual_h, 0); 
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    
    // Minimap rajzolása
    float map_size = 200.0f; 
    float margin = 20.0f;
    float center_x = virtual_w - (map_size / 2.0f) - margin;
    float center_y = virtual_h - (map_size / 2.0f) - margin;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.6f);
    glBegin(GL_QUADS);
    glVertex2f(center_x - map_size/2, center_y - map_size/2);
    glVertex2f(center_x + map_size/2, center_y - map_size/2);
    glVertex2f(center_x + map_size/2, center_y + map_size/2);
    glVertex2f(center_x - map_size/2, center_y + map_size/2);
    glEnd();
    
    float angle_rad = app->helicopter.rotation_y * 3.14159f / 180.0f;
    float scale = 1.2f; 
    float cos_a = cos(angle_rad);
    float sin_a = sin(angle_rad);
    
    glColor3f(0.0f, 0.8f, 0.0f);
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    for(int i = 0; i < MAX_TREES; i++) {
        float dx = app->scene.trees[i].x - app->helicopter.x;
        float dz = app->scene.trees[i].z - app->helicopter.z;
        float lx = dx * cos_a - dz * sin_a;
        float lz = dx * sin_a + dz * cos_a;
        if (fabs(lx * scale) < map_size/2 && fabs(lz * scale) < map_size/2) {
            glVertex2f(center_x - lx * scale, center_y - lz * scale);
        }
    }
    glEnd();
    
    glColor3f(1.0f, 0.5f, 0.0f);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    float fdx = app->scene.fire_x - app->helicopter.x;
    float fdz = app->scene.fire_z - app->helicopter.z;
    float flx = fdx * cos_a - fdz * sin_a;
    float flz = fdx * sin_a + fdz * cos_a;
    if (fabs(flx * scale) < map_size/2 && fabs(flz * scale) < map_size/2) {
        glVertex2f(center_x - flx * scale, center_y - flz * scale);
    }
    glEnd();
    
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(center_x, center_y);
    for(int i = 0; i <= 360; i += 20) {
        float r = i * 3.14159f / 180.0f;
        glVertex2f(center_x + cos(r) * 6, center_y + sin(r) * 6);
    }
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(center_x, center_y - 15);
    glVertex2f(center_x - 6, center_y - 6);
    glVertex2f(center_x + 6, center_y - 6);
    glEnd();

    // --- HUD: Magasság és Sebesség ---
    char hud_data[64];
    glColor3f(1.0f, 1.0f, 0.0f); 
    sprintf(hud_data, "ALT: %.1f M", app->helicopter.y);
    draw_text(hud_data, virtual_w - 340, 40, 15.0f);

    sprintf(hud_data, "SPD: %.1f KM/H", app->helicopter.base_speed);
    draw_text(hud_data, virtual_w - 340, 70, 15.0f);
    
    // --- RÉSZLETES HELP MENÜ ---
    if (app->show_help) {
        glColor4f(0.0f, 0.0f, 0.0f, 0.85f);
        float hm = 100.0f; // Fix margó a virtuális felbontáshoz képest
        glBegin(GL_QUADS);
        glVertex2f(hm, hm);
        glVertex2f(virtual_w - hm, hm);
        glVertex2f(virtual_w - hm, virtual_h - hm);
        glVertex2f(hm, virtual_h - hm);
        glEnd();
        
        // Címsor (Kicsinyítve 25-ről 20-ra)
        glColor3f(1.0f, 1.0f, 0.0f);
        draw_text("HASZNALATI UTMUTATO", hm + 150, hm + 40, 20.0f);

        float start_y = hm + 120;
        float line_h = 35.0f; // Sortávolság is kisebb lett (45-ről 35-re)
        float text_size = 13.0f; // Szövegméret 18-ról 13-ra csökkentve!
        
        // Mozgás szekció
        glColor3f(1.0f, 1.0f, 1.0f);
        draw_text("W, S      - ELORE / HATRA MOZGAS", hm + 40, start_y, text_size);
        draw_text("A, D      - BALRA / JOBBRA FORDULAS", hm + 40, start_y + line_h, text_size);
        draw_text("Q, E      - MAGASSAG (FEL / LE)", hm + 40, start_y + line_h*2, text_size);
        
        // Fények szekció
        glColor3f(0.0f, 1.0f, 1.0f);
        draw_text("+ / -      - FENYERO PLUSZ / MINUSZ", hm + 40, start_y + line_h*3.5f, text_size);
        draw_text("I / K     - FENYERO (ALTERNATIV)", hm + 40, start_y + line_h*4.5f, text_size);
        
        // Egyéb szekció
        glColor3f(1.0f, 0.5f, 0.0f);
        draw_text("ESC       - KILEPES A JATEKBOL", hm + 40, start_y + line_h*6, text_size);
        draw_text("F1 VAGY H - EZ A MENU ELREJTESE", hm + 40, start_y + line_h*7, text_size);
    }

    glDisable(GL_BLEND);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
