#include "Qubic.hpp"


#include <iostream>
#include <optional>

int main(){
    Qubic game;
    std::optional<Player> winner = game.play();
    std::cout<<"Igra je gotova"<<std::endl;
    if(winner.has_value()){
        std::cout<<"Pobjedio je "<<winner.value().id()<<std::endl;
    }
    else{
        std::cout<<"Igra je zavrsila nerjeseno"<<std::endl;
    }
    return 0;
}