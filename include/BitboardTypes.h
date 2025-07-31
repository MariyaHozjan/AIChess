//
// Created by Maša Hozjan on 28. 07. 25.
//

#ifndef BITBOARDTYPES_H
#define BITBOARDTYPES_H

#include <cstdint>

enum Color { WHITE, BLACK };

struct BitboardPosition {
    uint64_t pawns;
    uint64_t knights;
    uint64_t bishops;
    uint64_t rooks;
    uint64_t queens;
    uint64_t king;
};

struct GameState {
    BitboardPosition whitePieces;
    BitboardPosition blackPieces;
    Color currentTurn;
};

#endif //BITBOARDTYPES_H
