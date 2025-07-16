//
// Created by Maša Hozjan on 30. 06. 25.
//

#include "King.h"

std::string_view King::getSymbol() const {
    return getColor()== Color::WHITE ? "♔" : "♚";
}

bool King::isValidMove(Position from, Position to, const std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& board) const {
    uint8_t rowDiff = abs(from.row - to.row);
    uint8_t colDiff = abs(from.col - to.col);

    if (rowDiff > 1 || colDiff > 1) {
        return false;
    }

    if (board[to.row][to.col] && board[to.row][to.col]->getColor() == this->getColor()) {
        return false;
    }

    return true;
}

//King cant move to a place where it could be attacked - not yet implemented.