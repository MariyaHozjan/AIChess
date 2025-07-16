//
// Created by Maša Hozjan on 21. 05. 25.
//
#include "Knight.h"

std::string_view Knight::getSymbol() const {
    return getColor() == Color::WHITE ? "♘" : "♞";
}

bool Knight::isValidMove(Position from, Position to, const std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& board) const {

    uint8_t rowDiff = abs(from.row - to.row);
    uint8_t colDiff = abs(from.col - to.col);

    if (!((rowDiff == 1 && colDiff == 2) || (rowDiff == 2 && colDiff == 1))) {
        return false;
    }

    if (board[to.row][to.col] && board[to.row][to.col]->getColor() == this->getColor()) {
        return false;
    }

    return true;
}
