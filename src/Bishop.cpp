//
// Created by Maša Hozjan on 30. 06. 25.
//

#include "../include/Bishop.h"

Bishop::Bishop(Color c) : Piece(c) {}

std::string Bishop::getSymbol() const {
    return getColor() == Color::WHITE ? "♗" : "♝";
}

bool Bishop::isValidMove(Position from, Position to, const std::unique_ptr<Piece> board[8][8]) const {
    int rowDiff = abs(to.row - from.row);
    int colDiff = abs(to.col - from.col);

    if (rowDiff != colDiff) return false;

    int rowStep = (to.row - from.row) > 0 ? 1 : -1;
    int colStep = (to.col - from.col) > 0 ? 1 : -1;

    int r = from.row + rowStep;
    int c = from.col + colStep;

    while (r != to.row && c != to.col) {
        if (board[r][c]) return false; // Path blocked
        r += rowStep;
        c += colStep;
    }

    if (board[to.row][to.col] && board[to.row][to.col]->getColor() == this->getColor()) {
        return false; // Can't capture your own piece
    }

    return true;
}
