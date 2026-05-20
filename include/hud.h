#ifndef HUD_H
#define HUD_H

#include <stdbool.h>
#include "helicopter.h"
#include "scene.h"

/**
 * @brief A 2D-s felhasználói felület (HUD) és a minimap kezeléséért felelős adatszerkezet.
 */
typedef struct {
    float virtual_w; /**< A HUD virtuális felbontásának szélessége pixelben */
    float virtual_h; /**< A HUD virtuális felbontásának magassága pixelben */
} Hud;

/**
 * @brief Inicializálja a felhasználói felületet a megadott dimenziókkal.
 * @param hud Mutató a Hud struktúrára.
 * @param width A felület virtuális szélessége.
 * @param height A felület virtuális magassága.
 */
void init_hud(Hud* hud, float width, float height);

/**
 * @brief Kirajzolja a 2D-s elemeket a képernyőre (Minimap, Magasság/Sebesség, Súgó).
 * Kikapcsolja a 3D-s fényeket és a mélységtesztet a rajzolás idejére.
 * @param hud Mutató a Hud struktúrára.
 * @param heli Mutató a helikopterre (az adatok lekérdezéséhez).
 * @param scene Mutató a játéktérre (a fák és a tűz radarra rajzolásához).
 * @param show_help Megjelenítse-e a részletes billentyűzet-kiosztás menüt.
 */
void render_hud(Hud* hud, Helicopter* heli, Scene* scene, bool show_help);

#endif