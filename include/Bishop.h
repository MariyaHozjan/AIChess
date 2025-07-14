//
// Created by Maša Hozjan on 30. 06. 25.
//

#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"
#include <string>

class Bishop : public Piece {
public:
    Bishop(Color c);
    std::string getSymbol() const override;


    bool isValidMove(Position from, Position to, const std::unique_ptr<Piece> board[8][8]) const override;

};

#endif //BISHOP_H
