#include "Qubic.hpp"

#include <optional>

Qubic::Qubic() {
    mPlayers.push_back(Player('X'));
    mPlayers.push_back(Player('O'));
}

std::optional<Player> Qubic::play() {
    std::optional<Player> winner;
    std::optional<int> result;
    int playerOnMove=0;
    result= mCube.result();
    //dodat cu primjer table da vidim jel radi 
    /*
    mCube.cube[0][0][2] = 'O';
    mCube.cube[0][1][3] = 'O';
    mCube.cube[0][2][0] = 'X';
    
    mCube.cube[0][2][1] = 'X';
    
    mCube.cube[0][3][2] = 'X';
    mCube.cube[0][0][1] = 'X';
    
    mCube.cube[0][0][3] = 'X';
    mCube.cube[0][1][0] = 'X';
    
    mCube.cube[0][2][2] = 'O';
    
    mCube.cube[0][3][1] = 'O';
    mCube.cube[0][2][3] = 'O';
    mCube.cube[0][3][3] = 'O';
    */
    //mCube.mNumber=12;
    //playerOnMove=1;
    
    mCube.print();
    while(!result.has_value()){
        playerOnMove%=2;
        mPlayers[playerOnMove].play(mCube);
        mCube.print();
        playerOnMove++;  
        result= mCube.result();    
    }
    if(result.value()==1){
        winner=mPlayers[0];
    }
    else if(result.value()==-1){
        winner=mPlayers[1];
    }
    return winner;
}
