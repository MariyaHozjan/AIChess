//
// Created by Maša Hozjan on 28. 07. 25.
//
// MoveGen.cpp
#include "../include/MoveGen.h"

uint64_t generateKnightMoves(uint64_t knight) {
    uint64_t moves = 0;
    int pos = __builtin_ctzll(knight);
    int row = pos / 8;
    int col = pos % 8;

    static constexpr int knightMoves[8][2] = {
        {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
        {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
    };

    for (auto& [dr, dc] : knightMoves) {
        int r = row + dr;
        int c = col + dc;
        if (r >= 0 && r < 8 && c >= 0 && c < 8) {
            moves |= (1ULL << (r * 8 + c));
        }
    }
    return moves;
}

uint64_t generateKingMoves(uint64_t king) {
    uint64_t moves = 0;
    int pos = __builtin_ctzll(king);
    int row = pos / 8;
    int col = pos % 8;

    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0) continue;
            int r = row + dr;
            int c = col + dc;
            if (r >= 0 && r < 8 && c >= 0 && c < 8) {
                moves |= (1ULL << (r * 8 + c));
            }
        }
    }
    return moves;
}

uint64_t generateRookMoves(int square, uint64_t allPieces) {
    uint64_t moves = 0;
    int row = square / 8;
    int col = square % 8;

    for (int r = row + 1; r < 8; ++r) {
        int sq = r * 8 + col;
        moves |= (1ULL << sq);
        if (allPieces & (1ULL << sq)) break;
    }
    for (int r = row - 1; r >= 0; --r) {
        int sq = r * 8 + col;
        moves |= (1ULL << sq);
        if (allPieces & (1ULL << sq)) break;
    }
    for (int c = col + 1; c < 8; ++c) {
        int sq = row * 8 + c;
        moves |= (1ULL << sq);
        if (allPieces & (1ULL << sq)) break;
    }
    for (int c = col - 1; c >= 0; --c) {
        int sq = row * 8 + c;
        moves |= (1ULL << sq);
        if (allPieces & (1ULL << sq)) break;
    }
    return moves;
}

uint64_t generateBishopMoves(int square, uint64_t allPieces) {
    uint64_t moves = 0;
    int row = square / 8;
    int col = square % 8;

    for (int r = row + 1, c = col + 1; r < 8 && c < 8; ++r, ++c) {
        int sq = r * 8 + c;
        moves |= (1ULL << sq);
        if (allPieces & (1ULL << sq)) break;
    }
    for (int r = row + 1, c = col - 1; r < 8 && c >= 0; ++r, --c) {
        int sq = r * 8 + c;
        moves |= (1ULL << sq);
        if (allPieces & (1ULL << sq)) break;
    }
    for (int r = row - 1, c = col + 1; r >= 0 && c < 8; --r, ++c) {
        int sq = r * 8 + c;
        moves |= (1ULL << sq);
        if (allPieces & (1ULL << sq)) break;
    }
    for (int r = row - 1, c = col - 1; r >= 0 && c >= 0; --r, --c) {
        int sq = r * 8 + c;
        moves |= (1ULL << sq);
        if (allPieces & (1ULL << sq)) break;
    }
    return moves;
}

uint64_t generateQueenMoves(int square, uint64_t allPieces) {
    return generateRookMoves(square, allPieces) | generateBishopMoves(square, allPieces);
}

uint64_t generatePawnMovesWhite(int square, uint64_t allPieces, uint64_t blackPieces) {
    uint64_t moves = 0;
    int row = square / 8;
    int col = square % 8;
    int oneAhead = square - 8;

    if (oneAhead >= 0 && !(allPieces & (1ULL << oneAhead))) {
        moves |= (1ULL << oneAhead);
        int twoAhead = square - 16;
        if (row == 6 && !(allPieces & (1ULL << twoAhead))) {
            moves |= (1ULL << twoAhead);
        }
    }
    if (col > 0) {
        int leftCapture = square - 9;
        if (leftCapture >= 0 && (blackPieces & (1ULL << leftCapture))) {
            moves |= (1ULL << leftCapture);
        }
    }
    if (col < 7) {
        int rightCapture = square - 7;
        if (rightCapture >= 0 && (blackPieces & (1ULL << rightCapture))) {
            moves |= (1ULL << rightCapture);
        }
    }
    return moves;
}

uint64_t generatePawnMovesBlack(int square, uint64_t allPieces, uint64_t whitePieces) {
    uint64_t moves = 0;
    int row = square / 8;
    int col = square % 8;
    int oneAhead = square + 8;

    if (oneAhead < 64 && !(allPieces & (1ULL << oneAhead))) {
        moves |= (1ULL << oneAhead);
        int twoAhead = square + 16;
        if (row == 1 && !(allPieces & (1ULL << twoAhead))) {
            moves |= (1ULL << twoAhead);
        }
    }
    if (col > 0) {
        int leftCapture = square + 7;
        if (leftCapture < 64 && (whitePieces & (1ULL << leftCapture))) {
            moves |= (1ULL << leftCapture);
        }
    }
    if (col < 7) {
        int rightCapture = square + 9;
        if (rightCapture < 64 && (whitePieces & (1ULL << rightCapture))) {
            moves |= (1ULL << rightCapture);
        }
    }
    return moves;
}