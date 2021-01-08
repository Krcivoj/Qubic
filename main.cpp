#include "Qubic.hpp"

#include <iostream>
#include <optional>

int main(){
    Qubic game;
    std::cout << "------IGRA QUBIC ZAPOCINJE------" << std::endl;
    std::cout << std::endl;
    std::optional<Player> winner = game.play();
    std::cout<<"-----IGRA JE GOTOVA!-----"<<std::endl;
    if(winner.has_value()){
        std::cout<<"Pobjedio je: "<<winner.value().id()<<std::endl;
    }
    else{
        std::cout<<"Igra je zavrsila nerjeseno!"<<std::endl;
    }
    return 0;
}