//
// Created by Maša Hozjan on 30. 06. 25.
//

#ifndef KING_H
#define KING_H

#include "Piece.h"
#include <string>

class King : public Piece {
public:
    King(Color c);
    std::string getSymbol() const override;

    bool isValidMove(Position from, Position to, const std::unique_ptr<Piece> board[8][8]) const override;
};

#endif //KING_H
