#ifndef HUD_H
#define HUD_H

#include <stdbool.h>
#include "helicopter.h"
#include "scene.h"

typedef struct {
    float virtual_w;
    float virtual_h;
} Hud;

void init_hud(Hud* hud, float width, float height);
void render_hud(Hud* hud, Helicopter* heli, Scene* scene, bool show_help);

#endif