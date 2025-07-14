//
// Created by Maša Hozjan on 21. 05. 25.
//
#include "../include/Board.h"
#include <iostream>
#include "../include/Pawn.h"
#include "../include/Knight.h"
#include "../include/Rook.h"
#include "../include/King.h"
#include "../include/Queen.h"
#include "../include/Bishop.h"

// Constructor: sets all squares to empty
Board::Board() {
    // Always use curly brackets
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            squares[i][j] = nullptr;
        }
    }
}


void Board::setupBoard() {
    for (int i = 0; i < 8; i++) {
        squares[0][0] = std::make_unique<Rook>(Color::BLACK);
        squares[0][1] = std::make_unique<Knight>(Color::BLACK);
        squares[0][2] = std::make_unique<Bishop>(Color::BLACK);
        squares[0][3] = std::make_unique<King>(Color::BLACK);
        squares[0][4] = std::make_unique<Queen>(Color::BLACK);
        squares[0][5] = std::make_unique<Bishop>(Color::BLACK);
        squares[0][6] = std::make_unique<Knight>(Color::BLACK);
        squares[0][7] = std::make_unique<Rook>(Color::BLACK);
        squares[1][i] = std::make_unique<Pawn>(Color::BLACK);
        squares[6][i] = std::make_unique<Pawn>(Color::WHITE);
        squares[7][0] = std::make_unique<Rook>(Color::WHITE);
        squares[7][1] = std::make_unique<Knight>(Color::WHITE);
        squares[7][2] = std::make_unique<Bishop>(Color::WHITE);
        squares[7][3] = std::make_unique<King>(Color::WHITE);
        squares[7][4] = std::make_unique<Queen>(Color::WHITE);
        squares[7][5] = std::make_unique<Bishop>(Color::WHITE);
        squares[7][6] = std::make_unique<Knight>(Color::WHITE);
        squares[7][7] = std::make_unique<Rook>(Color::WHITE);
    }
}

// Print the board to the console
void Board::printBoard() {
    for (int i = 0; i < 8; ++i) { //int i = 0; i < 8; ++i
        std::cout << 8 - i << " "; // Row numbers (8 at top)
        for (int j = 0; j < 8; ++j) {
            if (squares[i][j])
                std::cout << squares[i][j]->getSymbol() << " ";
            else
                std::cout << ". ";
        }
        std::cout << std::endl;
    }
    std::cout << "  a b c d e f g h" << std::endl; // Column letters
}

bool Board::movePiece(Position from, Position to) {
    if (!squares[from.row][from.col]) return false;

    if (!squares[from.row][from.col] -> isValidMove(from, to, squares)) {
        return false;
    }

    squares[to.row][to.col] = std::move(squares[from.row][from.col]);
    squares[from.row][from.col] = nullptr;
    return true;
}

Piece* Board::getPiece(int row, int col) {
    return squares[row][col].get(); // get raw pointer from unique_ptr
}



