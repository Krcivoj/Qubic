#include "Cube.hpp"
#include <iostream>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//stvara praznu kocku
Cube3::Cube3() {
    mNumber=0;
    clear();
}

//kocku pretvara u praznu kocku
void Cube3::clear() {
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            for(int k=0; k<3; k++)
                cube[i][j][k]=' ';    
}

char Cube3::value(int i, int j, int k){
    return cube[i][j][k];
}

//vraća 1 ako je X pobjedio, -1 ako je O pobjedio, 0 ako je nerjeseno
//ako nije nista od navedenog prazan optional
std::optional<int> Cube3::result() {
    char winner=winning_line();
    if(winner=='X') return 500;
    if(winner=='O') return -500; 
    if(mNumber>=27) return 0;
    return {};
}

char Cube3::winning_line(){
    //najprije po levelima provjerimo dobitke u horizontalnom polozaju =24slučajeva
    for(int i=0;i<3;i++){
        //provjera po redcima
        for(int j=0;j<3;j++){
            if(cube[i][j][0]!=' ' && cube[i][j][0]==cube[i][j][1] && cube[i][j][1]==cube[i][j][2]) return cube[i][j][0];
        }
        //provjera po stupcima
        for(int j=0;j<3;j++){
            if(cube[i][0][j]!=' ' && cube[i][0][j]==cube[i][1][j] && cube[i][1][j]==cube[i][2][j]) return cube[i][0][j];
        }
        //provjera dvije dijagonale
        if(cube[i][0][0]!=' ' && cube[i][0][0]==cube[i][1][1] && cube[i][1][1]==cube[i][2][2]) return cube[i][0][0];
        if(cube[i][0][2]!=' ' && cube[i][0][2]==cube[i][1][1] && cube[i][1][1]==cube[i][2][0]) return cube[i][0][2];
    }
    
    //za vertikalne netrebam provjeravat horizontalne jer to vec jesmo =15
    for(int i=0;i<3;i++){
        //provjera po stupcima
        for(int j=0;j<3;j++){
            if(cube[0][j][i]!=' ' && cube[0][j][i]==cube[1][j][i] && cube[1][j][i]==cube[2][j][i]) return cube[0][j][i];
        }
        //provjera dvije dijagonale
        if(cube[0][0][i]!=' ' && cube[0][0][i]==cube[1][1][i] && cube[1][1][i]==cube[2][2][i]) return cube[0][0][i];
        if(cube[0][2][i]!=' ' && cube[0][2][i]==cube[1][1][i] && cube[1][1][i]==cube[2][0][i]) return cube[0][2][i];
    }
    //fale mi dijagonale po redcima =6
    for(int i=0;i<3;i++){
        if(cube[0][i][0]!=' ' && cube[0][i][0]==cube[1][i][1] && cube[1][i][1]==cube[2][i][2]) return cube[0][i][0];
        if(cube[0][i][2]!=' ' && cube[0][i][2]==cube[1][i][1] && cube[1][i][1]==cube[2][i][0]) return cube[0][i][2];
    }
    //unutrasnje dijagonale =4
    if(cube[0][0][0]!=' ' && cube[0][0][0]==cube[2][2][2] && cube[2][2][2]==cube[1][1][1]) return cube[0][0][0];
    if(cube[0][0][2]!=' ' && cube[0][0][2]==cube[1][1][1] && cube[1][1][1]==cube[2][2][0]) return cube[0][0][2];
    if(cube[0][2][2]!=' ' && cube[0][2][2]==cube[1][1][1] && cube[1][1][1]==cube[2][0][0]) return cube[0][2][2];
    if(cube[0][2][0]!=' ' && cube[0][2][0]==cube[1][1][1] && cube[1][1][1]==cube[2][0][2]) return cube[0][2][0];
    
    return ' ';
}

