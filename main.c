#include <GL/glut.h>
#include "app.h"

App app;

void display() {
    render_app(&app);
}

void reshape(int width, int height) {
    app.window_width = width;
    app.window_height = height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)width / (double)height, 0.1, 1000.0);
}

void idle() {
    double current_time = (double)glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    double delta_time = current_time - app.last_update_time;
    app.last_update_time = current_time;

    update_app(&app, delta_time);
    glutPostRedisplay();
}

void key_down(unsigned char key, int x, int y) {
    app.keys[key] = true;
    if (key == 27) exit(0); // ESC kilépés
}

void key_up(unsigned char key, int x, int y) {
    app.keys[key] = false;
}

void special_down(int key, int x, int y) {
    if (key < 256) app.special_keys[key] = true;
}

void special_up(int key, int x, int y) {
    if (key < 256) app.special_keys[key] = false;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("Helikopter Szimulator QTMKZZ");

    init_app(&app);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutKeyboardFunc(key_down);
    glutKeyboardUpFunc(key_up);
    glutSpecialFunc(special_down);
    glutSpecialUpFunc(special_up);

    app.last_update_time = (double)glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    
    glutMainLoop();
    return 0;
}