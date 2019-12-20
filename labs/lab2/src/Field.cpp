//
// Created by igorc on 09.10.2019.
//

#include "Field.h"

#define y val.first
#define x val.second

using namespace std;

const int tetramino[28][4] =
        {
                {0, 0, 0, 0},
                {0, 1, 1, 0},
                {0, 1, 1, 0},
                {0, 0, 0, 0},

                {0, 0, 0, 0},
                {1, 1, 1, 1},
                {0, 0, 0, 0},
                {0, 0, 0, 0},

                {0, 0, 0, 0},
                {0, 0, 1, 1},
                {0, 1, 1, 0},
                {0, 0, 0, 0},

                {0, 0, 0, 0},
                {0, 1, 1, 0},
                {0, 0, 1, 1},
                {0, 0, 0, 0},

                {0, 0, 0, 0},
                {0, 1, 1, 1},
                {0, 1, 0, 0},
                {0, 0, 0, 0},

                {0, 0, 0, 0},
                {0, 1, 1, 1},
                {0, 0, 0, 1},
                {0, 0, 0, 0},

                {0, 0, 0, 0},
                {0, 1, 1, 1},
                {0, 0, 1, 0},
                {0, 0, 0, 0},
        };

Field::Field() {
    for(int i = 0; i < 21; i++) {
        for(int j = 0; j < 12; j++) {
            if(j == 0 || j == 11 || i == 20) {
                field[i][j].block = 1;
                field[i][j].red = (GLfloat) 80/255;
                field[i][j].green = (GLfloat) 80/255;
                field[i][j].blue = (GLfloat) 80/255;
            }
            else {
                field[i][j].block = 0;
                setColor(i, j, 7);
            }
        }
    }
    nextType = (Type)(rand() % NUM);
}

Field::~Field() {

}


bool Field::spawnNewFigure() {
    int newFigure[4][4];
    figure_x = 4;
    figure_y = 0;
    rotation = 0;
    currentType = nextType;
    nextType = (Type)(rand() % NUM);
    for(size_t i = currentType * 4; i < currentType * 4 + 4; i++) {
        for(size_t j = 0; j < 4; j++) {
            newFigure[i - currentType * 4][j] = tetramino[i][j];
        }
    }

    for(size_t i = 0; i < 4; i++) {
        for(size_t j = 4; j < 8; j++) {
            field[i][j].block += newFigure[i][j-4];
            if(newFigure[i][j-4] == 1) {
                current_figure.push_back(make_pair(i, j));
            }
            if(field[i][j].block == 2) {
                for(auto val : current_figure) {
                    field[y][x].block--;
                }
                gameOver();
                return false;
            }
        }
    }

    for(auto val : current_figure)
        setColor(y, x, currentType);

    return true;
}

bool Field::moveDown() {
    for(auto & val : current_figure) {
        field[y][x].block--;
        setColor(y, x, 7);
        y++;
        field[y][x].block++;
    }

    for(auto & val : current_figure) {
        if(field[y][x].block == 2) {
            for(auto val : current_figure) {
                field[y][x].block--;
                y--;
                field[y][x].block++;
                setColor(y, x, currentType);
            }
            current_figure.clear();
            checkRows();
            return false;
        }
    }

    for(auto val : current_figure) {
        setColor(y, x, currentType);
    }

    figure_y++;

    if(current_figure.empty())
        spawnNewFigure();

    return true;
}

bool Field::moveLeft() {
    int leftest = 12;
    for(auto val : current_figure) {
        if(leftest > x)
            leftest = x;
    }

    for(auto val : current_figure) {
        if(x == leftest) {
            if(field[y][x - 1].block == 1)
                return false;
        }
    }

    for(auto & val : current_figure) {
        field[y][x].block--;
        setColor(y, x, 7);
        x--;
        field[y][x].block++;
    }

    for(auto val : current_figure) {
        setColor(y, x, currentType);
    }

    figure_x--;

    return true;
}

bool Field::moveRight() {
    int rightest = 0;
    for(auto val : current_figure) {
        if(rightest < x)
            rightest = x;
    }

    for(auto val : current_figure) {
        if(x == rightest) {
            if(field[y][x + 1].block == 1)
                return false;
        }
    }

    for(auto & val : current_figure) {
        field[y][x].block--;
        setColor(y, x, 7);
        x++;
        field[y][x].block++;
    }

    for(auto val : current_figure) {
        setColor(y, x, currentType);
    }

    figure_x++;

    return true;
}

void Field::rotate() {
    rotation++;

    if (currentType == O) {
        ;
    }
    else if (currentType == I || currentType == S || currentType == Z) {
        if (rotation % 2 == 0) {
            rotateOCW();
        }
        else {
            rotateCW();
        }
    }
    else if (currentType == L || currentType == J || currentType == T) {
        rotateCW();
    }
}

