#include <iostream>

int main() {
    const int MAX_MOVES = 9;

    char board[] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
    char mark[] = { 'X', 'O' };

    int move = 0;

    for (int turn = 0; turn < MAX_MOVES; ++turn) {
        // Draw the board.
        std::cout << " " << board[0] << " | " << board[1] << " | " << board[2] << std::endl;
        std::cout << " -----------" << std::endl;
        std::cout << " " << board[3] << " | " << board[4] << " | " << board[5] << std::endl;
        std::cout << " -----------" << std::endl;
        std::cout << " " << board[6] << " | " << board[7] << " | " << board[8] << std::endl;

        // Get next move.
        std::cout << std::endl << "Player " << (turn % 2) + 1 << " select cell (1 - 9)" << std::endl;
        std::cin >> move;

        if (board[move - 1] != ' ') {
            std::cout << "Sorry but that cell is taken! You lose the game." << std::endl;
            turn = MAX_MOVES;
        } else {
            board[move - 1] = mark[turn % 2];
        }
    }

    std::cout << "Game Over." << std::endl;
    return 0;
}
