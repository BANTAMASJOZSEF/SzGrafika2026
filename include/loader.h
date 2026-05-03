#ifndef LOADER_H
#define LOADER_H

#include <GL/gl.h>

/**
 * @brief Betölt egy képfájlt (pl. JPG, PNG) és OpenGL textúrává alakítja.
 * A beolvasáshoz és a kép dekódolásához az SDL2_image könyvtárat használja.
 * * @param path A képfájl elérési útvonala (pl. "assets/texture.png").
 * @return Az OpenGL textúra azonosítója (GLuint). Hiba esetén 0-t ad vissza.
 */
GLuint load_texture_sdl(const char* path);

/**
 * @brief Betölt egy Wavefront (.obj) 3D modellt a fájlrendszerből.
 * A modellt beolvassa, majd egy OpenGL Display List-be fordítja,
 * ami drasztikusan felgyorsítja a sokszögek későbbi kirajzolását.
 * * @param filename Az .obj fájl elérési útvonala (pl. "assets/model.obj").
 * @return Az OpenGL display list azonosítója (GLuint). Hiba esetén 0-t ad vissza.
 */
GLuint load_obj(const char* filename);

#endif