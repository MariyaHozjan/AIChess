//
// Created by Maša Hozjan on 21. 05. 25.
//

#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"
#include <string>

class Rook : public Piece {
public:
    using Piece::Piece;

    std::string_view getSymbol() const override;

    bool isValidMove(Position from, Position to, const std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& board) const override;
};

#endif //ROOK_H
