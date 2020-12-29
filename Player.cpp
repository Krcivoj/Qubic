#include "Player.hpp"

#include <iostream>
#include <vector>
#include <utility>
#include <optional>

bool Move::isValid(Cube& cube){
    if(mLevel<0 || mLevel>3) return false;
    if(mRow<0 || mRow>3) return false;
    if(mColumn<0 || mColumn>3) return false;
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

////////////////////////////////////////////////////////////////////

Player::Player(char id=' ') {
    mName=id;
}

char Player::id(){
    return mName;
}

//algoritam min max(verzija s podrezivanjem - vrlo ugrubo treba provjerit)
std::pair<int, Move> Player::minMax(Cube& cube, std::vector<Move> moves, char id, int alpha, int beta){
    std::pair<int, Move> result;
    std::optional<int> value;
    //najprije imam minimax funkciju koja mi vraća vrijednost
    //treba odredit kako ćemo nac pravi potez za odigrat
    //ideja: kad pozivam min max succ cu pozvat generate moves, na svakom u vectoru odigrat opet minmax... 
    //i prije odlaska na sljed potez vratit stanje s cube[...]=' '
    //međutim i dalje nezz kako ću znat kasnije di odigrat potez
    //mozda ako dok idem trazit max u svim generiranim potezima uz max vrijednost pamtim i max indeks u potezima tj potez koji zelim odigrat
    //pa ako mjenjam max mjenjam i taj indeks, na krjau znam koji potez u generiranim u vecotru moram odigrat
    //za aplha beta ideju, iako mi se ovo cini sumljivo, obzirom na int a ne int
    // Check if this branch's best move is worse than the best
	// option of a previously search branch. If it is, skip it

    //terminal state
    
    value=cube.result();
    if(value.has_value()){
        result.first=value.value();
        return result;
    }
    
    int n=moves.size();
    Move move;
    std::pair<int, Move> temp;
    Cube tCube;
    //dodano
    if(n==0 && !value.has_value()) {
        std::cout << "greska   " <<cube.mNumber <<  "    " << id << std::endl;
        cube.print();
    }
    //max
    if(id == 'X'){
        result.first=-2;
        for(int i=0; i<n; i++){
            move=moves.front();
            moves.erase(moves.begin());
            tCube= cube;
            if(!tCube.play(move, 'X'))std::cout<<"NE";
            temp=minMax(tCube, moves, 'O',alpha,beta);
            if(temp.first>result.first){
                result.first=temp.first;
                result.second=move;
                //dodano za alpha beta 
                alpha = std::max(alpha, result.first);
				if (beta <= alpha) break; 
            }
            moves.push_back(move);
            //kad naidemo na 1 sigurno necemo naci bolje pa izlazim
            if(result.first==1)break;
        }
    }

    //min
    else if(id == 'O'){
        result.first=2;
        for(int i=0; i<n; i++){
            move=moves.front();
            moves.erase(moves.begin());
            tCube= cube;
            if(!tCube.play(move, 'O'))std::cout<<"NE";
            temp=minMax(tCube, moves, 'X',alpha,beta);
            if(temp.first<result.first){
                result.first=temp.first;
                result.second=move;
                beta = std::min(beta, result.first);
				if (beta <= alpha) break; 
            }
            moves.push_back(move);
            //kad naidemo na -1 sigurno necemo naci bolje pa izlazim
            if(result.first==-1)break;
        }
    }
    return result;
}

void Player::play(Cube& cube) {
    Move move;
    
    
    std::vector<Move> moves= cube.generate_moves();
    //std::cout << moves.size() << std::endl;
    //cube.print();
    int alpha = -1000;
    int beta = 1000;
    move = minMax(cube, moves, mName, alpha, beta).second;
    std::cout << "Na redu je igrac: "<< mName <<std::endl;
    std::cout << "Hint: "<< move <<std::endl;

    do{
        std::cout << "Odaberite potez:" << std::endl;
        std::cin>>move;
    }while(!cube.play(move,mName));
}
