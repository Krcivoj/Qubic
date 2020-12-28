#pragma once

#include "Player.hpp"

#include <optional>
#include <vector>

class Move;
class Cube{
    private:
        char cube[4][4][4];  //prvi indeks oznacava nivo, drugi redak i treći stupac
        int mNumber;
    public:
        Cube();
        
        void clear();
        char value(int i, int j, int k);
        //ako je završno stanje vraća vrijednost inače ništa
        std::optional<int> result();
        //provjerava postoji li cetvorka za pobjedu ako da true, ako ne false
        bool winning_line(char);
        //ova funkcija generira sve moguće poteze na tabli, sprema ih u vektor 
        std::vector<Move> generate_moves();
        //odigra potez Move sa znakom char
        bool play(Move,char);
        //iscrtava kocku u terminalu
        void print();
};