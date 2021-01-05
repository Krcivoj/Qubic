#include "Cube.hpp"
#include <iostream>

//stvara praznu kocku
Cube::Cube() {
    mTimes=0;
    mNumber=0;
    clear();
}

//kocku pretvara u praznu kocku
void Cube::clear() {
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            for(int k=0; k<4; k++)
                cube[i][j][k]=' ';    
}

char Cube::value(int i, int j, int k){
    return cube[i][j][k];
}

//vraća 1 ako je X pobjedio, -1 ako je O pobjedio, 0 ako je nerjeseno
//ako nije nista od navedenog prazan optional
std::optional<int> Cube::result() {
    char winner=winning_line();
    if(winner=='X') return 2;
    if(winner=='O') return -2; 
    if(mNumber>=64) return 0;
    return {};
}

char Cube::winning_line(){
    //najprije po levelima provjerimo dobitke u horizontalnom polozaju =40slučajeva
    for(int i=0;i<4;i++){
        //provjera po redcima
        for(int j=0;j<4;j++){
            if(cube[i][j][0]!=' ' && cube[i][j][0]==cube[i][j][1] && cube[i][j][1]==cube[i][j][2] && cube[i][j][2]==cube[i][j][3]) return cube[i][j][0];
        }
        //provjera po stupcima
        for(int j=0;j<4;j++){
            if(cube[i][0][j]!=' ' && cube[i][0][j]==cube[i][1][j] && cube[i][1][j]==cube[i][2][j] && cube[i][2][j]==cube[i][3][j]) return cube[i][0][j];
        }
        //provjera dvije dijagonale
        if(cube[i][0][0]!=' ' && cube[i][0][0]==cube[i][1][1] && cube[i][1][1]==cube[i][2][2] && cube[i][2][2]==cube[i][3][3]) return cube[i][0][0];
        if(cube[i][0][3]!=' ' && cube[i][0][3]==cube[i][1][2] && cube[i][1][2]==cube[i][2][1] && cube[i][2][1]==cube[i][3][0]) return cube[i][0][3];
    }
    
    //za vertikalne netrebam provjeravat horizontalne jer to vec jesmo =24
    for(int i=0;i<4;i++){
        //provjera po stupcima
        for(int j=0;j<4;j++){
            if(cube[0][j][i]!=' ' && cube[0][j][i]==cube[1][j][i] && cube[1][j][i]==cube[2][j][i] && cube[2][j][i]==cube[3][j][i]) return cube[0][j][i];
        }
        //provjera dvije dijagonale
        if(cube[0][0][i]!=' ' && cube[0][0][i]==cube[1][1][i] && cube[1][1][i]==cube[2][2][i] && cube[2][2][i]==cube[3][3][i]) return cube[0][0][i];
        if(cube[0][3][i]!=' ' && cube[0][3][i]==cube[1][2][i] && cube[1][2][i]==cube[2][1][i] && cube[2][1][i]==cube[3][0][i]) return cube[0][3][i];
    }
    //fale mi dijagonale po redcima =8
    for(int i=0;i<4;i++){
        if(cube[0][i][0]!=' ' && cube[0][i][0]==cube[1][i][1] && cube[1][i][1]==cube[2][i][2] && cube[2][i][2]==cube[3][i][3]) return cube[0][i][0];
        if(cube[0][i][3]!=' ' && cube[0][i][3]==cube[1][i][2] && cube[1][i][2]==cube[2][i][1] && cube[2][i][1]==cube[3][i][0]) return cube[0][i][3];
    }
    //unutrasnje dijagonale =4
    if(cube[0][0][0]!=' ' && cube[0][0][0]==cube[2][2][2] && cube[2][2][2]==cube[3][3][3] && cube[3][3][3]==cube[1][1][1]) return cube[0][0][0];
    if(cube[0][0][3]!=' ' && cube[0][0][3]==cube[1][1][2] && cube[1][1][2]==cube[2][2][1] && cube[2][2][1]==cube[3][3][0]) return cube[0][0][3];
    if(cube[0][3][3]!=' ' && cube[0][3][3]==cube[1][2][2] && cube[1][2][2]==cube[2][1][1] && cube[2][1][1]==cube[3][1][1]) return cube[0][3][3];
    if(cube[0][3][0]!=' ' && cube[0][3][0]==cube[1][2][1] && cube[1][2][1]==cube[2][1][2] && cube[2][1][2]==cube[3][0][3]) return cube[0][3][0];
    
    return ' ';
}

//mozda postoji neki ljepsi nacin
std::vector<Move> Cube::generate_first_moves(){
    std::vector<Move> moves;
    for(int i=0;i<1;i++){
        for(int j=0;j<2;j++){
            for(int k=0;k<2;k++){
                if(cube[i][j][k]==' '){
                    moves.push_back( Move(i,j,k) );
                }
            }
        }
    }
    return moves;
}

std::vector<Move> Cube::generate_second_moves(){
    std::vector<Move> moves;
    for(int i=0;i<1;i++){
        for(int j=0;j<4;j++){
            for(int k=0;k<4-j;k++){
                if(cube[i][j][k]==' '){
                    moves.push_back( Move(i,j,k) );
                }
            }
        }
    }
    return moves;
}

