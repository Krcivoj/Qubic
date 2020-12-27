#include "Player.hpp"

#include <iostream>
#include <vector>

Player::Player() {
    name=' ';
}

Player::Player(char id) {
    name=id;
}

char Player::id(){
    return name;
}
void Player::play(Cube& cube) {
    std::vector<int> move(3);
    move = minMax(cube, name);
    std::cout<<"Na redu je igrac "<<name<<std::endl;
    std::cout<<"Hint: "<<move<<std::endl;

    do{
        std::cin>>move;
    }while(!cube.play(move));
}

//treba dodati operator << za ispis move
//i operator >> za onos move