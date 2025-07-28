//
// Created by Maša Hozjan on 22. 07. 25.
//

#ifndef BITBOARDCHESS_H
#define BITBOARDCHESS_H

#include <cstdint>
#include <iostream>
#include <bitset>
#include <string>

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

void initializeBoard(GameState&);
//void printBitboard(uint64_t board);
void printBoard(const GameState& state);

uint64_t generateKnightMoves(uint64_t knight);
uint64_t generateKingMoves(uint64_t king);
uint64_t generateRookMoves(int square, uint64_t allPieces);
uint64_t generateBishopMoves(int square, uint64_t allPieces);
uint64_t generateQueenMoves(int square, uint64_t allPieces);
uint64_t generatePawnMoves(int square, uint64_t allPieces);
uint64_t generatePawnMovesWhite(int square, uint64_t allPieces, uint64_t blackPieces);
uint64_t generatePawnMovesBlack(int square, uint64_t allPieces, uint64_t whitePieces);

#endif //BITBOARDCHESS_H
