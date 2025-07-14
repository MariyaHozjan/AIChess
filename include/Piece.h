//
// Created by Maša Hozjan on 21. 05. 25.
//

#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <memory>

#include "Position.h"

enum class Color { WHITE, BLACK };

class Piece {
public:
    explicit Piece(Color c);

    virtual ~Piece() = default;

    virtual std::string getSymbol() const = 0;

    virtual bool isValidMove(Position from, Position to,
        const std::unique_ptr<Piece> board[8][8]) const = 0;

    Color getColor() const;
private:
    Color m_color;
};
#endif //PIECE_H

/*
This is an abstract class, which means it cant be instantiated - you cant create an object from it directly.
Its used as base class, providing a blueprint for other classes.
A class becomes abstract when it has at least one pure virtual function -> virtual .... = 0. Its a placeholder function
meaning: "every subclass must provide its own version of this function".

When a function is marked virtual, C++ uses dynamic dispatch to decide at runtime which version of the function to call.
So that when you have a base class pointer (like Piece*), calling getSymbol() will run the correct function from the
subclass (like Pawn), not the base class version.
 */
