//
// Created by Maša Hozjan on 21. 05. 25.
//

#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"
#include <string>

class Rook : public Piece {
public:
    Rook(Color c);
    std::string getSymbol() const override;

    bool isValidMove(Position from, Position to, const std::unique_ptr<Piece> board[8][8]) const override;
};

#endif //ROOK_H
