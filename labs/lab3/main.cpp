//
// Created by igorc on 25.12.2019.
//

#include <GL/freeglut.h>
#include <GL/glaux.h>

void init();
void display();
void draw_cube();
void draw3();
void draw4();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void loop(int time);
void loadTextures();

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
GLuint texture[8];


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

    loadTextures();
    glEnable(GL_TEXTURE_2D);

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


    glColor4f(1.0,0.9,0.0, AlphaChannel);
    glNormal3f(-1,1,-1);
    glVertex3f( 1 + diverge, 0-diverge, 0+diverge);
    glVertex3f( 0 + diverge,-1-diverge, 0+diverge);
    glVertex3f( 0+ diverge, 0-diverge, 1+diverge);


    glColor4f(0.8,0.0,0.8, AlphaChannel);
    glNormal3f(-1,-1,1);
    glVertex3f(-1-diverge, 0-diverge, 0+diverge);
    glVertex3f( 0-diverge,-1-diverge, 0+diverge);
    glVertex3f( 0-diverge, 0-diverge, 1+diverge);

    glColor4f(0.0,1.0,0.0, AlphaChannel);
    glNormal3f(1,-1,-1);
    glVertex3f(-1-diverge, 0+diverge, 0+diverge);
    glVertex3f( 0-diverge, 1+diverge, 0+diverge);
    glVertex3f( 0-diverge, 0+diverge, 1+diverge);

    glColor4f(0.0,0.9,0.9, AlphaChannel);
    glNormal3f(-1,-1,1);
    glVertex3f( 1+diverge, 0+diverge, 0-diverge);
    glVertex3f( 0+diverge, 1+diverge, 0-diverge);
    glVertex3f( 0+diverge, 0+diverge,-1-diverge);

    glColor4f(0.0,0.0,1.0, AlphaChannel);
    glNormal3f(1,-1,-1);
    glVertex3f( 1+diverge, 0-diverge, 0-diverge);
    glVertex3f( 0+diverge,-1-diverge, 0-diverge);
    glVertex3f( 0+diverge, 0-diverge,-1-diverge);

    glColor4f(1.0,0.0,0.0, AlphaChannel);
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
    /*glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_TRIANGLES);
    glNormal3f(1,1,1);
    glTexCoord2f(0, 0);     glVertex3f(1+diverge,0+diverge,0+diverge);
    glTexCoord2f(1, 0);     glVertex3f(0+diverge,1+diverge,0+diverge);
    glTexCoord2f(0.5, 1);   glVertex3f(0+diverge,0+diverge,1+diverge);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_TRIANGLES);
    glNormal3f(-1,1,-1);
    glTexCoord2f(0, 0);     glVertex3f( 1+diverge, 0-diverge, 0+diverge);
    glTexCoord2f(1, 0);     glVertex3f( 0+diverge,-1-diverge, 0+diverge);
    glTexCoord2f(0.5, 1);   glVertex3f( 0+diverge, 0-diverge, 1+diverge);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glBegin(GL_TRIANGLES);
    glNormal3f(-1,-1,1);
    glTexCoord2f(0, 0);     glVertex3f(-1-diverge, 0-diverge, 0+diverge);
    glTexCoord2f(1, 0);     glVertex3f( 0-diverge,-1-diverge, 0+diverge);
    glTexCoord2f(0.5, 1);   glVertex3f( 0-diverge, 0-diverge, 1+diverge);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glBegin(GL_TRIANGLES);
    glNormal3f(1,-1,-1);
    glTexCoord2f(0, 0);     glVertex3f(-1-diverge, 0+diverge, 0+diverge);
    glTexCoord2f(1, 0);     glVertex3f( 0-diverge, 1+diverge, 0+diverge);
    glTexCoord2f(0.5, 1);   glVertex3f( 0-diverge, 0+diverge, 1+diverge);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glBegin(GL_TRIANGLES);
    glNormal3f(-1,-1,1);
    glTexCoord2f(0, 0);     glVertex3f( 1+diverge, 0+diverge, 0-diverge);
    glTexCoord2f(1, 0);     glVertex3f( 0+diverge, 1+diverge, 0-diverge);
    glTexCoord2f(0.5, 1);   glVertex3f( 0+diverge, 0+diverge,-1-diverge);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glBegin(GL_TRIANGLES);
    glNormal3f(1,-1,-1);
    glTexCoord2f(0, 0);     glVertex3f( 1+diverge, 0-diverge, 0-diverge);
    glTexCoord2f(1, 0);     glVertex3f( 0+diverge,-1-diverge, 0-diverge);
    glTexCoord2f(0.5, 1);   glVertex3f( 0+diverge, 0-diverge,-1-diverge);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture[6]);
    glBegin(GL_TRIANGLES);
    glNormal3f(1,1,1);
    glTexCoord2f(0, 0);     glVertex3f(-1-diverge, 0-diverge, 0-diverge);
    glTexCoord2f(1, 0);     glVertex3f( 0-diverge,-1-diverge, 0-diverge);
    glTexCoord2f(0.5, 1);   glVertex3f( 0-diverge, 0-diverge,-1-diverge);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture[7]);
    glBegin(GL_TRIANGLES);
    glNormal3f(-1,1,-1);
    glTexCoord2f(0, 0);     glVertex3f(-1-diverge, 0+diverge, 0-diverge);
    glTexCoord2f(1, 0);     glVertex3f( 0-diverge, 1+diverge, 0-diverge);
    glTexCoord2f(0.5, 1);   glVertex3f( 0-diverge, 0+diverge,-1-diverge);
    glEnd();*/
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

    draw3();

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
            AlphaChannel == 1.f ? AlphaChannel = 0.5f : AlphaChannel = 1.f;
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

