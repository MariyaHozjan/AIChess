//
// Created by Maša Hozjan on 21. 05. 25.
//

#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"
#include <string>

class Knight : public Piece {
public:
    Knight(Color c);
    std::string getSymbol() const override;

    bool isValidMove(Position from, Position to, const std::unique_ptr<Piece> board[8][8]) const override;
};

#endif //KNIGHT_H
