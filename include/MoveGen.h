//
// Created by Maša Hozjan on 28. 07. 25.
//

#ifndef MOVEGEN_H
#define MOVEGEN_H

#include <cstdint>

uint64_t generateKnightMoves(uint64_t knight);
uint64_t generateKingMoves(uint64_t king);
uint64_t generateRookMoves(int square, uint64_t allPieces);
uint64_t generateBishopMoves(int square, uint64_t allPieces);
uint64_t generateQueenMoves(int square, uint64_t allPieces);
uint64_t generatePawnMovesWhite(int square, uint64_t allPieces, uint64_t blackPieces);
uint64_t generatePawnMovesBlack(int square, uint64_t allPieces, uint64_t whitePieces);

#endif //MOVEGEN_H
