#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "scene.h"
#include "helicopter.h"
#include "hud.h"

/**
 * @brief A teljes alkalmazást (Application) összefogó struktúra.
 * Magába foglalja az ablakkezelést, az OpenGL kontextust, a bemeneteket, 
 * az időzítést, valamint a játékteret és a járművet (tiszta OOP tokozás).
 */
typedef struct {
    SDL_Window* window;         /**< Az alkalmazás SDL ablaka */
    SDL_GLContext gl_context;   /**< Az OpenGL grafikai kontextus */
    bool is_running;            /**< Futási állapotjelző flag a fő hurokhoz */
    Uint32 last_time;           /**< Az időzítéshez (delta time) használt előző időbélyeg */
    
    bool keys[256];             /**< Normál billentyűk állapotát tároló tömb */
    bool special_keys[256];     /**< Speciális billentyűk (pl. nyilak) állapotát tároló tömb */
    
    // Fényerő és Help menü állapot (Követelményekhez)
    float light_intensity;      /**< A környezeti fény és köd intenzitása (0.0 - 2.0) */
    float sun_angle;            /**< A Nap aktuális elfordulási szöge az X-Z síkon */
    bool show_help;             /**< A Súgó (Help) képernyő megjelenítését vezérlő flag */
    
    Scene scene;                /**< A környezetet (erdő, talaj, részecskék) kezelő objektum */
    Helicopter helicopter;      /**< A helikopter fizikai és grafikai modellje */
    Hud hud;                    /**< A hud kirajzolása */
} App;

/**
 * @brief Inicializálja az alkalmazást, létrehozza az ablakot, az OpenGL kontextust és az al-objektumokat.
 * @param app Mutató az App struktúrára.
 * @param width Az ablak kívánt szélessége pixelben.
 * @param height Az ablak kívánt magassága pixelben.
 * @return true Sikeres inicializálás esetén, false hiba esetén.
 */
bool init_app(App* app, int width, int height);

/**
 * @brief Kezeli az operációs rendszer felől érkező SDL eseményeket (ablak bezárása, billentyűzet input).
 * @param app Mutató az App struktúrára.
 */
void handle_app_events(App* app);

/**
 * @brief Frissíti az alkalmazás belső logikáját, kiszámítja a delta time-ot, kezeli a mozgást és az ütközéseket.
 * @param app Mutató az App struktúrára.
 */
void update_app(App* app);

/**
 * @brief Rendereli a teljes 3D-s színteret (világ, helikopter, árnyékok), majd átvált 2D-be a HUD és a Minimap rajzolásához.
 * @param app Mutató az App struktúrára.
 */
void render_app(App* app);

/**
 * @brief Felszabadítja az alkalmazás által lefoglalt erőforrásokat, törli az OpenGL kontextust és bezárja az ablakot.
 * @param app Mutató az App struktúrára.
 */
void destroy_app(App* app);

/**
 * @brief Segédfüggvény szöveg kirajzolásához a 2D-s felületen.
 * @param text A kirajzolni kívánt karakterlánc.
 * @param x Vízszintes képernyő-koordináta.
 * @param y Függőleges képernyő-koordináta.
 * @param scale Szöveg méretezése (skálázása).
 */
void draw_text(const char* text, float x, float y, float scale);

#endif