#include "app.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    App app;

    // Az alkalmazás inicializálása (Ablak, OpenGL context, játék elemek)
    if (!init_app(&app, 1024, 768)) {
        fprintf(stderr, "Hiba az alkalmazas inicializalasa soran!\n");
        return 1;
    }

    // Fő játék hurok
    while (app.is_running) {
        handle_app_events(&app);
        update_app(&app);
        render_app(&app);
    }

    // Erőforrások felszabadítása és leállás
    destroy_app(&app);

    return 0;
}