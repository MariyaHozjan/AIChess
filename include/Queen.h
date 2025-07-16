//
// Created by Maša Hozjan on 30. 06. 25.
//

#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"
#include <string>

class Queen : public Piece {
public:
    using Piece::Piece;

    std::string_view getSymbol() const override;

    bool isValidMove(Position from, Position to, const std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& board) const override;
};

#endif //QUEEN_H
