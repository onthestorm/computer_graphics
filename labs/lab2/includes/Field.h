//
// Created by igorc on 09.10.2019.
//

#ifndef COMPUTER_GRAPHICS_FIELD_H
#define COMPUTER_GRAPHICS_FIELD_H

#include <iostream>
#include <vector>
#include <string>
//#include <Gl/gl.h>
#include <GL/freeglut.h>

enum Type {O, I, S, Z, L, J, T, NUM};

void showText(const char* str,int x, int y, GLfloat red,GLfloat green,GLfloat blue);

struct Block {
    int block;
    GLfloat red;
    GLfloat green;
    GLfloat blue;
};

static Block field[21][12];
static int points = 0;
static Type nextType;
static bool gameState = true;

class Field {
public:
    Field();
    ~Field();

    bool spawnNewFigure();

    bool moveDown();
    bool moveLeft();
    bool moveRight();
    void rotate();

    int checkRows();

    void setColor(int i, int j, int type);
    static void setColor(int type, GLfloat & red, GLfloat & green, GLfloat & blue);

    void startGame();
    void gameOver();
    bool getState();


    void display();
    static void draw();
    static void drawQuad(int cur_x, int cur_y, GLfloat cur_red, GLfloat cur_green, GLfloat cur_blue);
private:
    std::vector<std::pair<int, int>> current_figure;
    int figure_x;
    int figure_y;
    Type currentType;
    int rotation = 0;

    bool rotateCW();
    bool rotateOCW();
};


#endif //COMPUTER_GRAPHICS_FIELD_H
