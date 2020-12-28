#include "Cube.hpp"
#include <iostream>

//stvara praznu kocku
Cube::Cube() {
    mNumber=0;
    clear();
}

//kocku pretvara u praznu koku
void Cube::clear() {
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            for(int k=0; k<4; k++)
                cube[i][j][k]=' ';    
}

bool Cube::winning_line(char c){
    //najprije po levelima provjerimo dobitke u horizontalnom polozaju =40slučajeva
    for(int i=0;i<4;i++){
        //provjera po redcima
        for(int j=0;j<4;j++){
            if(cube[i][j][0]==c && cube[i][j][1]==c && cube[i][j][2]==c && cube[i][j][3]==c) return true;
        }
        //provjera po stupcima
        for(int j=0;j<4;j++){
            if(cube[i][0][j]==c && cube[i][1][j]==c && cube[i][2][j]==c && cube[i][3][j]==c) return true;
        }
        //provjera dvije dijagonale
        if(cube[i][0][0]==c && cube[i][1][1]==c && cube[i][2][2]==c && cube[i][3][3]==c ) return true;
        if(cube[i][0][3]==c && cube[i][1][2]==c && cube[i][2][1]==c && cube[i][3][0]==c ) return true;
    }
    //za vertikalne netrebam provjeravat horizontalne jer to vec jesmo =24
    for(int i=0;i<4;i++){
        //provjera po stupcima
        for(int j=0;j<4;j++){
            if(cube[0][j][i]==c && cube[1][j][i]==c && cube[2][j][i]==c && cube[3][j][i]==c) return true;
        }
        //provjera dvije dijagonale
        if(cube[0][0][i]==c && cube[1][1][i]==c && cube[2][2][i]==c && cube[3][3][i]==c ) return true;
        if(cube[0][3][i]==c && cube[1][2][i]==c && cube[2][1][i]==c && cube[3][0][i]==c ) return true;
    }
    //fale mi dijagonale po redcima =8
    for(int i=0;i<4;i++){
        if(cube[0][i][0]==c && cube[1][i][1]==c && cube[2][i][2]==c && cube[3][i][3]==c ) return true;
        if(cube[0][i][3]==c && cube[1][i][2]==c && cube[2][i][1]==c && cube[3][i][0]==c ) return true;
    }
    //unutrasnje dijagonale =4
    if(cube[0][0][0]==c && cube[2][2][2]==c && cube[3][3][3]==c && cube[1][1][1]==c ) return true;
    if(cube[0][0][3]==c && cube[1][1][2]==c && cube[2][2][1]==c && cube[3][3][0]==c ) return true;
    if(cube[0][3][3]==c && cube[1][2][2]==c && cube[2][1][1]==c && cube[3][1][1]==c ) return true;
    if(cube[0][3][0]==c && cube[1][2][1]==c && cube[2][1][2]==c && cube[3][0][3]==c ) return true;
    return false;
}
//vraća 1 ako je X pobjedio, -1 ako je O pobjedio, 0 ako je nerjeseno
//ako nije nista od navedenog prazan optional
std::optional<int> Cube::result() {
    if(winning_line('X')) return 1;
    if(winning_line('O')) return -1;
    if(mNumber>=64) return 0; 
    return {};
}

char Cube::value(int i, int j, int k){
    return cube[i][j][k];
}

//iscrtava kocku u terminalu
void Cube::print(){
    //printanje po nivoima
    for(int j=0;j<4;j++){
        std::cout << "Nivo " << j+1 << ":" << std::endl;
        for(int i=0;i<17;i++){
            std::cout << "-";
        }
        std::cout << std::endl;
        //printanje po redcima
        for(int k=0;k<4;k++){
            //sad printamo redak s vrijednostima
            std::cout << "| " << cube[j][k][0] << " | " << cube[j][k][1] << " | " << cube[j][k][2] << " | "<< cube[j][k][3] << " |"<<std::endl;
            //donja linija
            for(int i=0;i<17;i++){
                std::cout << "-";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

//odigra potez na poziciji move i poveća broj odigranih
//vraca true ako je move bio valjan
//mozda promjenit ovu provjeru
bool Cube::play(Move move,char c) {
    if(!move.isValid(*this)) return false;
    cube[move.level()][move.row()][move.column()] = c;
    mNumber++;
    return true;
}

//mozda postoji neki ljepsi nacin
std::vector<Move> Cube::generate_moves(){
    std::vector<Move> moves;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            for(int k=0;k<4;k++){
                if(cube[i][j][k]==' '){
                    Move m(i,j,k);
                    moves.push_back(m);
                }
            }
        }
    }
    return moves;
}
