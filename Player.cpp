#include "Player.hpp"

#include <iostream>
#include <vector>
#include <utility>
#include <optional>

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
std::pair<int, Move> Player::minMax(Cube* cube, std::vector<Move> moves, char id, int alpha, int beta, int s){
    std::pair<int, Move> result;
    std::optional<int> value;

    //terminal state  
    value=cube->result();
    if(value.has_value()){
        result.first=value.value();
        result.second=Move(-1,-1,-1);
        return result;
    }
    
    int n=moves.size();
    Move move;
    std::pair<int, Move> temp;

    //dodano
    if(s<=0){
        /*
        if(mName=='O')result.first=1;
        else result.first=-1;
        result.second=Move(-1,-1,-1);
        return result;
        return{};
        */
        result.second = Move(-1,-1,-1);
        if(id=='X') result.first = cube->heuristic('X','O');
        else result.first = cube->heuristic('O','X');
        return result;
    }

    //max
    if(id == 'X'){
        result.first=-1000;
        for(int i=0; i<n; i++){
            move=moves.front();
            moves.erase(moves.begin());
            if(!cube->play(move, 'X')){std::cout<<"NE"<<move; std::cin.ignore(1);}
            temp=minMax(cube, moves, 'O', alpha, beta,s-1);
            moves.push_back(move);
            cube->unPlay(move);
            if(temp.first>result.first){
                result.first=temp.first;
                result.second=move;
                //dodano za alpha beta 
                alpha = std::max(alpha, result.first); 
            }
            if (beta <= alpha) break;
            //kad naidemo na 2 sigurno necemo naci bolje pa izlazim
            if(result.first==500)break;
        }
    }

    //min
    else if(id == 'O'){
        result.first=1000;
        for(int i=0; i<n; i++){
            move=moves.front();
            moves.erase(moves.begin());
            if(!cube->play(move, 'O')){std::cout<<"NE"<<move; std::cin.ignore(1);}
            temp=minMax(cube, moves, 'X', alpha, beta,s-1);
            moves.push_back(move);
            cube->unPlay(move);
            if(temp.first<result.first){
                result.first=temp.first;
                result.second=move;
                beta = std::min(beta, result.first);
                //if (beta <= alpha) break; 
            }
            if (beta <= alpha) break;
            //kad naidemo na -2 sigurno necemo naci bolje pa izlazim
            if(result.first==-500)break;
        }
    }
    return result;
}

void shuffle(std::vector<Move>& moves){
    int n = moves.size();
    for (int i = 0; i < n - 1; i++)
    {
        int j = i + rand() % (n - i);
        std::swap(moves[i], moves[j]);
    }
} 

void Player::play(Cube* cube) {
    std::pair<int, Move> result;
    Move move;
    std::vector<Move> moves=cube->generate_moves();
    srand(unsigned(time(NULL)));
    shuffle(moves);

    std::cout << moves.size() << std::endl;
    //cube.print();
    int alpha = -1000;
    int beta = 1000;
    for(int i=1; i<=cube->maxDepth();i++){
        result = minMax(cube, moves, mName, alpha, beta,i);
        std::cout<<i<<','<<result.first<< std::endl;
        if(result.first==-500 || result.first==500)break;
    }

    std::cout << "Privremeni: "<< result.first<< result.second <<std::endl;
    if(mName=='O' && result.first>0){
        for(int i=1; i<=cube->maxDepth();i++){
            result = minMax(cube, moves, 'X', alpha, beta,i);
            std::cout<<i<<','<<result.first<< std::endl;
            if(result.first==-500 || result.first==500)break;
        }
    }

    else if(mName=='X' && result.first<0){
        for(int i=1; i<=cube->maxDepth();i++){
            result = minMax(cube, moves, 'O', alpha, beta,i);
            std::cout<<i<<','<<result.first<< std::endl;
            if(result.first==-500 || result.first==500)break;
        }
    }

    std::cout << "Na redu je igrac: "<< mName <<std::endl;
    std::cout << "Hint: "<< result.first<< result.second <<std::endl;

    do{
        std::cout << "Odaberite potez:" << std::endl;
        std::cin>>move;
        //move=result.second;
    }while(!cube->play(move,mName));
}
