#pragma once
#include "Cube.hpp"

#include <vector>
#include <iostream>

class Cube;
class Move{
private:
    int mLevel;
    int mRow;
    int mColumn;
public:
    Move():mLevel(0),mRow(0),mColumn(0){}
    Move(int i, int j, int k):mLevel(i),mRow(j),mColumn(k){}
    bool isValid(Cube&);
    int level(){return mLevel;}
    int row(){return mRow;}
    int column(){return mColumn;}
    friend std::ostream& operator<<(std::ostream& os,const Move& move);
    friend std::istream& operator>>(std::istream& is,Move& move);
};

class Player{
    private:
        char mName;
        Move minMax(Cube&, char);
    public:
        Player();
        Player(char);

        char id();
        void play(Cube&);
};

