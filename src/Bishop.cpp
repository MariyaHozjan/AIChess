//
// Created by Maša Hozjan on 30. 06. 25.
//

#include "Bishop.h"

std::string_view Bishop::getSymbol() const {
    return getColor() == Color::WHITE ? "♗" : "♝";
}

bool Bishop::isValidMove(Position from, Position to, const std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& board) const {
    uint8_t rowDiff = abs(to.row - from.row);
    uint8_t colDiff = abs(to.col - from.col);

    if (rowDiff != colDiff) {
        return false;
    }

    int rowStep = (to.row - from.row) > 0 ? 1 : -1;
    int colStep = (to.col - from.col) > 0 ? 1 : -1;

    int r = from.row + rowStep;
    int c = from.col + colStep;

    while (r != to.row && c != to.col) {
        if (board[r][c]) {
            return false;
        }// Path blocked
        r += rowStep;
        c += colStep;
    }

    if (board[to.row][to.col] && board[to.row][to.col]->getColor() == this->getColor()) {
        return false; // Can't capture your own piece
    }

    return true;
}
