//
// Created by Maša Hozjan on 21. 05. 25.
//

#include "Rook.h"

std::string_view Rook::getSymbol() const {
    return getColor() == Color::WHITE ? "♖" : "♜";
}

bool Rook::isValidMove(Position from, Position to,
                         const std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& board) const {
    if (from.row != to.row && from.col && to.col) {
        return false;
    }

    int rowStep =  (from.row < to.row) ? 1 : (from.row > to.row) ? -1 : 0;
    int colStep = (from.col < to.col) ? 1 : (from.col > to.col) ? -1 : 0;

    int r = from.row + rowStep;
    int c = from.col + colStep;

    while (r != to.row || c != to.col) {
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

