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
    //dodat cu primjer table da vidim jel radi 
    
    // mCube.cube[0][0][2] = 'O';
    // // mCube.cube[0][1][3] = 'O';
    // mCube.cube[0][2][0] = 'X';
    
    // mCube.cube[0][2][1] = 'X';
    
    // // mCube.cube[0][3][2] = 'X';
    // mCube.cube[0][0][1] = 'X';
    
    // mCube.cube[0][0][3] = 'X';
    // // mCube.cube[0][1][0] = 'X';
    
    // mCube.cube[0][2][2] = 'O';
    
    // mCube.cube[0][3][1] = 'O';
    // // mCube.cube[0][2][3] = 'O';
    // mCube.cube[0][3][3] = 'O';
    
    // mCube.mNumber=8;
    //playerOnMove=1;
    
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
