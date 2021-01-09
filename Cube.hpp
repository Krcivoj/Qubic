#pragma once

#include "Player.hpp"

#include <optional>
#include <vector>

class Move;

class Cube{
    public:
        //cisti kocku
        virtual void clear()=0;
        //vraca vrijednost koja se nalazi na poziciji (i,j,k)
        virtual char value(int i, int j, int k)=0;
        //ako je završno stanje vraća vrijednost inače ništa
        virtual std::optional<int> result()=0;
        //ova funkcija generira sve moguće poteze na tabli, sprema ih u vektor
        virtual std::vector<Move> generate_moves()=0; 
        //odigra potez Move sa znakom char
        virtual bool play(Move,char)=0;
        //odigra potez unazad
        virtual void unPlay(Move)=0;
        //heuristicka funkcija
        virtual int heuristic(char,char)=0;
        //vraca optimalnu dubinu minmax
        virtual int maxDepth()=0;
        //iscrtava kocku u terminalu
        virtual void print()=0;
};

class Cube3: public Cube{
    private:
        //prvi indeks oznacava nivo, drugi redak i treći stupac
        char cube[3][3][3];
        int mNumber;

        //provjerava postoji li cetvorka za pobjedu ako da true, ako ne false
        char winning_line();
        
    public:
        //konstruktor stvara kocku spremnu za igru
        Cube3();
        //cisti kocku
        void clear();
        //vraca vrijednost koja se nalazi na poziciji (i,j,k)
        char value(int i, int j, int k);
        //ako je završno stanje vraća vrijednost inače ništa
        std::optional<int> result();
        //ova funkcija generira sve moguće poteze na tabli, sprema ih u vektor
        std::vector<Move> generate_moves();
        bool isValid(Move); 
        //odigra potez Move sa znakom char
        bool play(Move,char);
        //odigra potez unazad
        void unPlay(Move);
        //heuristicka funkcija: 
        //prvi char = player, drugi char = opponent
        //svi slucajevi uz uvijete da je samo jedna vrsta oznaka u lineu:
        //ako player ima 2 u redu onda +4 boda
        //ako player ima 1 u redu onda +2 boda
        //ako opponent ima 2 u redu onda -3 boda
        //ako opponent ima 1 u redu onda -1 boda
        int heuristic(char,char);
        //vraca optimalnu dubinu minmax
        int maxDepth();
        //iscrtava kocku u terminalu
        void print();
};

class Cube4: public Cube{
    private:
        //prvi indeks oznacava nivo, drugi redak i treći stupac
        char cube[4][4][4];
        //broj odigranih poteza <=> broj znakova igraca na tabli
        int mNumber;

        //provjerava postoji li cetvorka za pobjedu ako da true, ako ne false
        char winning_line();
        
    public:
        //konstruktor stvara kocku spremnu za igru
        Cube4();
        //cisti kocku
        void clear();
        //vraca vrijednost koja se nalazi na poziciji (i,j,k)
        char value(int i, int j, int k);
        //ako je završno stanje vraća vrijednost inače ništa
        std::optional<int> result();
        //ova funkcija generira sve moguće poteze na tabli, sprema ih u vektor
        std::vector<Move> generate_moves();
        bool isValid(Move); 
        //odigra potez Move sa znakom char
        bool play(Move,char);
        //odigra potez unazad
        void unPlay(Move);
        //heuristicka funkcija: 
        //prvi char = player, drugi char = opponent
        //svi slucajevi uz uvijete da je samo jedna vrsta oznaka u lineu:
        //ako player ima 3 u redu onda +6 boda
        //ako player ima 2 u redu onda +4 boda
        //ako player ima 1 u redu onda +2 boda
        //ako opponent ima 3 u redu onda -5 boda
        //ako opponent ima 2 u redu onda -3 boda
        //ako opponent ima 1 u redu onda -1 boda
        int heuristic(char,char);
        //vraca optimalnu dubinu minmax
        int maxDepth();
        //iscrtava kocku u terminalu
        void print();
};