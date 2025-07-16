//
// Created by Maša Hozjan on 21. 05. 25.
//
#include "Pawn.h"

std::string_view Pawn::getSymbol() const {
    return getColor() == Color::WHITE ? "♙" : "♟";
}

bool Pawn::isValidMove(Position from, Position to,
                       const std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& board) const {
    int direction = (getColor() == Color::WHITE) ? -1 : 1; // white moves up, black down
    uint8_t startRow = (getColor() == Color::WHITE) ? 6 : 1;

    // Move forward by 1 square
    if (to.col == from.col && to.row == from.row + direction) {
        return board[to.row][to.col] == nullptr; // only if square is empty
    }

    // Move forward by 2 squares from starting position
    if (to.col == from.col && from.row == startRow && to.row == from.row + 2 * direction) {
        return board[from.row + direction][from.col] == nullptr &&
               board[to.row][to.col] == nullptr;
    }

    // Capture diagonally
    if (abs(to.col - from.col) == 1 && to.row == from.row + direction) {
        return board[to.row][to.col] && board[to.row][to.col]->getColor() != getColor();
    }

    // All other moves are invalid
    return false;
}
