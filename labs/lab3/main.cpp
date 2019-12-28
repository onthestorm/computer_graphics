//
// Created by igorc on 25.12.2019.
//

#include <GL/freeglut.h>
#include <GL/glaux.h>
#include <CImg.h>

void init();
void display();
void draw_cube();
void draw3();
void draw4();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void loop(int time);

GLfloat diverge = 0.02;
GLfloat AlphaChannel = 1;
bool rotating = false;
bool rotated = false;
bool display_cube = false;

GLfloat lght_rot = 1, lght_rotD = 0.6, shift = -5;
GLfloat lght_pos[4] = {2, 0, 0, 1};

GLfloat angle_x = 0;
GLfloat angle_y = 0;

GLuint cube;

typedef struct T_GL_DATA {
    size_t width, height;
    unsigned char *data;
} TGL;

GLuint textures[8];
TGL texts[8];

using namespace cimg_library;


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA|GLUT_ALPHA);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(650, 200);
    glutCreateWindow("Octaedr");
    init();

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutTimerFunc(30, loop, 1);
    glutMainLoop();

    return 0;
}

void init() {
    glClearColor(0, 0, 0, 1);


    glTranslatef(0,0,shift);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glLightfv(GL_LIGHT0, GL_POSITION, lght_pos);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    glEnable(GL_BLEND); //Enable blending.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set blending function.



    cube = glGenLists(1);
    draw_cube();

}

void draw_cube() {
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glNewList(cube, GL_COMPILE);
        for(int i = 0; i < 31; i++) {
                glBegin(GL_LINE_LOOP);
                    glVertex3f(-1.5, 1.5 - i * 0.1, 1.5);
                    glVertex3f(1.5, 1.5 - i * 0.1, 1.5);
                    glVertex3f(1.5, 1.5 - i * 0.1, -1.5);
                    glVertex3f(-1.5, 1.5 - i * 0.1, -1.5);
                glEnd();
                glBegin(GL_LINE_LOOP);
                    glVertex3f(1.5 - i * 0.1, 1.5, 1.5);
                    glVertex3f(1.5 - i * 0.1, -1.5, 1.5);
                    glVertex3f(1.5 - i * 0.1, -1.5, -1.5);
                    glVertex3f(1.5 - i * 0.1, 1.5, -1.5);
                glEnd();
                glBegin(GL_LINE_LOOP);
                    glVertex3f(-1.5, 1.5, 1.5 - i * 0.1);
                    glVertex3f(1.5, 1.5, 1.5 - i * 0.1);
                    glVertex3f(1.5, -1.5, 1.5 - i * 0.1);
                    glVertex3f(-1.5, -1.5, 1.5 - i * 0.1);
                glEnd();

        }
    glEndList();
}

