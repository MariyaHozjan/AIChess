//
// Created by Maša Hozjan on 28. 07. 25.
//
// BoardUtils.cpp
#include "../include/BoardUtils.h"
#include <iostream>

void initializeBoard(GameState& state) {
    state.whitePieces.pawns   = 0x00FF000000000000ULL;
    state.whitePieces.knights = 0x4200000000000000ULL;
    state.whitePieces.bishops = 0x2400000000000000ULL;
    state.whitePieces.rooks   = 0x8100000000000000ULL;
    state.whitePieces.queens  = 0x0800000000000000ULL;
    state.whitePieces.king    = 0x1000000000000000ULL;

    state.blackPieces.pawns   = 0x000000000000FF00ULL;
    state.blackPieces.knights = 0x0000000000000042ULL;
    state.blackPieces.bishops = 0x0000000000000024ULL;
    state.blackPieces.rooks   = 0x0000000000000081ULL;
    state.blackPieces.queens  = 0x0000000000000008ULL;
    state.blackPieces.king    = 0x0000000000000010ULL;

    state.currentTurn = WHITE;
}

void printBoard(const GameState& state) {
    std::string board[64] = {};

    auto setSymbols = [&](uint64_t bb, const std::string& sym) {
        for (int i = 0; i < 64; ++i) {
            if ((bb >> i) & 1ULL) board[i] = sym;
        }
    };

    setSymbols(state.whitePieces.pawns,   "♙");
    setSymbols(state.whitePieces.knights, "♘");
    setSymbols(state.whitePieces.bishops, "♗");
    setSymbols(state.whitePieces.rooks,   "♖");
    setSymbols(state.whitePieces.queens,  "♕");
    setSymbols(state.whitePieces.king,    "♔");

    setSymbols(state.blackPieces.pawns,   "♟");
    setSymbols(state.blackPieces.knights, "♞");
    setSymbols(state.blackPieces.bishops, "♝");
    setSymbols(state.blackPieces.rooks,   "♜");
    setSymbols(state.blackPieces.queens,  "♛");
    setSymbols(state.blackPieces.king,    "♚");

    for (int rank = 7; rank >= 0; --rank) {
        std::cout << rank + 1 << " ";
        for (int file = 0; file < 8; ++file) {
            std::string s = board[rank * 8 + file];
            std::cout << (s.empty() ? "." : s) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "  a b c d e f g h\n";
}

int squareFromAlgebraic(const std::string& pos) {
    int file = pos[0] - 'a';
    int rank = pos[1] - '1';
    return rank * 8 + file;
}

bool isSquareOccupiedByOwnPiece(uint64_t toMask, const BitboardPosition& player) {
    uint64_t myPieces =
        player.pawns | player.knights | player.bishops |
        player.rooks | player.queens | player.king;
    return (toMask & myPieces) != 0;
}

uint64_t getAllPieces(const BitboardPosition& player, const BitboardPosition& opponent) {
    return player.pawns | player.knights | player.bishops |
           player.rooks | player.queens | player.king |
           opponent.pawns | opponent.knights | opponent.bishops |
           opponent.rooks | opponent.queens | opponent.king;
}

bool isGameOver(const GameState& state) {
    return state.whitePieces.king == 0 || state.blackPieces.king == 0;
}
