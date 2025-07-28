//
// Created by Maša Hozjan on 22. 07. 25.
//

#include "../include/BitboardChess.h"

void initializeBoard(GameState& state) {
    state.whitePieces.pawns   = 0b0000000011111111000000000000000000000000000000000000000000000000ULL;
    state.whitePieces.knights = 0b0100001000000000000000000000000000000000000000000000000000000000ULL;
    state.whitePieces.bishops = 0b0010010000000000000000000000000000000000000000000000000000000000ULL;
    state.whitePieces.rooks   = 0b1000000100000000000000000000000000000000000000000000000000000000ULL;
    state.whitePieces.queens  = 0b0000100000000000000000000000000000000000000000000000000000000000ULL;
    state.whitePieces.king    = 0b0001000000000000000000000000000000000000000000000000000000000000ULL;

    state.blackPieces.pawns   = 0b0000000000000000000000000000000000000000000000001111111100000000ULL;
    state.blackPieces.knights = 0b0000000000000000000000000000000000000000000000000000000001000010ULL;
    state.blackPieces.bishops = 0b0000000000000000000000000000000000000000000000000000000000100100ULL;
    state.blackPieces.rooks   = 0b0000000000000000000000000000000000000000000000000000000010000001ULL;
    state.blackPieces.queens  = 0b0000000000000000000000000000000000000000000000000000000000001000ULL;
    state.blackPieces.king    = 0b0000000000000000000000000000000000000000000000000000000000010000ULL;

    state.currentTurn = WHITE;
}

/*
//Outputs bitboard in a 0 and 1 format. Eg. printBitboard(state.whitePieces.knights);
void printBitboard(uint64_t board) {
    for (int rank = 7; rank >= 0; --rank) {
        for (int file = 0; file < 8; ++file) {
            int square = rank * 8 + file;
            std::cout << ((board >> square) & 1ULL);
        }
        std::cout << std::endl;
    }
}
*/

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

uint64_t generateKnightMoves(uint64_t knight) {
    uint64_t moves = 0;
    int pos = __builtin_ctzll(knight); // least significant bit index
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
    int row = square / 8; //Convert square index (0–63) into row and column
    int col = square % 8;

    // Up
    for (int r = row + 1; r < 8; ++r) {
        int sq = r * 8 + col;
        moves |= (1ULL << sq); //Add each square to moves until we hit a piece or the end of the board
        if (allPieces & (1ULL << sq)) break; //Stops if a piece blocks the way
    }
    // Down
    for (int r = row - 1; r >= 0; --r) {
        int sq = r * 8 + col;
        moves |= (1ULL << sq);
        if (allPieces & (1ULL << sq)) break;
    }
    // Right
    for (int c = col + 1; c < 8; ++c) {
        int sq = row * 8 + c;
        moves |= (1ULL << sq);
        if (allPieces & (1ULL << sq)) break;
    }
    // Left
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

    // Up-right
    for (int r = row + 1, c = col + 1; r < 8 && c < 8; ++r, ++c) {
        int sq = r * 8 + c;
        moves |= (1ULL << sq);
        if (allPieces & (1ULL << sq)) break;
    }
    // Up-left
    for (int r = row + 1, c = col - 1; r < 8 && c >= 0; ++r, --c) {
        int sq = r * 8 + c;
        moves |= (1ULL << sq);
        if (allPieces & (1ULL << sq)) break;
    }
}

uint64_t generateQueenMoves(int square, uint64_t allPieces) {
    uint64_t moves = 0;
    int row = square / 8;
    int col = square % 8;

    // Up
    for (int r = row + 1; r < 8; ++r) {
        int sq = r * 8 + col;
        moves |= (1ULL << sq); //Add each square to moves until we hit a piece or the end of the board
        if (allPieces & (1ULL << sq)) break; //Stops if a piece blocks the way
    }
    // Down
    for (int r = row - 1; r >= 0; --r) {
        int sq = r * 8 + col;
        moves |= (1ULL << sq);
        if (allPieces & (1ULL << sq)) break;
    }
    // Right
    for (int c = col + 1; c < 8; ++c) {
        int sq = row * 8 + c;
        moves |= (1ULL << sq);
        if (allPieces & (1ULL << sq)) break;
    }
    // Left
    for (int c = col - 1; c >= 0; --c) {
        int sq = row * 8 + c;
        moves |= (1ULL << sq);
        if (allPieces & (1ULL << sq)) break;
    }
    // Up-right
    for (int r = row + 1, c = col + 1; r < 8 && c < 8; ++r, ++c) {
        int sq = r * 8 + c;
        moves |= (1ULL << sq);
        if (allPieces & (1ULL << sq)) break;
    }
    // Up-left
    for (int r = row + 1, c = col - 1; r < 8 && c >= 0; ++r, --c) {
        int sq = r * 8 + c;
        moves |= (1ULL << sq);
        if (allPieces & (1ULL << sq)) break;
    }
    return moves;
}

uint64_t generatePawnMovesWhite(int square, uint64_t allPieces, uint64_t blackPieces) {
    uint64_t moves = 0;
    int row = square / 8;
    int col = square % 8;

    // White moves down the board
    int oneAhead = square - 8;
    if (oneAhead >= 0 && !(allPieces & (1ULL << oneAhead))) {
        moves |= (1ULL << oneAhead);

        int twoAhead = square - 16;
        if (row == 6 && !(allPieces & (1ULL << twoAhead))) {
            moves |= (1ULL << twoAhead);
        }
    }

    // Diagonal captures
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

    // Black moves up the board
    int oneAhead = square + 8;
    if (oneAhead < 64 && !(allPieces & (1ULL << oneAhead))) {
        moves |= (1ULL << oneAhead);

        int twoAhead = square + 16;
        if (row == 1 && !(allPieces & (1ULL << twoAhead))) {
            moves |= (1ULL << twoAhead);
        }
    }

    // Diagonal captures
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



