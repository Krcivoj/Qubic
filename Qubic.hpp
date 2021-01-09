#pragma once

#include "Cube.hpp"
#include "Player.hpp"

#include <vector>


class Qubic{
    private:
        Cube* mCube;
        std::vector<Player> mPlayers;

    public:
        //stvara uvijete za početak igre
        Qubic();
        //oslobadanje memorije
        ~Qubic();

        //implementira logiku igre
        std::optional<Player> play();

};