#pragma once

#include "Cube.hpp"
#include "Player.hpp"

#include <vector>


class Qubic{
    private:
        Cube mCube;
        std::vector<Player> mPlayers;

    public:
        Qubic();

        std::optional<Player> play();

};