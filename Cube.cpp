#include "Cube.hpp"

//stvara praznu kocku
Cube::Cube() {
    clear();
}

//kocku pretvara u praznu koku
void Cube::clear() {
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            for(int k=0; k<4; k++)
                cube[i][j][k]=' ';    
}


//vraća 1 ako je X pobjedio, -1 ako je O pobjedio, 0 ako je nerjeseno
//ako nije nista od navedenog prazan optional
std::optional<int> Cube::result() {

}

//iscrtava kocku u terminalu
void Cube::print() {
    
}

//odigra potez na poziciji move 
//vraca true ako je move bio valjan
bool Cube::play(std::vector<int> move) {
    
}
