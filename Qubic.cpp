#include "Qubic.hpp"

#include <optional>

Qubic::Qubic() {
    players.push_back(Player('X'));
    players.push_back(Player('O'));
}

std::optional<Player> Qubic::play() {
    std::optional<Player> winner;
    std::optional<int> result;
    int i=0;
    result= mCube.result();
    while(!result.has_value()){
        mCube.print();
        i%=2;
        players[i].play(mCube);
        i++;  
        result= mCube.result();    
    }
    if(result.value()==1){
        winner=players[0];
    }
    else if(result.value()==-1){
        winner=players[1];
    }
    return winner;
}
