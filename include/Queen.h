//
// Created by Maša Hozjan on 30. 06. 25.
//

#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"
#include <string>

class Queen : public Piece {
public:
    Queen(Color c);
    std::string getSymbol() const override;

    bool isValidMove(Position from, Position to, const std::unique_ptr<Piece> board[8][8]) const override;
};

#endif //QUEEN_H
