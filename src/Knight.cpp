//
// Created by Maša Hozjan on 21. 05. 25.
//
#include "../include/Knight.h"

Knight::Knight(Color c) : Piece(c) {}

std::string Knight::getSymbol() const {
    return getColor() == Color::WHITE ? "♘" : "♞";
}

bool Knight::isValidMove(Position from, Position to, const std::unique_ptr<Piece> board[8][8]) const {

    int rowDiff = abs(from.row - to.row);
    int colDiff = abs(from.col - to.col);

    if (!((rowDiff == 1 && colDiff == 2) || (rowDiff == 2 && colDiff == 1))) return false;

    if (board[to.row][to.col] && board[to.row][to.col]->getColor() == this->getColor())
        return false;

    return true;
}