std::vector<Move> Cube3::generate_moves(){
    std::vector<Move> moves;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){
                if(cube[i][j][k]==' '){
                    moves.push_back( Move(i,j,k) );
                }
            }
        }
    }
    return moves;
}

bool Cube3::isValid(Move move) {
    if(move.level()<0 || move.level()>2) return false;
    if(move.row()<0 || move.row()>2) return false;
    if(move.column()<0 || move.column()>2) return false;
    if(value(move.level(),move.row(),move.column())!=' ') return false;
    return true;
}

//odigra potez na poziciji move i poveća broj odigranih
//vraca true ako je move bio valjan
//mozda promjenit ovu provjeru
bool Cube3::play(Move move,char c) {
    if(!isValid(move)) return false;
    cube[move.level()][move.row()][move.column()] = c;
    mNumber++;
    return true;
}

void Cube3::unPlay(Move move) {
    if(cube[move.level()][move.row()][move.column()] != ' '){
        cube[move.level()][move.row()][move.column()] = ' ';
        mNumber--;
    }
}

int Cube3::heuristic(char player, char opponent){
    //idem po svim winning lines i brojim koliko se znakova ukupno nalazi nasih i protivnikovih
    int result=0;
    for(int i=0;i<3;i++){
        //provjera po redcima
        for(int j=0;j<3;j++){
            int broj_pl=0;
            int broj_op=0;
            for(int k=0;k<3;k++){
                if(cube[i][j][k]==player) broj_pl++;
                if(cube[i][j][k]==opponent) broj_op++;
            }
            if(broj_pl>0 && broj_op==0){
                if(broj_pl==1) result+=2;
                else if(broj_pl==2) result+=4;
            }
            else if(broj_pl==0 && broj_op>0){
                if(broj_op==1) result-=1;
                else if(broj_op==2) result-=3;
            }
        }
        //provjera po stupcima
        for(int j=0;j<3;j++){
            int broj_pl=0;
            int broj_op=0;
            for(int k=0;k<3;k++){
                if(cube[i][k][j]==player) broj_pl++;
                if(cube[i][k][j]==opponent) broj_op++;
            }
            if(broj_pl>0 && broj_op==0){
                if(broj_pl==1) result+=2;
                else if(broj_pl==2) result+=4;
            }
            else if(broj_pl==0 && broj_op>0){
                if(broj_op==1) result-=1;
                else if(broj_op==2) result-=3;
            }
        }
        //provjera dvije dijagonale
        int broj_pl=0;
        int broj_op=0;
        for(int k=0;k<3;k++){
            if(cube[i][k][k]==player) broj_pl++;
            if(cube[i][k][k]==opponent) broj_op++;
        }
        if(broj_pl>0 && broj_op==0){
            if(broj_pl==1) result+=2;
            else if(broj_pl==2) result+=4;
        }
        else if(broj_pl==0 && broj_op>0){
            if(broj_op==1) result-=1;
            else if(broj_op==2) result-=3;
        }
        broj_pl=0;
        broj_op=0;
        for(int k=0;k<3;k++){
            if(cube[i][k][2-k]==player) broj_pl++;
            if(cube[i][k][2-k]==opponent) broj_op++;
        }
        if(broj_pl>0 && broj_op==0){
            if(broj_pl==1) result+=2;
            else if(broj_pl==2) result+=4;
        }
        else if(broj_pl==0 && broj_op>0){
            if(broj_op==1) result-=1;
            else if(broj_op==2) result-=3;
        }
    }
    //za vertikalne netrebam provjeravat horizontalne jer to vec jesmo
    for(int i=0;i<3;i++){
        //provjera po stupcima
        for(int j=0;j<3;j++){
            int broj_pl=0;
            int broj_op=0;
            for(int k=0;k<3;k++){
                if(cube[k][j][i]==player) broj_pl++;
                if(cube[k][j][i]==opponent) broj_op++;
            }
            if(broj_pl>0 && broj_op==0){
                if(broj_pl==1) result+=2;
                else if(broj_pl==2) result+=4;
            }
            else if(broj_pl==0 && broj_op>0){
                if(broj_op==1) result-=1;
                else if(broj_op==2) result-=3;
            }
        }
        //provjera dvije dijagonale
        int broj_pl=0;
        int broj_op=0;
        for(int k=0;k<3;k++){
            if(cube[k][k][i]==player) broj_pl++;
            if(cube[k][k][i]==opponent) broj_op++;
        }
        if(broj_pl>0 && broj_op==0){
            if(broj_pl==1) result+=2;
            else if(broj_pl==2) result+=4;
        }
        else if(broj_pl==0 && broj_op>0){
            if(broj_op==1) result-=1;
            else if(broj_op==2) result-=3;
        }
        broj_pl=0;
        broj_op=0;
        for(int k=0;k<3;k++){
            if(cube[k][2-k][i]==player) broj_pl++;
            if(cube[k][2-k][i]==opponent) broj_op++;
        }
        if(broj_pl>0 && broj_op==0){
            if(broj_pl==1) result+=2;
            else if(broj_pl==2) result+=4;
        }
        else if(broj_pl==0 && broj_op>0){
            if(broj_op==1) result-=1;
            else if(broj_op==2) result-=3;
        }
    }
    //fale mi dijagonale po redcima
    for(int i=0;i<3;i++){
        int broj_pl=0;
        int broj_op=0;
        for(int k=0;k<3;k++){
            if(cube[k][i][k]==player) broj_pl++;
            if(cube[k][i][k]==opponent) broj_op++;
        }
        if(broj_pl>0 && broj_op==0){
            if(broj_pl==1) result+=2;
            else if(broj_pl==2) result+=4;
        }
        else if(broj_pl==0 && broj_op>0){
            if(broj_op==1) result-=1;
            else if(broj_op==2) result-=3;
        }
        broj_pl=0;
        broj_op=0;
        for(int k=0;k<3;k++){
            if(cube[k][i][2-k]==player) broj_pl++;
            if(cube[k][i][2-k]==opponent) broj_op++;
        }
        if(broj_pl>0 && broj_op==0){
            if(broj_pl==1) result+=2;
            else if(broj_pl==2) result+=4;
        }
        else if(broj_pl==0 && broj_op>0){
            if(broj_op==1) result-=1;
            else if(broj_op==2) result-=3;
        }
    }
    //unutarnje dijagonale
    int broj_pl=0;
    int broj_op=0;
    for(int i=0;i<3;i++){
        if(cube[i][i][i]==player) broj_pl++;
        else if(cube[i][i][i]==opponent) broj_op++;
    }
    if(broj_pl>0 && broj_op==0){
        if(broj_pl==1) result+=2;
        else if(broj_pl==2) result+=4;
    }
    else if(broj_pl==0 && broj_op>0){
        if(broj_op==1) result-=1;
        else if(broj_op==2) result-=3;
    }
    broj_pl=0;
    broj_op=0;
    for(int i=0;i<3;i++){
        if(cube[i][i][2-i]==player) broj_pl++;
        else if(cube[i][i][2-i]==opponent) broj_op++;
    }
    if(broj_pl>0 && broj_op==0){
        if(broj_pl==1) result+=2;
        else if(broj_pl==2) result+=4;
    }
    else if(broj_pl==0 && broj_op>0){
        if(broj_op==1) result-=1;
        else if(broj_op==2) result-=3;
    }
    broj_pl=0;
    broj_op=0;
    for(int i=0;i<3;i++){
        if(cube[2-i][i][i]==player) broj_pl++;
        else if(cube[2-i][i][i]==opponent) broj_op++;
    }
    if(broj_pl>0 && broj_op==0){
        if(broj_pl==1) result+=2;
        else if(broj_pl==2) result+=4;
    }
    else if(broj_pl==0 && broj_op>0){
        if(broj_op==1) result-=1;
        else if(broj_op==2) result-=3;
    }
    broj_pl=0;
    broj_op=0;
    for(int i=0;i<3;i++){
        if(cube[i][2-i][i]==player) broj_pl++;
        else if(cube[i][2-i][i]==opponent) broj_op++;
    }
    if(broj_pl>0 && broj_op==0){
        if(broj_pl==1) result+=2;
        else if(broj_pl==2) result+=4;
    }
    else if(broj_pl==0 && broj_op>0){
        if(broj_op==1) result-=1;
        else if(broj_op==2) result-=3;
    }
    if (player=='O') return -result;
    return result;
}

