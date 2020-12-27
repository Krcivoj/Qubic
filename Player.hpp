#include "Cube.hpp"

#include <vector>

class Player{
    private:
        char name;

        std::vector<int> minMax(Cube&, char);
    public:
        Player();
        Player(char);

        char id();
        void play(Cube&);
};