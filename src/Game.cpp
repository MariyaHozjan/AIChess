//
// Created by Maša Hozjan on 28. 07. 25.
//

// Game.cpp
#include "../include/Game.h"
#include "../include/BoardUtils.h"
#include "../include/MoveGen.h"
#include <iostream>
#include <sstream>

void Game::run() {
    GameState game;
    initializeBoard(game);

    while (true) {
        printBoard(game);
        std::cout << (game.currentTurn == WHITE ? "White" : "Black") << "'s move (e.g. e2 e4, or 'q' to quit): ";

        std::string input;
        std::getline(std::cin, input);

        if (input == "q") break;

        if (input.size() != 5 || input[2] != ' ') {
            std::cout << "Invalid format! Use e.g. e2 e4\n";
            continue;
        }

        std::string fromStr = input.substr(0, 2);
        std::string toStr = input.substr(3, 2);

        int from = squareFromAlgebraic(fromStr);
        int to = squareFromAlgebraic(toStr);

        uint64_t fromMask = 1ULL << from;
        uint64_t toMask = 1ULL << to;

        BitboardPosition& player = (game.currentTurn == WHITE) ? game.whitePieces : game.blackPieces;
        BitboardPosition& opponent = (game.currentTurn == WHITE) ? game.blackPieces : game.whitePieces;

        bool moved = false;

        if (player.knights & fromMask) {
            uint64_t moves = generateKnightMoves(fromMask);
            if ((moves & toMask) && !isSquareOccupiedByOwnPiece(toMask, player)) {
                player.knights &= ~fromMask;
                player.knights |= toMask;
                captureAt(opponent, toMask);
                moved = true;
            }
        }
        else if (player.king & fromMask) {
            uint64_t moves = generateKingMoves(fromMask);
            if ((moves & toMask) && !isSquareOccupiedByOwnPiece(toMask, player)) {
                player.king &= ~fromMask;
                player.king |= toMask;
                captureAt(opponent, toMask);
                moved = true;
            }
        }
        else if (player.rooks & fromMask) {
            uint64_t all = getAllPieces(player, opponent);
            uint64_t moves = generateRookMoves(from, all);
            if ((moves & toMask) && !isSquareOccupiedByOwnPiece(toMask, player)) {
                player.rooks &= ~fromMask;
                player.rooks |= toMask;
                captureAt(opponent, toMask);
                moved = true;
            }
        }
        else if (player.bishops & fromMask) {
            uint64_t all = getAllPieces(player, opponent);
            uint64_t moves = generateBishopMoves(from, all);
            if ((moves & toMask) && !isSquareOccupiedByOwnPiece(toMask, player)) {
                player.bishops &= ~fromMask;
                player.bishops |= toMask;
                captureAt(opponent, toMask);
                moved = true;
            }
        }
        else if (player.queens & fromMask) {
            uint64_t all = getAllPieces(player, opponent);
            uint64_t moves = generateQueenMoves(from, all);
            if ((moves & toMask) && !isSquareOccupiedByOwnPiece(toMask, player)) {
                player.queens &= ~fromMask;
                player.queens |= toMask;
                captureAt(opponent, toMask);
                moved = true;
            }
        }
        else if (player.pawns & fromMask) {
            uint64_t all = getAllPieces(player, opponent);
            uint64_t enemy = opponent.pawns | opponent.knights | opponent.bishops |
                             opponent.rooks | opponent.queens | opponent.king;
            uint64_t moves = (game.currentTurn == WHITE)
                             ? generatePawnMovesWhite(from, all, enemy)
                             : generatePawnMovesBlack(from, all, enemy);
            if ((moves & toMask) && !isSquareOccupiedByOwnPiece(toMask, player)) {
                player.pawns &= ~fromMask;
                player.pawns |= toMask;
                captureAt(opponent, toMask);
                moved = true;
            }
        }

        if (isGameOver(game)) {
            std::cout << "Game over! Winner: " << (game.currentTurn == WHITE ? "White" : "Black") << "\n";
            break;
        }

        if (moved) {
            game.currentTurn = (game.currentTurn == WHITE) ? BLACK : WHITE;
        } else {
            std::cout << "Invalid move.\n";
        }
    }
}

void Game::captureAt(BitboardPosition& opponent, uint64_t toMask) {
    opponent.pawns   &= ~toMask;
    opponent.knights &= ~toMask;
    opponent.bishops &= ~toMask;
    opponent.rooks   &= ~toMask;
    opponent.queens  &= ~toMask;
    opponent.king    &= ~toMask;
}