int Cube3::maxDepth() {
    return 27-mNumber;
}

void Cube3::print(){
    //printanje po nivoima
    //promjenila za provjeru
    for(int j=0;j<3;j++){
        std::cout << "Nivo " << j << ":" << std::endl;
        for(int i=0;i<13;i++){
            std::cout << "-";
        }
        std::cout << std::endl;
        //printanje po redcima
        for(int k=0;k<3;k++){
            //sad printamo redak s vrijednostima
            std::cout << "| " << cube[j][k][0] << " | " << cube[j][k][1] << " | " << cube[j][k][2]<< " |"<<std::endl;
            //donja linija
            for(int i=0;i<13;i++){
                std::cout << "-";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////

//stvara praznu kocku
Cube4::Cube4() {
    mNumber=0;
    clear();
}

//kocku pretvara u praznu kocku
void Cube4::clear() {
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            for(int k=0; k<4; k++)
                cube[i][j][k]=' ';    
}

char Cube4::value(int i, int j, int k){
    return cube[i][j][k];
}

//vraća 1 ako je X pobjedio, -1 ako je O pobjedio, 0 ako je nerjeseno
//ako nije nista od navedenog prazan optional
std::optional<int> Cube4::result() {
    char winner=winning_line();
    if(winner=='X') return 500;
    if(winner=='O') return -500; 
    if(mNumber>=64) return 0;
    return {};
}

char Cube4::winning_line(){
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

std::vector<Move> Cube4::generate_moves(){
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

bool Cube4::isValid(Move move) {
    if(move.level()<0 || move.level()>3) return false;
    if(move.row()<0 || move.row()>3) return false;
    if(move.column()<0 || move.column()>3) return false;
    if(value(move.level(),move.row(),move.column())!=' ') return false;
    return true;
}

//odigra potez na poziciji move i poveća broj odigranih
//vraca true ako je move bio valjan
//mozda promjenit ovu provjeru
bool Cube4::play(Move move,char c) {
    if(!isValid(move)) return false;
    cube[move.level()][move.row()][move.column()] = c;
    mNumber++;
    return true;
}

void Cube4::unPlay(Move move) {
    if(cube[move.level()][move.row()][move.column()] != ' '){
        cube[move.level()][move.row()][move.column()] = ' ';
        mNumber--;
    }
}

//iscrtava kocku u terminalu
void Cube4::print(){
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
         " / "<<cube[j][1][2]<<"|/ "<<cube[j][1][3]<<" /  |"<<std::endl;
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

int Cube4::heuristic(char player, char opponent){
    //idem po svim winning lines i brojim koliko se znakova ukupno nalazi nasih i protivnikovih
    int result=0;
    for(int i=0;i<4;i++){
        //provjera po redcima
        for(int j=0;j<4;j++){
            int broj_pl=0;
            int broj_op=0;
            for(int k=0;k<4;k++){
                if(cube[i][j][k]==player) broj_pl++;
                if(cube[i][j][k]==opponent) broj_op++;
            }
            if(broj_pl>0 && broj_op==0){
                if(broj_pl==1) result+=2;
                else if(broj_pl==2) result+=4;
                else if(broj_pl==3) result+=6;
            }
            else if(broj_pl==0 && broj_op>0){
                if(broj_op==1) result-=1;
                else if(broj_op==2) result-=3;
                else if(broj_op==3) result-=5;
            }
        }
        //provjera po stupcima
        for(int j=0;j<4;j++){
            int broj_pl=0;
            int broj_op=0;
            for(int k=0;k<4;k++){
                if(cube[i][k][j]==player) broj_pl++;
                if(cube[i][k][j]==opponent) broj_op++;
            }
            if(broj_pl>0 && broj_op==0){
                if(broj_pl==1) result+=2;
                else if(broj_pl==2) result+=4;
                else if(broj_pl==3) result+=6;
            }
            else if(broj_pl==0 && broj_op>0){
                if(broj_op==1) result-=1;
                else if(broj_op==2) result-=3;
                else if(broj_op==3) result-=5;
            }
        }
        //provjera dvije dijagonale
        int broj_pl=0;
        int broj_op=0;
        for(int k=0;k<4;k++){
            if(cube[i][k][k]==player) broj_pl++;
            if(cube[i][k][k]==opponent) broj_op++;
        }
        if(broj_pl>0 && broj_op==0){
            if(broj_pl==1) result+=2;
            else if(broj_pl==2) result+=4;
            else if(broj_pl==3) result+=6;
        }
        else if(broj_pl==0 && broj_op>0){
            if(broj_op==1) result-=1;
            else if(broj_op==2) result-=3;
            else if(broj_op==3) result-=5;
        }
        broj_pl=0;
        broj_op=0;
        for(int k=0;k<4;k++){
            if(cube[i][k][3-k]==player) broj_pl++;
            if(cube[i][k][3-k]==opponent) broj_op++;
        }
        if(broj_pl>0 && broj_op==0){
            if(broj_pl==1) result+=2;
            else if(broj_pl==2) result+=4;
            else if(broj_pl==3) result+=6;
        }
        else if(broj_pl==0 && broj_op>0){
            if(broj_op==1) result-=1;
            else if(broj_op==2) result-=3;
            else if(broj_op==3) result-=5;
        }
    }
    //za vertikalne netrebam provjeravat horizontalne jer to vec jesmo
    for(int i=0;i<4;i++){
        //provjera po stupcima
        for(int j=0;j<4;j++){
            int broj_pl=0;
            int broj_op=0;
            for(int k=0;k<4;k++){
                if(cube[k][j][i]==player) broj_pl++;
                if(cube[k][j][i]==opponent) broj_op++;
            }
            if(broj_pl>0 && broj_op==0){
                if(broj_pl==1) result+=2;
                else if(broj_pl==2) result+=4;
                else if(broj_pl==3) result+=6;
            }
            else if(broj_pl==0 && broj_op>0){
                if(broj_op==1) result-=1;
                else if(broj_op==2) result-=3;
                else if(broj_op==3) result-=5;
            }
        }
        //provjera dvije dijagonale
        int broj_pl=0;
        int broj_op=0;
        for(int k=0;k<4;k++){
            if(cube[k][k][i]==player) broj_pl++;
            if(cube[k][k][i]==opponent) broj_op++;
        }
        if(broj_pl>0 && broj_op==0){
            if(broj_pl==1) result+=2;
            else if(broj_pl==2) result+=4;
            else if(broj_pl==3) result+=6;
        }
        else if(broj_pl==0 && broj_op>0){
            if(broj_op==1) result-=1;
            else if(broj_op==2) result-=3;
            else if(broj_op==3) result-=5;
        }
        broj_pl=0;
        broj_op=0;
        for(int k=0;k<4;k++){
            if(cube[k][3-k][i]==player) broj_pl++;
            if(cube[k][3-k][i]==opponent) broj_op++;
        }
        if(broj_pl>0 && broj_op==0){
            if(broj_pl==1) result+=2;
            else if(broj_pl==2) result+=4;
            else if(broj_pl==3) result+=6;
        }
        else if(broj_pl==0 && broj_op>0){
            if(broj_op==1) result-=1;
            else if(broj_op==2) result-=3;
            else if(broj_op==3) result-=5;
        }
    }
    //fale mi dijagonale po redcima
    for(int i=0;i<4;i++){
        int broj_pl=0;
        int broj_op=0;
        for(int k=0;k<4;k++){
            if(cube[k][i][k]==player) broj_pl++;
            if(cube[k][i][k]==opponent) broj_op++;
        }
        if(broj_pl>0 && broj_op==0){
            if(broj_pl==1) result+=2;
            else if(broj_pl==2) result+=4;
            else if(broj_pl==3) result+=6;
        }
        else if(broj_pl==0 && broj_op>0){
            if(broj_op==1) result-=1;
            else if(broj_op==2) result-=3;
            else if(broj_op==3) result-=5;
        }
        broj_pl=0;
        broj_op=0;
        for(int k=0;k<4;k++){
            if(cube[k][i][3-k]==player) broj_pl++;
            if(cube[k][i][3-k]==opponent) broj_op++;
        }
        if(broj_pl>0 && broj_op==0){
            if(broj_pl==1) result+=2;
            else if(broj_pl==2) result+=4;
            else if(broj_pl==3) result+=6;
        }
        else if(broj_pl==0 && broj_op>0){
            if(broj_op==1) result-=1;
            else if(broj_op==2) result-=3;
            else if(broj_op==3) result-=5;
        }
    }
    //unutrasnje dijagonale
    int broj_pl=0;
    int broj_op=0;
    for(int i=0;i<4;i++){
        if(cube[i][i][i]==player) broj_pl++;
        else if(cube[i][i][i]==opponent) broj_op++;
    }
    if(broj_pl>0 && broj_op==0){
            if(broj_pl==1) result+=2;
            else if(broj_pl==2) result+=4;
            else if(broj_pl==3) result+=6;
        }
        else if(broj_pl==0 && broj_op>0){
            if(broj_op==1) result-=1;
            else if(broj_op==2) result-=3;
            else if(broj_op==3) result-=5;
        }
    broj_pl=0;
    broj_op=0;
    for(int i=0;i<4;i++){
        if(cube[i][i][3-i]==player) broj_pl++;
        else if(cube[i][i][3-i]==opponent) broj_op++;
    }
    if(broj_pl>0 && broj_op==0){
            if(broj_pl==1) result+=2;
            else if(broj_pl==2) result+=4;
            else if(broj_pl==3) result+=6;
        }
        else if(broj_pl==0 && broj_op>0){
            if(broj_op==1) result-=1;
            else if(broj_op==2) result-=3;
            else if(broj_op==3) result-=5;
        }
    broj_pl=0;
    broj_op=0;
    for(int i=0;i<4;i++){
        if(cube[3-i][i][i]==player) broj_pl++;
        else if(cube[3-i][i][i]==opponent) broj_op++;
    }
    if(broj_pl>0 && broj_op==0){
            if(broj_pl==1) result+=2;
            else if(broj_pl==2) result+=4;
            else if(broj_pl==3) result+=6;
        }
        else if(broj_pl==0 && broj_op>0){
            if(broj_op==1) result-=1;
            else if(broj_op==2) result-=3;
            else if(broj_op==3) result-=5;
        }
    broj_pl=0;
    broj_op=0;
    for(int i=0;i<4;i++){
        if(cube[i][3-i][i]==player) broj_pl++;
        else if(cube[i][3-i][i]==opponent) broj_op++;
    }
    if(broj_pl>0 && broj_op==0){
            if(broj_pl==1) result+=2;
            else if(broj_pl==2) result+=4;
            else if(broj_pl==3) result+=6;
        }
        else if(broj_pl==0 && broj_op>0){
            if(broj_op==1) result-=1;
            else if(broj_op==2) result-=3;
            else if(broj_op==3) result-=5;
        }
    if(player=='O') return -result;
    return result;
}

int Cube4::maxDepth() {
    return 6;
}