//mozda postoji neki ljepsi nacin
std::vector<Move> Cube::generate_other_moves(){
    std::vector<Move> moves;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            for(int k=0;k<4;k++){
                if(cube[i][j][k]==' '){
                    moves.push_back( Move(i,j,k) );
                }
            }
        }
    }
    return moves;
}

void Cube::generate_moves(std::vector<Move>& moves){
    if(mTimes>=3)return;
    if(mTimes==2){
        moves=generate_other_moves();
    }
    else if(mTimes==1){
        moves=generate_second_moves();
    }
    else if(mTimes==0){
        moves=generate_first_moves();
    }
    mTimes++;
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

void Cube::unPlay(Move move) {
    if(cube[move.level()][move.row()][move.column()] != ' '){
        cube[move.level()][move.row()][move.column()] = ' ';
        mNumber--;
    }
}

//iscrtava kocku u terminalu
void Cube::print(){
    //printanje po nivoima
    //promjenila za provjeru
    /*
    for(int j=0;j<2;j++){
        std::cout << "Nivo " << j << ":" << std::endl;
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
    */
    int i;
    //rub prvog levela
    std::cout << "         ________________"<<std::endl;
    //prvi redak prvog levela
    std::cout << "        /";
    for(i=0;i<4;i++){
       std::cout << " " <<cube[0][0][i] << " /";
    }
    std::cout << "|" << std::endl;
    //linija 
    std::cout <<"       /___/___/___/___/ |"<<std::endl;
    //drugi redak prvog levela
    std::cout << "      /";
    for(i=0;i<4;i++){
       std::cout << " " <<cube[0][1][i] << " /";
    }
    std::cout << "  |" << std::endl;
    //linija
    std::cout <<"     /___/___/___/___/   |"<<std::endl;
    //treci redak prvog levela
    std::cout << "    /";
    for(i=0;i<4;i++){
       std::cout << " " <<cube[0][2][i] << " /";
    }
    std::cout << "    |" << std::endl;
    //linija
    std::cout <<"   /___/___/___/___/     |"<<std::endl;
    //cetvrti redak prvog levela
    std::cout << "  /";
    for(i=0;i<4;i++){
       std::cout << " " <<cube[0][3][i] << " /";
    }
    std::cout << "      |" << std::endl;
    //linija
    std::cout <<" /___/___/___/___/       |"<<std::endl;

    //ovaj dio bi trebao bit isti za svaki "blok"
    for(int j=1;j<3;j++){
        //razmaknica medu levelima
        std::cout << "|       |________|_______|"<<std::endl;
        //prvi redak drugog levela
        std::cout << "|       /";
        std::cout << " " << cube[j][0][0] << " / " << cube[j][0][1] <<
         " /|"<<cube[j][0][2]<<" / "<<cube[j][0][3]<<" /|"<<std::endl;
        //linija
        std::cout <<"|      /___/___/_|_/___/ |"<<std::endl;
        //drugi redak drugog levela
        std::cout << "|     /";
        std::cout << " " << cube[j][1][0] << " / " << cube[j][1][1] <<
         " / "<<cube[j][2][2]<<"|/ "<<cube[j][3][3]<<" /  |"<<std::endl;
        //linija
        std::cout <<"|    /___/___/___|___/   |"<<std::endl;
        //treci redak drugog levela
        std::cout << "|   /";
        std::cout << " " << cube[j][2][0] << " / " << cube[j][2][1] <<
         " / "<<cube[j][2][2]<<" /|"<<cube[j][2][3]<<" /    |"<<std::endl;
        //linija
        std::cout <<"|  /___/___/___/_|_/     |"<<std::endl;
        //cetvrti redak drugog levela
        std::cout << "| /";
        std::cout << " " << cube[j][3][0] << " / " << cube[j][3][1] <<
         " / "<<cube[j][3][2]<<" / "<<cube[j][3][3]<<"|/      |"<<std::endl;
        //linija
        std::cout <<"|/___/___/___/___|       |"<<std::endl;
    }
    //razmaknica medu levelima
        std::cout << "|       |________|_______|"<<std::endl;
        //prvi redak cetvrtog levela
        std::cout << "|       /";
        std::cout << " " << cube[3][0][0] << " / " << cube[3][0][1] <<
         " /|"<<cube[3][0][2]<<" / "<<cube[3][0][3]<<" /"<<std::endl;
        //linija
        std::cout <<"|      /___/___/_|_/___/ "<<std::endl;
        //drugi redak cetvrtog levela
        std::cout << "|     /";
        std::cout << " " << cube[3][1][0] << " / " << cube[3][1][1] <<
         " / "<<cube[3][1][2]<<"|/ "<<cube[3][1][3]<<" /  "<<std::endl;
        //linija
        std::cout <<"|    /___/___/___|___/"<<std::endl;
        //treci redak cetvrtog levela
        std::cout << "|   /";
        std::cout << " " << cube[3][2][0] << " / " << cube[3][2][1] <<
         " / "<<cube[3][2][2]<<" /|"<<cube[3][2][3]<<" /"<<std::endl;
        //linija
        std::cout <<"|  /___/___/___/_|_/"<<std::endl;
        //cetvrti redak cetvrtog levela
        std::cout << "| /";
        std::cout << " " << cube[3][3][0] << " / " << cube[3][3][1] <<
         " / "<<cube[3][3][2]<<" / "<<cube[3][3][3]<<"|/"<<std::endl;
        //linija
        std::cout <<"|/___/___/___/___|"<<std::endl;
}