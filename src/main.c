#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdbool.h>
#include "app.h"

App app;

void reshape(int width, int height) {
    if (height == 0) height = 1; // Nullával osztás elleni védelem
    app.window_width = width;
    app.window_height = height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)width / (double)height, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_Window* window = SDL_CreateWindow(
        "Helikopter Szimulator QTMKZZ",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1024, 768,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);

    init_app(&app);
    reshape(1024, 768);

    Uint32 last_time = SDL_GetTicks();
    bool running = true;
    SDL_Event event;

    while (running) {
        Uint32 current_time = SDL_GetTicks();
        double delta_time = (current_time - last_time) / 1000.0;
        last_time = current_time;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_WINDOWEVENT) {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    reshape(event.window.data1, event.window.data2);
                }
            } else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
                bool is_down = (event.type == SDL_KEYDOWN);
                SDL_Keycode key = event.key.keysym.sym;
                
                // Sima gombok (Betűk, számok, alap írásjelek)
                if (key < 256) {
                    app.keys[key] = is_down;
                } else {
                    // Speciális gombok bekötése
                    if (key == SDLK_UP) app.special_keys[101] = is_down;
                    if (key == SDLK_DOWN) app.special_keys[103] = is_down;
                    if (key == SDLK_LEFT) app.special_keys[100] = is_down;
                    if (key == SDLK_RIGHT) app.special_keys[102] = is_down;
                    
                    //F1 gomb bekötése a Help menühöz
                    if (key == SDLK_F1) app.special_keys[1] = is_down;
                    
                    // ÚJ: Numpad + és - gombok bekötése a fényerőhöz
                    if (key == SDLK_KP_PLUS) app.keys['+'] = is_down;
                    if (key == SDLK_KP_MINUS) app.keys['-'] = is_down;
                }
            }
        }

        // ESC gombbal kilépés
        if (app.keys[27]) {
            running = false;
        }

        update_app(&app, delta_time);
        render_app(&app);
        
        SDL_GL_SwapWindow(window);
        SDL_Delay(16);
    }

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}