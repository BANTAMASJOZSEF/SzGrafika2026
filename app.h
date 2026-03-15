#ifndef APP_H
#define APP_H

#include <stdbool.h>
#include "scene.h"
#include "helicopter.h"

typedef struct {
    Scene scene;
    Helicopter helicopter;
    bool special_keys[256];
    bool keys[256];
    double last_update_time;
    int window_width;
    int window_height;
} App;

void init_app(App* app);
void update_app(App* app, double delta_time);
void render_app(App* app);

#endif