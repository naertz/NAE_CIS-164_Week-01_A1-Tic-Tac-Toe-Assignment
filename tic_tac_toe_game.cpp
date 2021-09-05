#include <iostream>

using namespace std;

int main() {
    char mark[] = { 'X', 'O' };
    char board[] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
    int move = 0;
    const int MAXMOVES = 9;

    for (int turn = 0; turn < MAXMOVES; ++turn) {
        // draw the board
        cout << " " << board[0] << " | " << board[1] << " | " << board[2] << endl;
        cout << " -----------" << endl;
        cout << " " << board[3] << " | " << board[4] << " | " << board[5] << endl;
        cout << " -----------" << endl;
        cout << " " << board[6] << " | " << board[7] << " | " << board[8] << endl;

        // get next move
        cout << endl << "Player " << (turn % 2) + 1 << " select cell (1 - 9)" << endl;
        cin >> move;

        if (board[move - 1] != ' ') {
            std::cout << "Sorry but that cell is taken! You lose the game." << endl;
            turn = MAXMOVES;
        } else {
            board[move - 1] = mark[turn % 2];
        }
    }

    cout << "Game Over." << endl;
    return 0;
}
