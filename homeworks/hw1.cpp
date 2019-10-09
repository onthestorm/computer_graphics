//
// Created by igorc on 01.10.2019.
//

#include <iostream>
#include <fstream>
#include <vector>

#define coord pair<int, int>

using namespace std;

struct object {
    int square = 0;
    string type;
    vector<coord> coords;

    void print() {
        cout << "Size = " << square << endl;
        cout << "Type - " << type << endl;
    }
};

void locate(char** matrix, object & obj, int x, int y, int n);

int main()
{
    int n;
    cout << "Enter matrix size : ";
    cin >> n;

    char** matrix;
    matrix = new char*[n];
    for(int i = 0; i < n; i++) {
        matrix[i] = new char[n];
    }

    ifstream in("data.txt");
    if(in.is_open()) {
        string line;
        for(int i = 0; i < n; i++) {
            getline(in, line);
            memcpy(matrix[i], line.data(), n);
        }
    }
    else {
        cout << "No data" << endl;
        return 1;
    }

    vector<object> objects;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(matrix[i][j] == '1') {
                object newObject;
                locate(matrix, newObject, i, j, n);
                if(newObject.square == 1)
                    newObject.type = "Anomaly";
                else if(newObject.square >= 2 && newObject.square < 5)
                    newObject.type = "Enemy";
                else
                    newObject.type = "Ground";
                objects.push_back(newObject);
            }
        }
    }

    for(size_t i = 0; i < objects.size(); i++) {
        cout << "Object " << i+1 << ":" << endl;
        objects[i].print();
        cout << "--------------------" << endl;
    }

    return 0;
}

void locate(char** matrix, object & obj, int x, int y, int n) {
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, -1, 0, 1};
    int nx, ny;
    obj.coords.emplace_back(make_pair(x, y));
    obj.square++;
    matrix[x][y] = '0';
    for(int k = 0; k < 4; k++) {
        nx = x + dx[k];
        ny = y + dy[k];
        if (nx >= 0 && nx < n && ny >= 0 && ny < n)
            if (matrix[nx][ny] == '1')
                locate(matrix, obj, nx, ny, n);
     }
}


