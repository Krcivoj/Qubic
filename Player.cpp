#include "Player.hpp"

#include <iostream>
#include <vector>

Player::Player() {
    mName=' ';
}

Player::Player(char id) {
    mName=id;
}

char Player::id(){
    return mName;
}

//algoritam min max(verzija bez podrezivanja)
Move Player::minMax(Cube& cube, char id){
    Move move;
    //najprije imam minimax funkciju koja mi vraća vrijednost
    //treba odredit kako ćemo nac pravi potez za odigrat
    //ideja: kad pozivam min max succ cu pozvat generate moves, na svakom u vectoru odigrat opet minmax... 
    //i prije odlaska na sljed potez vratit stanje s cube[...]=' '
    //međutim i dalje nezz kako ću znat kasnije di odigrat potez
    //mozda ako dok idem trazit max u svim generiranim potezima uz max vrijednost pamtim i max indeks u potezima tj potez koji zelim odigrat
    //pa ako mjenjam max mjenjam i taj indeks, na krjau znam koji potez u generiranim u vecotru moram odigrat
    return move;
}

void Player::play(Cube& cube) {
    Move move;
    move = minMax(cube, id());
    std::cout << "Na redu je igrac: "<< id() <<std::endl;
    std::cout << "Hint: "<< move <<std::endl;

    do{
        std::cout << "Odaberite potez:" << std::endl;
        std::cin>>move;
    }while(!cube.play(move,id()));
}

bool Move::isValid(Cube& cube){
    if(mLevel>3) return false;
    if(mRow>3) return false;
    if(mColumn>3) return false;
    if(cube.value(mLevel,mRow,mColumn)!=' ') return false;
    return true;
}

std::ostream& operator<<(std::ostream& os, const Move& move){
    os << "Level: " << move.mLevel << ", Row: " << move.mRow << ", Column: " << move.mColumn;
    return os;
}
std::istream& operator>> (std::istream& is, Move& move){
    is>> move.mLevel >> move.mRow >> move.mColumn;
    return is;
}