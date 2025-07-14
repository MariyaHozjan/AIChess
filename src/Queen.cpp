//
// Created by Maša Hozjan on 30. 06. 25.
//

#include "Queen.h"

Queen::Queen(Color c) : Piece(c) {}

std::string Queen::getSymbol() const {
    return getColor() == Color::WHITE ? "♕" : "♛";
}

bool Queen::isValidMove(Position from, Position to, const std::unique_ptr<Piece> board[8][8]) const {
    int rowDiff = abs(from.row - to.row);
    int colDiff = abs(from.col - to.col);

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
