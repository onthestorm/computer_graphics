//
// Created by igorc on 09.10.2019.
//

#include "Field.h"

using namespace std;

void loop(int value);
void keyboard(unsigned char key, int x, int y);

Field tetris;

int main(int argc, char** argv) {
    //srand(time(NULL));

    tetris.spawnNewFigure();

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize ( 600 , 600 );
    glutInitWindowPosition(650,200);
    glutCreateWindow("Tetris");

    glClearColor((GLfloat) 158/225, (GLfloat) 158/225,(GLfloat) 158/225, 0.0);
    glOrtho(0.f,600.f,0.f,600.f,-1.f,1.f);

    glutKeyboardFunc(keyboard);
    //glutReshapeFunc();
    tetris.display();
    glutPostRedisplay();
    glutTimerFunc(300, loop, 300);
    glutMainLoop();

    return 0;
}

void loop(int value) {
    if(tetris.getState()) {
        tetris.moveDown();
        glutPostRedisplay();
    }
    glutTimerFunc(300, loop, 300);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case ('a'): tetris.moveLeft(); break;
        case ('d'): tetris.moveRight(); break;
        case ('s'): tetris.moveDown(); break;
        case ('w'): tetris.rotate(); break;
        case ('r'): if(!tetris.getState()) {tetris.startGame(); break;}
        default: break;
    }
    glutPostRedisplay();
}



