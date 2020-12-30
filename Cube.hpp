#pragma once

#include "Player.hpp"

#include <optional>
#include <vector>

class Move;
class Cube{
    private:
          //prvi indeks oznacava nivo, drugi redak i treći stupac
        
    public:
        Cube();
        int mTimes;
        int mNumber;
        char cube[4][4][4]; //treba vratiti u private ali samo da mi bude lakse provjerit minmax
        void clear();
        char value(int i, int j, int k);
        //ako je završno stanje vraća vrijednost inače ništa
        std::optional<int> result();
        //provjerava postoji li cetvorka za pobjedu ako da true, ako ne false
        char winning_line();
        std::vector<Move> generate_first_moves();
        std::vector<Move> generate_second_moves();
        std::vector<Move> generate_other_moves();
        //ova funkcija generira sve moguće poteze na tabli, sprema ih u vektor 
        void generate_moves(std::vector<Move>&);
        //odigra potez Move sa znakom char
        bool play(Move,char);
        //odigra potez unazad
        void unPlay(Move);
        //iscrtava kocku u terminalu
        void print();
};