void draw3() {
    glBegin(GL_TRIANGLES);

    glColor4f(1.0,0.5,0.0, AlphaChannel);
    glNormal3f(1,1,1);
    glVertex3f( 1+diverge, 0+diverge, 0+diverge);
    glVertex3f( 0+diverge, 1+diverge, 0+diverge);
    glVertex3f( 0+diverge, 0+diverge, 1+diverge);


    glColor4f(1.0,0.0,0.0, AlphaChannel);
    glNormal3f(-1,1,-1);
    glVertex3f( 1 + diverge, 0-diverge, 0+diverge);
    glVertex3f( 0 + diverge,-1-diverge, 0+diverge);
    glVertex3f( 0+ diverge, 0-diverge, 1+diverge);


    glColor4f(1.0,0.0,0.0, AlphaChannel);
    glNormal3f(-1,-1,1);
    glVertex3f(-1-diverge, 0-diverge, 0+diverge);
    glVertex3f( 0-diverge,-1-diverge, 0+diverge);
    glVertex3f( 0-diverge, 0-diverge, 1+diverge);

    glColor4f(0.0,0.0,1.0, AlphaChannel);
    glNormal3f(1,-1,-1);
    glVertex3f(-1-diverge, 0+diverge, 0+diverge);
    glVertex3f( 0-diverge, 1+diverge, 0+diverge);
    glVertex3f( 0-diverge, 0+diverge, 1+diverge);

    glColor4f(0.0,1.0,1.0, AlphaChannel);
    glNormal3f(-1,-1,1);
    glVertex3f( 1+diverge, 0+diverge, 0-diverge);
    glVertex3f( 0+diverge, 1+diverge, 0-diverge);
    glVertex3f( 0+diverge, 0+diverge,-1-diverge);

    glColor4f(0.7,1.0,0.2, AlphaChannel);
    glNormal3f(1,-1,-1);
    glVertex3f( 1+diverge, 0-diverge, 0-diverge);
    glVertex3f( 0+diverge,-1-diverge, 0-diverge);
    glVertex3f( 0+diverge, 0-diverge,-1-diverge);

    glColor4f(1.0,0.0,0.5, AlphaChannel);
    glNormal3f(1,1,1);
    glVertex3f(-1-diverge, 0-diverge, 0-diverge);
    glVertex3f( 0-diverge,-1-diverge, 0-diverge);
    glVertex3f( 0-diverge, 0-diverge,-1-diverge);

    glNormal3f(-1,1,-1);
    glColor4f(1.0,0.0,0.0, AlphaChannel);
    glVertex3f(-1-diverge, 0+diverge, 0-diverge);

    glColor4f(0.0,1.0,0.0, AlphaChannel);
    glVertex3f( 0-diverge, 1+diverge, 0-diverge);

    glColor4f(0.0,0.0,1.0, AlphaChannel);
    glVertex3f( 0-diverge, 0+diverge,-1-diverge);

    glEnd();
}

