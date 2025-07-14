//
// Created by Maša Hozjan on 21. 05. 25.
//

#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"
#include <string>

class Pawn : public Piece {
public:
    Pawn(Color c);
    std::string getSymbol() const override;

    bool isValidMove(Position from, Position to, const std::unique_ptr<Piece> board[8][8]) const override;
};
#endif //PAWN_H
