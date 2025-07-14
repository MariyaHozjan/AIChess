//
// Created by Maša Hozjan on 21. 05. 25.
//

#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include <memory>

class Board {
private:
    std::unique_ptr<Piece> squares[8][8];

public:
    Board();
    void setupBoard();
    void printBoard();

    bool movePiece(Position from, Position to);

    Piece* getPiece(int row, int col);
};

#endif
