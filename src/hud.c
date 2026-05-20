#include "hud.h"
#include <GL/gl.h>
#include <math.h>
#include <stdio.h>

static void draw_text(const char* text, float x, float y, float scale) {
    float offset = 0.0f;
    while (*text) {
        char c = *text;
        if (c >= 'a' && c <= 'z') c -= 32; 
        if (c == ' ') { offset += scale * 1.5f; text++; continue; }
        
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

void init_hud(Hud* hud, float width, float height) {
    hud->virtual_w = width;
    hud->virtual_h = height;
}

void render_hud(Hud* hud, Helicopter* heli, Scene* scene, bool show_help) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    
    glOrtho(0.0, hud->virtual_w, hud->virtual_h, 0.0, -1.0, 1.0); 
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    
    // Minimap rajzolása
    float map_size = 200.0f; 
    float margin = 20.0f;
    float center_x = hud->virtual_w - (map_size / 2.0f) - margin;
    float center_y = hud->virtual_h - (map_size / 2.0f) - margin;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.6f);
    glBegin(GL_QUADS);
    glVertex2f(center_x - map_size/2, center_y - map_size/2);
    glVertex2f(center_x + map_size/2, center_y - map_size/2);
    glVertex2f(center_x + map_size/2, center_y + map_size/2);
    glVertex2f(center_x - map_size/2, center_y + map_size/2);
    glEnd();
    
    float angle_rad = heli->rotation_y * 3.14159f / 180.0f;
    float scale = 1.2f; 
    float cos_a = cos(angle_rad);
    float sin_a = sin(angle_rad);
    
    glColor3f(0.0f, 0.8f, 0.0f);
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    for(int i = 0; i < MAX_TREES; i++) {
        float dx = scene->trees[i].x - heli->x;
        float dz = scene->trees[i].z - heli->z;
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
    float fdx = scene->fire_x - heli->x;
    float fdz = scene->fire_z - heli->z;
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
    sprintf(hud_data, "ALT: %.1f M", heli->y);
    draw_text(hud_data, hud->virtual_w - 340, 40, 15.0f);

    sprintf(hud_data, "SPD: %.1f KM/H", heli->base_speed);
    draw_text(hud_data, hud->virtual_w - 340, 70, 15.0f);
    
    // --- RÉSZLETES HELP MENÜ ---
    if (show_help) {
        glColor4f(0.0f, 0.0f, 0.0f, 0.85f);
        float hm = 100.0f; 
        glBegin(GL_QUADS);
        glVertex2f(hm, hm);
        glVertex2f(hud->virtual_w - hm, hm);
        glVertex2f(hud->virtual_w - hm, hud->virtual_h - hm);
        glVertex2f(hm, hud->virtual_h - hm);
        glEnd();
        
        glColor3f(1.0f, 1.0f, 0.0f);
        draw_text("HASZNALATI UTMUTATO", hm + 150, hm + 40, 20.0f);

        float start_y = hm + 120;
        float line_h = 35.0f; 
        float text_size = 13.0f; 
        
        glColor3f(1.0f, 1.0f, 1.0f);
        draw_text("W, S      - ELORE / HATRA MOZGAS", hm + 40, start_y, text_size);
        draw_text("A, D      - BALRA / JOBBRA FORDULAS", hm + 40, start_y + line_h, text_size);
        draw_text("Q, E      - MAGASSAG (FEL / LE)", hm + 40, start_y + line_h*2, text_size);
        
        glColor3f(0.0f, 1.0f, 1.0f);
        draw_text("+ / -      - FENYERO PLUSZ / MINUSZ", hm + 40, start_y + line_h*3.5, text_size);
        draw_text("I / K     - FENYERO (ALTERNATIV)", hm + 40, start_y + line_h*4.5, text_size);

        draw_text("U / O - Nap szogenek allitasa", hm + 40, start_y + line_h*6, text_size);
        
        glColor3f(1.0f, 0.5f, 0.0f);
        draw_text("ESC       - KILEPES A JATEKBOL", hm + 40, start_y + line_h*8, text_size);
        draw_text("F1 VAGY H - EZ A MENU ELREJTESE", hm + 40, start_y + line_h*9, text_size);
    }

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}