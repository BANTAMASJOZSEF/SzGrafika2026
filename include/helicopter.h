#ifndef HELICOPTER_H
#define HELICOPTER_H

#include <GL/gl.h>
#include <stdbool.h>

/**
 * @brief A helikopter állapotát és tulajdonságait tároló adatszerkezet.
 */
typedef struct {
    float x, y, z;          /**< A helikopter térbeli pozíciója (x, y, z koordináták) */
    float rotation_y;       /**< A helikopter elfordulása az Y tengely körül (fokokban) */
    float rotor_angle;      /**< A főrotor aktuális forgási szöge (az animációhoz) */
    float base_speed;       /**< A helikopter haladási sebessége (km/h vagy egység/sec) */
    GLuint model_id;        /**< A betöltött 3D modell (OBJ) OpenGL display list azonosítója */
    GLuint texture_id;      /**< A helikopterre feszített textúra OpenGL azonosítója */
} Helicopter;

/**
 * @brief Inicializálja a helikoptert.
 * Beállítja a kezdőpozíciót, sebességet, és betölti a 3D modellt valamint a textúrát.
 * @param heli Mutató a Helicopter struktúrára.
 */
void init_helicopter(Helicopter* heli);

/**
 * @brief Frissíti a helikopter belső állapotát (pl. rotor forgatása).
 * @param heli Mutató a Helicopter struktúrára.
 * @param delta_time Az előző képkocka óta eltelt idő másodpercben (időfüggő animációhoz).
 */
void update_helicopter(Helicopter* heli, double delta_time);

/**
 * @brief Mozgatja a helikoptert a saját orra (vagy hátulja) felé.
 * @param heli Mutató a Helicopter struktúrára.
 * @param speed A mozgás sebessége (delta_time-mal szorozva).
 * @param direction Az irány (1.0f = előre, -1.0f = hátra).
 */
void move_helicopter(Helicopter* heli, float speed, float direction);

/**
 * @brief Elforgatja a helikoptert az Y tengely körül (jobbra/balra).
 * @param heli Mutató a Helicopter struktúrára.
 * @param angle A forgatás szöge fokokban.
 */
void turn_helicopter(Helicopter* heli, float angle);

/**
 * @brief Változtatja a helikopter magasságát (Y koordinátáját).
 * @param heli Mutató a Helicopter struktúrára.
 * @param speed A magasságváltozás mértéke és iránya (pozitív = fel, negatív = le).
 */
void elevate_helicopter(Helicopter* heli, float speed);

/**
 * @brief Kirajzolja a helikoptert a 3D térbe.
 * @param heli Mutató a Helicopter struktúrára.
 * @param is_shadow Ha true, textúrák nélkül, sötét színnel (árnyékként) rajzolja ki a modellt.
 */
void draw_helicopter(Helicopter* heli, bool is_shadow);

#endif