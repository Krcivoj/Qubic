#include "Qubic.hpp"

#include <optional>

Qubic::Qubic() {
    mPlayers.push_back(Player('X'));
    mPlayers.push_back(Player('O'));
}

std::optional<Player> Qubic::play() {
    std::optional<Player> winner;
    std::optional<int> result;
    int player_on_move=0;
    result= mCube.result();
    while(!result.has_value()){
        mCube.print();
        player_on_move%=2;
        mPlayers[player_on_move].play(mCube);
        player_on_move++;  
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
