//#import <spdlog/spdlog.h>
#include <iostream>

#include "Bishop.h"
#include "../include/Board.h"

int main() {
    Board board;         // Create a board
    board.setupBoard();

    Color currentTurn = Color::WHITE;
    std::string input;

    while (true) {
        board.printBoard();

        std::cout << (currentTurn == Color::WHITE ? "White" : "Black") << "'s move (e.g. e2 e4, or 'q' to quit): ";
        std::getline(std::cin, input);

        if (input == "q") break;

        if (input.size() != 5 || input[2] != ' ') {
            std::cout << "Invalid input.\n";
            continue;
        }

        int fromCol = input[0] - 'a';
        int fromRow = 8 - (input[1] - '0');
        int toCol = input[3] - 'a';
        int toRow = 8 - (input[4] - '0');

        if (fromRow < 0 || fromRow >= 8 || toRow < 0 || toRow >= 8 || fromCol < 0 || fromCol >= 8 || toCol < 0 || toCol >= 8) {
            std::cout << "Move out of bounds.\n";
            continue;
        }

        Position from {.row = fromRow, .col = fromCol};
        Position to {.row = toRow, .col = toCol};

        Piece* selected = board.getPiece(from);
        if (!selected) {
            std::cout << "No piece at source square.\n";
            continue;
        }

        if (selected->getColor() != currentTurn) {
            std::cout << "It's not your turn.\n";
            continue;
        }

        if (!board.movePiece(from, to)) {
            std::cout << "Invalid move.\n";
            continue;
        }

        Color opponent = (currentTurn == Color::WHITE) ? Color::BLACK : Color::WHITE;
        if (!board.isKingAlive(opponent)) {
            board.printBoard();
            std::cout << (currentTurn == Color::WHITE ? "White" : "Black") << " wins! The king was captured.\n";
            break;
        }


        currentTurn = (currentTurn == Color::WHITE) ? Color::BLACK : Color::WHITE;
        std::cout << "Turn switched. Next: " << (currentTurn == Color::WHITE ? "White" : "Black") << "\n";

    }

    std::cout << "Game ended.\n";
    return 0;
}