bool Field::rotateCW() {
    int Figure[4][4] = {0};
    int newFigure[4][4] = {0};
    vector<pair<int, int>> newCoords;
    for(auto val : current_figure) {
        Figure[y-figure_y][x-figure_x] = 1;
        setColor(y, x, 7);
    }

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(Figure[i][j]) {
                int new_y = 1 - (j - 2);
                int new_x = 2 + (i - 1);
                if (0 <= new_y && new_y < 4 && 0 <= new_x && new_x < 4) {
                    newFigure[new_y][new_x] = 1;
                    newCoords.push_back(make_pair(new_y + figure_y, new_x + figure_x));
                }
            }
        }
    }

    for(auto val : current_figure)
        field[y][x].block--;

    for(auto val : newCoords) {
        field[y][x].block++;
        setColor(y, x, currentType);
    }

    for(auto val : newCoords) {
        if(field[y][x].block > 1) {
            for(auto val : newCoords) {
                field[y][x].block--;
                setColor(y, x, 7);
            }
            for(auto val : current_figure) {
                field[y][x].block++;
                setColor(y, x, currentType);
            }
            rotation--;
            return false;
        }
    }

    current_figure = newCoords;
    return true;
}

bool Field::rotateOCW() {
    int newFigure[4][4] = {0};
    vector<pair<int, int>> newCoords;

    for(auto val : current_figure)
        setColor(y, x, 7);

    for(size_t i = currentType * 4; i < currentType * 4 + 4; i++) {
        for(size_t j = 0; j < 4; j++) {
            newFigure[i - currentType * 4][j] = tetramino[i][j];
            if(newFigure[i - currentType * 4][j] == 1) {
                newCoords.push_back(make_pair(i - currentType * 4 + figure_y, j + figure_x));
            }
        }
    }

    for(auto val : current_figure)
        field[y][x].block--;

    for(auto val : newCoords) {
        field[y][x].block++;
        setColor(y, x, currentType);
    }

    for(auto val : newCoords) {
        if(field[y][x].block > 1) {
            for(auto val : newCoords) {
                field[y][x].block--;
                setColor(y, x, 7);
            }
            for(auto val : current_figure) {
                field[y][x].block++;
                setColor(y, x, currentType);
            }
            rotation--;
            return false;
        }
    }

    current_figure = newCoords;
    return true;
}

int Field::checkRows() {
    int removedRows = 0;
    vector<int> fullRows;
    bool fullRow;
    for(int i = 0; i < 20; i++) {
        fullRow = true;
        for(int j = 1; j < 11; j++) {
            if(field[i][j].block == 0) {
                fullRow = false;
            }
        }
        if(fullRow) {
            fullRows.push_back(i);
            removedRows++;
        }
    }

    for(auto val : fullRows) {
        for(int i = 1; i  < 11; i++) {
            field[val][i].block = 0;
            setColor(val, i, 7);
        }
        for(int i = val; i > 0; i--) {
            for(int j = 1; j < 11; j++) {
                if(field[i-1][j].block == 1) {
                    field[i-1][j].block--;
                    field[i][j].red = field[i-1][j].red;
                    field[i][j].green = field[i-1][j].green;
                    field[i][j].blue = field[i-1][j].blue;
                    setColor(i-1, j, 7);
                    field[i][j].block++;
                }
            }
        }
    }

    switch(removedRows) {
        case 0: {break;}
        case 1: {points+=100; break;}
        case 2: {points+=300; break;}
        case 3: {points+=700; break;}
        case 4: {points+=1500; break;}
        default: {break;}
    }
    return removedRows;
}

void Field::display() {
    glutDisplayFunc(draw);
}

void Field::draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    Block nextFigure[4][4];

    for(size_t i = nextType * 4; i < nextType * 4 + 4; i++) {
        for(size_t j = 0; j < 4; j++) {
            nextFigure[i - nextType * 4][j].block = tetramino[i][j];
            setColor(nextType, nextFigure[i - nextType * 4][j].red, nextFigure[i - nextType * 4][j].green, nextFigure[i - nextType * 4][j].blue);
        }
    }

    showText("Next figure", 410, 410, 0, 0, 0);
    if(gameState) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (nextFigure[i][j].block == 1) {
                    drawQuad(395 + j * 28, 400 - i * 28, nextFigure[i][j].red, nextFigure[i][j].green,
                             nextFigure[i][j].blue);
                }
            }
        }
    }

    showText("Score", 430, 200, 0, 0, 0);
    string value = to_string(points);
    showText(value.c_str(), 445, 165, 0, 0, 0);

    if(!gameState) {
        showText("You lose", 420, 120, 0, 0, 0);
        showText("Press R to restart", 375, 95, 0, 0, 0);
    }

    for(int i = 1; i < 20; i++) {
        for (int j = 1; j < 11; j++) {
            drawQuad(50 + (j-1) * 28, 565 - (i-1) * 28, field[i][j].red, field[i][j].green, field[i][j].blue);
        }
    }

    glFlush();
}

