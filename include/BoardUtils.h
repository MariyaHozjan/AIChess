//
// Created by Maša Hozjan on 28. 07. 25.
//

#ifndef BOARDUTILS_H
#define BOARDUTILS_H

#include "BitboardTypes.h"
#include <string>

void initializeBoard(GameState& state);
void printBoard(const GameState& state);
int squareFromAlgebraic(const std::string& pos);
bool isSquareOccupiedByOwnPiece(uint64_t toMask, const BitboardPosition& player);
uint64_t getAllPieces(const BitboardPosition& player, const BitboardPosition& opponent);
bool isGameOver(const GameState& state);

#endif //BOARDUTILS_H