void loadTextures() {
    /*AUX_RGBImageRec *texture1;
    texture1 = auxDIBImageLoad("texs/bricks.jpg");
    glGenTextures(1, &texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[0]);

    AUX_RGBImageRec *texture2;
    texture1 = auxDIBImageLoad("Data/cloth.jpg");
    glGenTextures(2, &texture[1]);
    glBindTexture(GL_TEXTURE_2D, texture[1]);

    AUX_RGBImageRec *texture3;
    texture1 = auxDIBImageLoad("Data/metal.jpg");
    glGenTextures(3, &texture[2]);
    glBindTexture(GL_TEXTURE_2D, texture[2]);

    AUX_RGBImageRec *texture4;
    texture1 = auxDIBImageLoad("Data/metal.jpg");
    glGenTextures(4, &texture[3]);
    glBindTexture(GL_TEXTURE_2D, texture[3]);

    AUX_RGBImageRec *texture5;
    texture1 = auxDIBImageLoad("Data/metal2.jpg");
    glGenTextures(5, &texture[4]);
    glBindTexture(GL_TEXTURE_2D, texture[4]);

    AUX_RGBImageRec *texture6;
    texture1 = auxDIBImageLoad("Data/metal3.jpg");
    glGenTextures(6, &texture[5]);
    glBindTexture(GL_TEXTURE_2D, texture[5]);

    AUX_RGBImageRec *texture7;
    texture1 = auxDIBImageLoad("Data/wood.jpg");
    glGenTextures(7, &texture[6]);
    glBindTexture(GL_TEXTURE_2D, texture[6]);

    AUX_RGBImageRec *texture8;
    texture1 = auxDIBImageLoad("Data/stones.jpg");
    glGenTextures(8, &texture[7]);
    glBindTexture(GL_TEXTURE_2D, texture[7]);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, texture1->data);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, texture2->sizeX, texture2->sizeY, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, texture2->data);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, texture3->sizeX, texture3->sizeY, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, texture3->data);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, texture4->sizeX, texture4->sizeY, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, texture4->data);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, texture5->sizeX, texture5->sizeY, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, texture5->data);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, texture6->sizeX, texture6->sizeY, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, texture6->data);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, texture7->sizeX, texture7->sizeY, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, texture7->data);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, texture8->sizeX, texture8->sizeY, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, texture8->data);*/
}