void Field::drawQuad(int cur_x, int cur_y, GLfloat cur_red, GLfloat cur_green, GLfloat cur_blue) {
   /* glBegin(GL_QUADS);
    glVertex2f(cur_x, cur_y);
    glVertex2f(cur_x, cur_y - 26);
    glVertex2f(cur_x + 26, cur_y - 26);
    glVertex2f(cur_x + 26, cur_y);
    glEnd();*/
    GLint QuadVertexArray[][2] = {{cur_x, cur_y},
                                  {cur_x, cur_y - 26},
                                  {cur_x + 26, cur_y - 26},
                                  {cur_x + 26, cur_y}};
    GLfloat QuadColorArray[][3] = { {cur_red, cur_green, cur_blue},
                                    {cur_red, cur_green, cur_blue},
                                    {cur_red, cur_green, cur_blue},
                                    {cur_red, cur_green, cur_blue}};
    GLubyte QuadIndexArray[][4] = {{0, 1, 2, 3}};

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(2, GL_INT, 0, QuadVertexArray);
    glColorPointer(3, GL_FLOAT, 0, QuadColorArray);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, QuadIndexArray);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void Field::gameOver() {
    gameState = false;
    current_figure.clear();
}

bool Field::getState() {
    return gameState;
}

void Field::startGame() {
    for(int i = 0; i < 20; i++) {
        for (int j = 1; j < 11; j++) {
            field[i][j].block = 0;
            setColor(i, j, 7);
        }
    }
    points = 0;
    gameState = true;
}

void Field::setColor(int i, int j, int type) {
    switch (type) {
        case 0:
            field[i][j].red = (GLfloat) 220/255 ;
            field[i][j].green = (GLfloat) 30/255;
            field[i][j].blue = (GLfloat) 30/255;
            break;
        case 1:
            field[i][j].red = (GLfloat) 255/255;
            field[i][j].green = (GLfloat) 155/255;
            field[i][j].blue = (GLfloat) 5/255;
            break;
        case 2:
            field[i][j].red = (GLfloat) 255/255;
            field[i][j].green = (GLfloat) 230/255;
            field[i][j].blue = (GLfloat) 5/255;
            break;
        case 3:
            field[i][j].red = (GLfloat) 60/255;
            field[i][j].green = (GLfloat) 230/255;
            field[i][j].blue = (GLfloat) 20/255;
            break;
        case 4:
            field[i][j].red = (GLfloat) 35/255;
            field[i][j].green = (GLfloat) 220/255;
            field[i][j].blue = (GLfloat) 210/255;
            break;
        case 5:
            field[i][j].red = (GLfloat) 30/255;
            field[i][j].green = (GLfloat) 40/255;
            field[i][j].blue = (GLfloat) 225/255;
            break;
        case 6:
            field[i][j].red = (GLfloat) 180/255;
            field[i][j].green = (GLfloat) 50/255;
            field[i][j].blue = (GLfloat) 205/255;
            break;
        default:
            field[i][j].red = (GLfloat) 225/255;
            field[i][j].green = (GLfloat) 225/255;
            field[i][j].blue = (GLfloat) 225/255;
            break;
    }
}

void Field::setColor(int type, GLfloat & red, GLfloat & green, GLfloat & blue) {
    switch (type) {
        case 0:
            red = (GLfloat) 220/255 ;
            green = (GLfloat) 30/255;
            blue = (GLfloat) 30/255;
            break;
        case 1:
            red = (GLfloat) 255/255;
            green = (GLfloat) 155/255;
            blue = (GLfloat) 5/255;
            break;
        case 2:
            red = (GLfloat) 255/255;
            green = (GLfloat) 230/255;
            blue = (GLfloat) 5/255;
            break;
        case 3:
            red = (GLfloat) 60/255;
            green = (GLfloat) 230/255;
            blue = (GLfloat) 20/255;
            break;
        case 4:
            red = (GLfloat) 35/255;
            green = (GLfloat) 220/255;
            blue = (GLfloat) 210/255;
            break;
        case 5:
            red = (GLfloat) 30/255;
            green = (GLfloat) 40/255;
            blue = (GLfloat) 225/255;
            break;
        case 6:
            red = (GLfloat) 180/255;
            green = (GLfloat) 50/255;
            blue = (GLfloat) 205/255;
            break;
        default:
            red = (GLfloat) 225/255;
            green = (GLfloat) 225/255;
            blue = (GLfloat) 225/255;
            break;
    }
}

void showText(const char* str,int x_coord, int y_coord, GLfloat red, GLfloat green, GLfloat blue) {
    glColor3f(red, green, blue);
    glRasterPos2f(x_coord, y_coord);
    int i = 0;
    while (str[i] !='\0') {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str[i]);
        i++;
        glRasterPos2f(x_coord + i*10, y_coord);
    }
}


