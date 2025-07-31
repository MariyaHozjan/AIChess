//
// Created by Maša Hozjan on 28. 07. 25.
//

#ifndef GAME_H
#define GAME_H
#include "BitboardTypes.h"

class Game {
public:
    void run();
private:
    void captureAt(BitboardPosition& opponent, uint64_t toMask);
};

#endif //GAME_H
