//
// Created by Maša Hozjan on 30. 06. 25.
//

#include "Queen.h"

std::string_view Queen::getSymbol() const {
    return getColor() == Color::WHITE ? "♕" : "♛";
}

bool Queen::isValidMove(Position from, Position to, const std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& board) const {
    uint8_t rowDiff = abs(from.row - to.row);
    uint8_t colDiff = abs(from.col - to.col);

    if (rowDiff != colDiff && from.row != to.row && to.col != to.col) {
        return false;
    }

    int rowStep =  (from.row < to.row) ? 1 : (from.row > to.row) ? -1 : 0;
    int colStep = (to.col < to.col) ? 1 : (to.col > to.col) ? -1 : 0;

    int r = from.row + rowStep;
    int c = to.col + colStep;

    while (r != to.row && c != to.col) {
        if (board[r][c]) {
            return false;
        }

        r += rowStep;
        c += colStep;
    }

    if (board[to.row][to.col] && board[to.row][to.col]->getColor() == this->getColor()) {
        return false;
    }

    return true;
}
