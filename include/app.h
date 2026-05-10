#ifndef APP_H
#define APP_H

#include <stdbool.h>
#include "scene.h"
#include "helicopter.h"

/**
 * @brief A teljes alkalmazást (Application) összefogó struktúra.
 * Kezeli az ablakot, a bemeneteket, a kamerát, a fényerőt és a játékteret.
 */
typedef struct {
    int window_width;
    int window_height;
    
    bool keys[256];
    bool special_keys[256];
    double last_update_time;
    
    // Fényerő és Help menü állapot (Követelményekhez)
    float light_intensity;
    float sun_angle;
    bool show_help;
    
    Scene scene;
    Helicopter helicopter;
} App;

/**
 * @brief Inicializálja az alkalmazást és az OpenGL-t.
 */
void init_app(App* app);

/**
 * @brief Frissíti a logikát és a bemeneteket.
 */
void update_app(App* app, double delta_time);

/**
 * @brief Rendereli az alkalmazást (3D és 2D elemek).
 */
void render_app(App* app);

#endif