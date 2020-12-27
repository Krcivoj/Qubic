#include "Cube.hpp"
#include "Player.hpp"

#include <vector>


class Qubic{
    private:
        Cube mCube;
        std::vector<Player> players;

    public:
        Qubic();

        std::optional<Player> play();

};