#include "BitboardChess.h"
#include <sstream>

int squareFromAlgebraic(const std::string& pos) {
    int file = pos[0] - 'a';
    int rank = pos[1] - '1';
    return rank * 8 + file;
}

bool isSquareOccupiedByOwnPiece(uint64_t toMask, const BitboardPosition& player) {
    uint64_t myPieces =
        player.pawns | player.knights | player.bishops |
        player.rooks | player.queens | player.king;

    return (toMask & myPieces) != 0;
}

uint64_t getAllPieces(const BitboardPosition& player, const BitboardPosition& opponent) {
    return player.pawns | player.knights | player.bishops |
           player.rooks | player.queens | player.king |
           opponent.pawns | opponent.knights | opponent.bishops |
           opponent.rooks | opponent.queens | opponent.king;
}

bool isGameOver(const GameState& state) {
    if (state.whitePieces.king == 0 || state.blackPieces.king == 0) {
        return true;
    }
    return false;
}

int main() {
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

        // Handle Knight move
        if (player.knights & fromMask) {
            uint64_t moves = generateKnightMoves(fromMask);

            if (moves & toMask) {
                if (isSquareOccupiedByOwnPiece(toMask, player)) {
                    std::cout << "You can't move to a square occupied by your own piece.\n";
                    continue;
                }

                player.knights &= ~fromMask;
                player.knights |= toMask;
                // Optional: capture opponent piece
                opponent.pawns   &= ~toMask;
                opponent.knights &= ~toMask;
                opponent.bishops &= ~toMask;
                opponent.rooks   &= ~toMask;
                opponent.queens  &= ~toMask;
                opponent.king    &= ~toMask;
                moved = true;
            }
        }

        // Handle King move
        else if (player.king & fromMask) {
            uint64_t moves = generateKingMoves(fromMask);

            if (moves & toMask) {
                if (isSquareOccupiedByOwnPiece(toMask, player)) {
                    std::cout << "You can't move to a square occupied by your own piece.\n";
                    continue;
                }

                player.king &= ~fromMask;
                player.king |= toMask;
                opponent.pawns   &= ~toMask;
                opponent.knights &= ~toMask;
                opponent.bishops &= ~toMask;
                opponent.rooks   &= ~toMask;
                opponent.queens  &= ~toMask;
                opponent.king    &= ~toMask;
                moved = true;
            }
        }

        // Handle Rook move
        else if (player.rooks & fromMask) { //Bitboard with just one square set
            uint64_t allPieces = getAllPieces(player, opponent); //Bitboard with all occupied squares for both players

            uint64_t moves = generateRookMoves(from, allPieces);

            if (moves & toMask) { //ToMask - bitboard with destination set
                if (isSquareOccupiedByOwnPiece(toMask, player)) {
                    std::cout << "You can't move to a square occupied by your own piece.\n";
                    continue;
                }

                //We remove the rook from the board and add it to the new position
                player.rooks &= ~fromMask;
                player.rooks |= toMask;

                // If there was opponent’s piece on the target square, this removes it we remove it
                opponent.knights &= ~toMask;
                opponent.bishops &= ~toMask;
                opponent.rooks   &= ~toMask;
                opponent.queens  &= ~toMask;
                opponent.king    &= ~toMask;

                moved = true;
            }
        }

        // Handle Bishop move
        else if (player.bishops & fromMask) {
            uint64_t allPieces = getAllPieces(player, opponent);

            uint64_t moves = generateBishopMoves(from, allPieces);

            if (moves & toMask) {
                if (isSquareOccupiedByOwnPiece(toMask, player)) {
                    std::cout << "You can't move to a square occupied by your own piece.\n";
                    continue;
                }
            }

            player.bishops &= ~fromMask;
            player.bishops |= toMask;
            opponent.knights &= ~toMask;
            opponent.bishops &= ~toMask;
            opponent.rooks   &= ~toMask;
            opponent.queens  &= ~toMask;
            opponent.king    &= ~toMask;

            moved = true;
        }

        // Handle Queen move
        else if (player.queens & fromMask) {
            uint64_t allPieces = getAllPieces(player, opponent);

            uint64_t moves = generateQueenMoves(from, allPieces);

            if (moves & toMask) {
                if (isSquareOccupiedByOwnPiece(toMask, player)) {
                    std::cout << "You can't move to a square occupied by your own piece.\n";
                    continue;
                }
            }

            player.queens &= ~fromMask;
            player.queens |= toMask;
            opponent.pawns   &= ~toMask;
            opponent.knights &= ~toMask;
            opponent.bishops &= ~toMask;
            opponent.rooks   &= ~toMask;
            opponent.queens  &= ~toMask;
            opponent.king    &= ~toMask;

            moved = true;
        }

        // Handle Pawn move
        else if (player.pawns & fromMask) {
            uint64_t allPieces = getAllPieces(player, opponent);

            uint64_t moves;
            if (game.currentTurn == WHITE) {
                moves = generatePawnMovesWhite(from, allPieces, opponent.pawns | opponent.knights | opponent.bishops |
                                                             opponent.rooks | opponent.queens | opponent.king);
            } else {
                moves = generatePawnMovesBlack(from, allPieces, opponent.pawns | opponent.knights | opponent.bishops |
                                                             opponent.rooks | opponent.queens | opponent.king);
            }

            if (moves & toMask) {
                if (isSquareOccupiedByOwnPiece(toMask, player)) {
                    std::cout << "You can't move to a square occupied by your own piece.\n";
                    continue;
                }

                player.pawns &= ~fromMask;
                player.pawns |= toMask;

                opponent.pawns   &= ~toMask;
                opponent.knights &= ~toMask;
                opponent.bishops &= ~toMask;
                opponent.rooks   &= ~toMask;
                opponent.queens  &= ~toMask;
                opponent.king    &= ~toMask;

                moved = true;
            }
        }

        if (isGameOver(game)) {
            std::cout << "Game over!\n The winner is " << (game.currentTurn == WHITE ? "White" : "Black") << ".\n";
            break;
        }

        if (moved) {
            game.currentTurn = (game.currentTurn == WHITE) ? BLACK : WHITE;
        }   else {
            std::cout << "Invalid move.\n";
        }
    }
}


