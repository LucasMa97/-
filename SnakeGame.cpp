#include <iostream>
#include <vector>
#include <string>
#include "Snake.h"

using namespace std;

#define width 16
#define height 16

enum Object {
    SNAKE,
    SPACE,
    SIDE,
    FOOD,
};

enum Action {
    MOVE_TO_SPACE,
    MOVE_TO_FOOD,
    MOVE_TO_SIDE,
};

vector<char> objChar = {'+', ' ', '#', '$'};

string guide = "press w/up s/down a/left d/right\n";
// random make a map of char
void InitMapChar(vector<char> mapChar, Snake player, vector<int> food)
{
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (x == 0 || y == 0 || x == height - 1 || y == width -1) {
                mapChar.push_back('#');
            }
            if (x == food[0] && y == food[1]) {
                mapChar.push_back('$');
            }
            mapChar.push_back(' ');
        }
    }
    // set char of snake
    list<vector<int>> points = player.readBody();
    list<vector<int>>::const_iterator itr = points.begin();
        while(itr != points.end()) {
            int snakeTmpX = (*itr)[0];
            int snakeTmpY = (*itr)[1];
            mapChar[snakeTmpX * width + snakeTmpY] = '+';
        }
}

// converse objs to char to prepare show in screen
void CharToObjs(const vector<char> mapChar, vector<Object> mapObjs)
{
    for (int i = 0; i < mapChar.size(); i++) {
        Object t;
        switch (mapChar[i]) {
            case '#' :
                t = Object(SIDE);  // FORCE VALUE TO INSTANCE
                break;
            case ' ' :
                t = Object(SPACE);
                break;
            case '$' :
                t = Object(FOOD);
                break;
            case '+' :
                t = Object(SNAKE);
            default:
                break;
        }
        mapObjs[i] = t;
    }
}

void Draw(vector<Object> mapObjs) 
{
    for (int i = 0; i < width; i++) {
        for ( int j = 0; j < height; j++) {
            cout << objChar[mapObjs[i * width + j]];
        }
        cout << endl;
    }
    cout << guide << endl;
}

void updateMapObjs(vector<Object> mapObjs, Snake player, vector<int> food)
{
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (x == 0 || y == 0 || x == height - 1 || y == width -1) {
                mapObjs.push_back(Object(SIDE));
            }
            if (x == food[0] && y == food[1]) {
                mapObjs.push_back(Object(FOOD));
            }
            mapObjs.push_back(Object(SPACE));
        }
    }
    // set char of snake
    list<vector<int>> points = player.readBody();
    list<vector<int>>::const_iterator itr = points.begin();
        while(itr != points.end()) {
            int snakeTmpX = (*itr)[0];
            int snakeTmpY = (*itr)[1];
            mapObjs[snakeTmpX * width + snakeTmpY] = Object(SNAKE);
        }
}

vector<int> RandomFood(Snake player) {
    vector<int> food(2);
    food[0] = rand() % height + 1;
    food[1] = rand() % width + 1;
    while (!player.checkExit(food, false)) {
        food[0] = rand() % height + 1;
        food[1] = rand() % width + 1;
    }
    return food;
}

int main()
{
    // init map
    vector<char> mapChar(width * height);
    Snake player{};
    vector<int> food = RandomFood(player);
    InitMapChar(mapChar, player, food);
    vector<Object> mapObjs(width * height);
    CharToObjs(mapChar, mapObjs);
    // main loop
    char input;
    while (true) {
        Draw(mapObjs);
        cin >> input;
        switch (player.move(input, food)) {
            case MOVE_TO_SPACE :
                break;
            case MOVE_TO_FOOD :
                food = RandomFood(player);
                break;
            case MOVE_TO_SIDE :
                // if move failed, break
                // failedUpdate(mapObjs, player);
                break;
        }
        updateMapObjs(mapObjs, player, food);
    }
    // end game
    cout << "YOU DIED!!!" << endl;
}
