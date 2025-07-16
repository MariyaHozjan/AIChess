//
// Created by Maša Hozjan on 21. 05. 25.
//
#include "Piece.h"

Piece::Piece(Color c) : m_color(c) {}

Color Piece::getColor() const {
    return m_color;
}