void draw4() {


    const char *txrs[]{"texs/bricks.bmp",
                       "texs/cloth.bmp",
                       "texs/metal.bmp",
                       "texs/metal2.bmp",
                       "texs/metal3.bmp",
                       "texs/skin.bmp",
                       "texs/stones.bmp",
                       "texs/wood.bmp"};

    CImg<unsigned char> *src = new CImg<unsigned char>();


    glGenTextures(8, textures);
    for (int i = 0; i < 8; i++) {
        src->load_bmp(txrs[i]);

        texts[i].width = src->width();
        texts[i].height = src->height();
        texts[i].data = new unsigned char[src->size()];
        memcpy(texts[i].data, src->data(), src->size());


        src->clear();

        glBindTexture(GL_TEXTURE_2D, textures[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texts[i].width, texts[i].height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                     texts[i].data);
    }

    delete src;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glBegin(GL_TRIANGLES);
    glNormal3f(1, 1, 1);
    glTexCoord2f(0, 0);
    glVertex3f(1 + diverge, 0 + diverge, 0 + diverge);
    glTexCoord2f(1, 0);
    glVertex3f(0 + diverge, 1 + diverge, 0 + diverge);
    glTexCoord2f(0.5, 1);
    glVertex3f(0 + diverge, 0 + diverge, 1 + diverge);
    glEnd();


    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glBegin(GL_TRIANGLES);
    glNormal3f(-1, 1, -1);
    glTexCoord2f(0, 0);
    glVertex3f(1 + diverge, 0 - diverge, 0 + diverge);
    glTexCoord2f(1, 0);
    glVertex3f(0 + diverge, -1 - diverge, 0 + diverge);
    glTexCoord2f(0.5, 1);
    glVertex3f(0 + diverge, 0 - diverge, 1 + diverge);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glBegin(GL_TRIANGLES);
    glNormal3f(-1, -1, 1);
    glTexCoord2f(0, 0);
    glVertex3f(-1 - diverge, 0 - diverge, 0 + diverge);
    glTexCoord2f(1, 0);
    glVertex3f(0 - diverge, -1 - diverge, 0 + diverge);
    glTexCoord2f(0.5, 1);
    glVertex3f(0 - diverge, 0 - diverge, 1 + diverge);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[3]);
    glBegin(GL_TRIANGLES);
    glNormal3f(1, -1, -1);
    glTexCoord2f(0, 0);
    glVertex3f(-1 - diverge, 0 + diverge, 0 + diverge);
    glTexCoord2f(1, 0);
    glVertex3f(0 - diverge, 1 + diverge, 0 + diverge);
    glTexCoord2f(0.5, 1);
    glVertex3f(0 - diverge, 0 + diverge, 1 + diverge);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[4]);
    glBegin(GL_TRIANGLES);
    glNormal3f(-1, -1, 1);
    glTexCoord2f(0, 0);
    glVertex3f(1 + diverge, 0 + diverge, 0 - diverge);
    glTexCoord2f(1, 0);
    glVertex3f(0 + diverge, 1 + diverge, 0 - diverge);
    glTexCoord2f(0.5, 1);
    glVertex3f(0 + diverge, 0 + diverge, -1 - diverge);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[5]);
    glBegin(GL_TRIANGLES);
    glNormal3f(1, -1, -1);
    glTexCoord2f(0, 0);
    glVertex3f(1 + diverge, 0 - diverge, 0 - diverge);
    glTexCoord2f(1, 0);
    glVertex3f(0 + diverge, -1 - diverge, 0 - diverge);
    glTexCoord2f(0.5, 1);
    glVertex3f(0 + diverge, 0 - diverge, -1 - diverge);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[6]);
    glBegin(GL_TRIANGLES);
    glNormal3f(1, 1, 1);
    glTexCoord2f(0, 0);
    glVertex3f(-1 - diverge, 0 - diverge, 0 - diverge);
    glTexCoord2f(1, 0);
    glVertex3f(0 - diverge, -1 - diverge, 0 - diverge);
    glTexCoord2f(0.5, 1);
    glVertex3f(0 - diverge, 0 - diverge, -1 - diverge);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[7]);
    glBegin(GL_TRIANGLES);
    glNormal3f(-1, 1, -1);
    glTexCoord2f(0, 0);
    glVertex3f(-1 - diverge, 0 + diverge, 0 - diverge);
    glTexCoord2f(1, 0);
    glVertex3f(0 - diverge, 1 + diverge, 0 - diverge);
    glTexCoord2f(0.5, 1);
    glVertex3f(0 - diverge, 0 + diverge, -1 - diverge);

    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void display(void) {
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка буфера цвета и буфера глубины

    glPushMatrix();
    glLoadIdentity(); // единичная матрица

    glTranslatef(0, 0, shift);
    glRotatef(lght_rot, 0.0, 1.0, 0.0);
    glLightfv(GL_LIGHT0, GL_POSITION, lght_pos);
    glTranslatef(lght_pos[0], lght_pos[1], lght_pos[2]);
    glColor4f(1.0, 1.0, 0.0, 1.0);
    GLUquadricObj *quad = gluNewQuadric();
    gluQuadricDrawStyle(quad, GLU_LINE);
    gluSphere(quad, 0.25, 10, 10);


    glPopMatrix();

    if(rotated) {
        glRotatef(angle_x, 1.0, 0.0, 0.0);
        glRotatef(angle_y, 0.0, 1.0, 0.0);
    }

    glColor4f(1.0,1.0,1.0,1.0);


    draw4();


    glColor4f(1.0,1.0,1.0, AlphaChannel);

    if(display_cube)
        glCallList(cube);

    angle_x = 0;
    angle_y = 0;
    rotated = false;

    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.f, (GLfloat)w/(GLfloat)h, 0.1f, 100.0f );//насколько широко открыто око камеры (120 градусов)
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch(key)
    {
        case 's':
            angle_x+=1;
            rotated = true;
            break;
        case 'w':
            angle_x-=1;
            rotated = true;
            break;
        case 'a':
            angle_y+=1;
            rotated = true;
            break;
        case 'd':
            angle_y-=1;
            rotated = true;
            break;
        case 'r':
            rotating = !rotating;
            rotated = true;
            break;
        case 'q':
            if(diverge == 0) {
                diverge = 0.02;
                break;
            } else {
                diverge = 0;
                break;
            }
        case 'f':
            AlphaChannel == 1.f ? AlphaChannel = 0.2f : AlphaChannel = 1.f;
            break;
        case 'c' :
            display_cube = !display_cube;
            break;

    }
    glutPostRedisplay();
}

void loop(int time) {
    lght_rot += lght_rotD;

    if(rotating) {
        angle_y += 1;
        rotated = true;
    }

    glutPostRedisplay();
    glutTimerFunc(30, loop, 1);
}




