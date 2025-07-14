//
// Created by Maša Hozjan on 30. 06. 25.
//

#include "../include/King.h"

King::King(Color c) : Piece(c) {}

std::string King::getSymbol() const {
    return getColor()== Color::WHITE ? "♔" : "♚";
}

bool King::isValidMove(Position from, Position to, const std::unique_ptr<Piece> board[8][8]) const {
    int rowDiff = abs(from.row - to.row);
    int colDiff = abs(from.col - to.col);

    if (rowDiff > 1 || colDiff > 1) return false;

    if (board[to.row][to.col] && board[to.row][to.col]->getColor() == this->getColor())
        return false;

    return true;
}

//King cant move to a place where it could be attacked - not yet implemented.