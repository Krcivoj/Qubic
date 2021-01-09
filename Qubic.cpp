#include "Qubic.hpp"

#include <optional>
#include <iostream>

Qubic::Qubic() {
    std::cout << "Odaberite verziju igre:" << std::endl;
    std::cout << "Za igru na kocki 3X3X3 odaberite 3" << std::endl;
    std::cout << "Za igru na kocki 4X4X4 odaberite 4" << std::endl;
    std::cout << "Vas odabir: ";
    int a;
    std::cin>>a;
    std::cout << std::endl << std::endl << std::endl;
    if(a==3){
        mCube= new Cube3();
        std::cout << "----IGRA KRIZIC-KRUZIC U 3D NA 3X3X3 KOCKI ZAPOCINJE---" << std::endl << std::endl;
    }
    else{
        mCube= new Cube4();
        std::cout << "----IGRA KRIZIC-KRUZIC U 3D NA 4X4X4 KOCKI ZAPOCINJE---" << std::endl << std::endl;
    }
    mPlayers.push_back(Player('X'));
    mPlayers.push_back(Player('O'));
}

std::optional<Player> Qubic::play() {
    std::optional<Player> winner;
    std::optional<int> result;
    int playerOnMove=0;
    result= mCube->result();
    
    mCube->print();
    result= mCube->result();
    while(!result.has_value()){
        playerOnMove%=2;
        mPlayers[playerOnMove].play(mCube);
        mCube->print();
        playerOnMove++;  
        result= mCube->result();    
    }
    if(result.value()==500){
        winner=mPlayers[0];
    }
    else if(result.value()==-500){
        winner=mPlayers[1];
    }
    return winner;
}

Qubic::~Qubic() {
    delete mCube;    
}
