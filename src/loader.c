#include "loader.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

GLuint load_texture_sdl(const char* path) {
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags)) return 0;

    SDL_Surface* surface = IMG_Load(path);
    if (surface == NULL) return 0;

    GLuint texture_name;
    glGenTextures(1, &texture_name);
    glBindTexture(GL_TEXTURE_2D, texture_name);

    int mode = GL_RGB;
    if (surface->format->BytesPerPixel == 4) mode = GL_RGBA;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SDL_FreeSurface(surface);
    return texture_name;
}

GLuint load_obj(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        return 0; //nincs meg a fajl
    }

    int v_cap = 10000, vt_cap = 10000, vn_cap = 10000;
    float (*v)[3] = malloc(v_cap * sizeof(*v)); // csúcspontok
    float (*vt)[2] = malloc(vt_cap * sizeof(*vt)); // textúrakoordináták
    float (*vn)[3] = malloc(vn_cap * sizeof(*vn)); // normálvektorok
    
    if (!v || !vt || !vn) {
        return 0;
    }

    int v_count = 1, vt_count = 1, vn_count = 1;
    char line[256];
    
    GLuint list_id = glGenLists(1);
    glNewList(list_id, GL_COMPILE);
    
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "v ", 2) == 0) {
            if (v_count >= v_cap) { v_cap *= 2; v = realloc(v, v_cap * sizeof(*v)); }
            sscanf(line, "v %f %f %f", &v[v_count][0], &v[v_count][1], &v[v_count][2]);
            v_count++;
        } else if (strncmp(line, "vt ", 3) == 0) {
            if (vt_count >= vt_cap) { vt_cap *= 2; vt = realloc(vt, vt_cap * sizeof(*vt)); }
            sscanf(line, "vt %f %f", &vt[vt_count][0], &vt[vt_count][1]);
            vt_count++;
        } else if (strncmp(line, "vn ", 3) == 0) {
            if (vn_count >= vn_cap) { vn_cap *= 2; vn = realloc(vn, vn_cap * sizeof(*vn)); }
            sscanf(line, "vn %f %f %f", &vn[vn_count][0], &vn[vn_count][1], &vn[vn_count][2]);
            vn_count++;
        } else if (strncmp(line, "f ", 2) == 0) {
            char* token = strtok(line + 2, " \t\n\r");
            
            glBegin(GL_POLYGON);
            
            while (token != NULL) {
                int vI = 0, uvI = 0, nI = 0;
                
                if (strstr(token, "//")) {
                    sscanf(token, "%d//%d", &vI, &nI);
                } else {
                    int matches = sscanf(token, "%d/%d/%d", &vI, &uvI, &nI);
                    if (matches == 1) sscanf(token, "%d", &vI);
                    else if (matches == 2) sscanf(token, "%d/%d", &vI, &uvI);
                }
                
                if (vI < 0) vI = v_count + vI;
                if (uvI < 0) uvI = vt_count + uvI;
                if (nI < 0) nI = vn_count + nI;

                if (nI > 0 && nI < vn_count) glNormal3f(vn[nI][0], vn[nI][1], vn[nI][2]);
                if (uvI > 0 && uvI < vt_count) glTexCoord2f(vt[uvI][0], vt[uvI][1]);
                if (vI > 0 && vI < v_count) glVertex3f(v[vI][0], v[vI][1], v[vI][2]);
                
                token = strtok(NULL, " \t\n\r"); 
            }
            glEnd();
        }
    }

    glEndList();
    fclose(file);
    
    free(v); free(vt); free(vn);
    
    return list_id;
}