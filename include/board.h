//
// Created by Maša Hozjan on 21. 05. 25.
//

#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include <memory>
#include <array>

class Board {
private:
    std::array<std::array<std::unique_ptr<Piece>, 8>, 8> squares;

public:
    Board();
    void setupBoard();
    void printBoard() const;

    bool movePiece(Position from, Position to);

    Piece* getPiece(Position from);

    bool isKingAlive(Color color) const;
};

#endif
