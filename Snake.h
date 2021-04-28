#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <list>
#include "SnakeGame.cpp"

using namespace std;

class Snake
{
public:
    Snake() {
        size = 3;
        int headX = width / 2;
        int headY = height /2;
        vector<int> tmpPos{headX, headY};
        body.push_back(tmpPos);
        tmpPos[0] -= 1;
        body.push_back(tmpPos);
        tmpPos[0] -= 1;
        body.push_back(tmpPos);
    }

    Snake(int initSize) {
        // TODO
    }

    bool moveLeft() {
        vector<int> head = body.front();
        vector<int> newHead{head[0] - 1, head[1]};
        body.push_front(newHead);
        body.pop_back();
        return checkAlive(newHead);
    }
    
    bool moveRight() {
        vector<int> head = body.front();
        vector<int> newHead{head[0] + 1, head[1]};
        body.push_front(newHead);
        body.pop_back();
        return checkAlive(newHead);
    }

    bool moveUp() {
        vector<int> head = body.front();
        vector<int> newHead{head[0], head[1] - 1};
        body.push_front(newHead);
        body.pop_back();
        return checkAlive(newHead);
    }

    bool moveDown() {
        vector<int> head = body.front();
        vector<int> newHead{head[0], head[1] + 1};
        body.push_front(newHead);
        body.pop_back();
        return checkAlive(newHead);
    }

    Action move(char input, vector<int> food) {
        bool isSucess = true;
        switch (input) {
            case 'w' :
                isSucess = moveUp();
                break;
            case 's' :
                isSucess = moveDown();
                break;
            case 'a' :
                isSucess = moveLeft();
                break;
            case 'd' :
                isSucess = moveRight();
                break;
            default :
                break;
        }
        if (isSucess && food == getHead()) {
            return Action(MOVE_TO_FOOD);
        } else if (isSucess) {
            return Action(MOVE_TO_SPACE);
        }
        return Action(MOVE_TO_SIDE);
    }
    const vector<int> getHead() const {
        return  body.front(); 
    }

    bool checkAlive(vector<int> newHead) {
        if (newHead[0] == height - 1 || newHead[0] == 0 ||
            newHead[1] == width - 1 || newHead[1] == 0) {
                return false;
        }
        if (checkExit(newHead, true)) {
            return false;
        }
        return true;
    }

    bool checkExit(const vector<int> target, bool afterMove) {
        list<vector<int>>::iterator itr = body.begin();
        if (afterMove) {
            itr++;
        }
        while(itr != body.end()) {
            if (*itr == target) {
                return true;
            }
        }
        return false;
    }
    
    const list<vector<int>>& readBody() {
        return body;
    }
private:
    list<vector<int>> body;
    int size;
};


#endif
