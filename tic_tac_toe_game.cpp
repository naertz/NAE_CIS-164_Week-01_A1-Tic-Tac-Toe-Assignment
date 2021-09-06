//===========================================
// Name        : tic_tac_toe_game.cpp
// Author      : Noah Allan Ertz (NAE)
// Email       : naertz@dmacc.edu
// Date        : 2021-09-06
// Description : Tic Tac Toe Game for Console
//===========================================

#include <climits>
#include <cstdlib>
#include <errno.h>
#include <iostream>

// Global Variable(s) ====================================================
enum stringToIntegerError { SUCCESS, OVERFLOW, UNDERFLOW, INCONVERTIBLE };
enum inputError { INVALID  =  0,
                  TOO_LOW  = -1,
                  TOO_HIGH = -2 };
// =======================================================================

// Function Declaration(s) =======================================================================================
stringToIntegerError stringToIntegerValidation (int &parsedInteger, const char *stringInputPointer, int base = 0);
int validateInput(std::string stringInput);
int getValidInput(int playerNumber);
// ===============================================================================================================

int main() {
    // Max moves in a tic tac toe game
    const int MAX_MOVES = 9;

    // Board spots
    char board[] = { ' ', ' ', ' ',
                     ' ', ' ', ' ',
                     ' ', ' ', ' ' };
    // Player symbols
    char mark[] = { 'X', 'O' };

    // Selected board spot
    int move = 0;

    // Booleans for potential winner outcomes
    bool isTopRowSame           = false;
    bool isMiddleRowSame        = false;
    bool isBottomRowSame        = false;
    bool isLeftColumnSame       = false;
    bool isMiddleColumnSame     = false;
    bool isRightColumnSame      = false;
    bool isDownwardDiagonalSame = false;
    bool isUpwardDiagonalSame   = false;

    // Boolean for winner outcome
    bool doesPlayerWin          = false;

    for (int turn = 0; turn < MAX_MOVES; ++turn) {
        // Get current player number.
        int playerNumber = turn % 2;

        // Draw the board.
        std::cout << " " << board[0] << " | " << board[1] << " | " << board[2] << std::endl;
        std::cout << " -----------" << std::endl;
        std::cout << " " << board[3] << " | " << board[4] << " | " << board[5] << std::endl;
        std::cout << " -----------" << std::endl;
        std::cout << " " << board[6] << " | " << board[7] << " | " << board[8] << std::endl;

        std::cout << std::endl;

        /** Change 1: Improved input validation.
         * // Get next move.
         * std::cout << std::endl << "Player " << (turn % 2) + 1 << " select cell (1 - 9)" << std::endl;
         * std::cin >> move;
         */

        // Get validated input and assign parsed integer to move.
        move = getValidInput(playerNumber);

        std::cout << std::endl;

        // Board array index from move
        int moveIndex = move - 1;

        // Determine if spot is taken.
        if (board[moveIndex] != ' ') { // Player loses if spot on board is taken.
            std::cout << "Sorry but that cell is taken! You lose the game." << std::endl;
            turn = MAX_MOVES;
        } else { // Spot is assigned with mark.
            board[moveIndex] = mark[playerNumber];
        }

        /* Change 2: Added ability for game to determine a winner or tie */

        // Update booleans based on selected spot.
        if (moveIndex == 0) {
            isTopRowSame           = board[0] == board[1] && board[0] == board[2];
            isLeftColumnSame       = board[0] == board[3] && board[0] == board[6];
            isDownwardDiagonalSame = board[0] == board[4] && board[0] == board[8];

            if (isTopRowSame || isLeftColumnSame || isDownwardDiagonalSame) {
                doesPlayerWin = true;
            }
        } else if (moveIndex == 1) {
            isTopRowSame           = board[0] == board[1] && board[0] == board[2];
            isMiddleColumnSame     = board[1] == board[4] && board[1] == board[7];

            if (isTopRowSame || isMiddleColumnSame) {
                doesPlayerWin = true;
            }
        } else if (moveIndex == 2) {
            isTopRowSame           = board[0] == board[1] && board[0] == board[2];
            isRightColumnSame      = board[2] == board[5] && board[2] == board[8];
            isUpwardDiagonalSame   = board[6] == board[4] && board[6] == board[2];

            if (isTopRowSame || isRightColumnSame || isUpwardDiagonalSame) {
                doesPlayerWin = true;
            }
        } else if (moveIndex == 3) {
            isMiddleRowSame        = board[3] == board[4] && board[3] == board[5];
            isLeftColumnSame       = board[0] == board[3] && board[0] == board[6];

            if (isMiddleRowSame || isLeftColumnSame) {
                doesPlayerWin = true;
            }
        } else if (moveIndex == 4) {
            isMiddleRowSame        = board[3] == board[4] && board[3] == board[5];
            isMiddleColumnSame     = board[1] == board[4] && board[1] == board[7];
            isDownwardDiagonalSame = board[0] == board[4] && board[0] == board[8];
            isUpwardDiagonalSame   = board[6] == board[4] && board[6] == board[2];

            if (isMiddleRowSame || isMiddleColumnSame || isDownwardDiagonalSame || isUpwardDiagonalSame) {
                doesPlayerWin = true;
            }
        } else if (moveIndex == 5) {
            isMiddleRowSame        = board[3] == board[4] && board[3] == board[5];
            isRightColumnSame      = board[2] == board[5] && board[2] == board[8];

            if (isMiddleRowSame || isRightColumnSame) {
                doesPlayerWin = true;
            }
        } else if (moveIndex == 6) {
            isBottomRowSame        = board[6] == board[7] && board[6] == board[8];
            isLeftColumnSame       = board[0] == board[3] && board[0] == board[6];
            isUpwardDiagonalSame   = board[6] == board[4] && board[6] == board[2];

            if (isBottomRowSame || isLeftColumnSame || isUpwardDiagonalSame) {
                doesPlayerWin = true;
            }
        } else if (moveIndex == 7) {
            isBottomRowSame        = board[6] == board[7] && board[6] == board[8];
            isMiddleColumnSame     = board[1] == board[4] && board[1] == board[7];

            if (isBottomRowSame || isMiddleColumnSame) {
                doesPlayerWin = true;
            }
        } else if (moveIndex == 8) {
            isBottomRowSame        = board[6] == board[7] && board[6] == board[8];
            isRightColumnSame      = board[2] == board[5] && board[2] == board[8];
            isDownwardDiagonalSame = board[0] == board[4] && board[0] == board[8];

            if (isBottomRowSame || isRightColumnSame || isDownwardDiagonalSame) {
                doesPlayerWin = true;
            }
        }

        // Determine if game is won.
        if (doesPlayerWin) { // Winner exists
            std::cout << "Player " << playerNumber << " wins!" << std::endl;
            turn = MAX_MOVES;
        } else if (turn == MAX_MOVES - 1) { // Tie
            std::cout << "Tie!" << std::endl;
        }
    }

    // End game.
    std::cout << "Game Over." << std::endl;
    return 0;
}

// Main Function(s) ========================================================================================================================================================================================================================================================
/**
 * @brief stringToIntegerValidation parses an integer from a string and returns the error result.
 * @param parsedInteger = Integer to receive parsed result passed by reference
 * @param stringInputPointer = Passed pointer to null-terminated byte string constant to be interpreted
 * @param base = Integer to determine base of integer passed by value (default to 0 for auto-detected base)
 * @return = stringToIntegerError enum representing the validation result from parsing string to integer
 */

stringToIntegerError stringToIntegerValidation (int &parsedInteger, const char *stringInputPointer, int base) {
    // Error result to return
    stringToIntegerError errorResult;
    // Pointer to pointer of character past the last character interpreted
    char *end;
    // Long to parse from string and to be cast to integer after validation
    long longToParse;
    // A preprocesor macro initialized to 0 for upcoming validation. In this case, it is used to determine if the long receives a value that is out of range.
    errno = 0;
    // Interpret integer value from byte string pointed to by the stringInputPointer.
    longToParse = std::strtol(stringInputPointer, &end, base);

    // Determine if errno is out of range AND long returns LONG_MAX (the maximum value of a long) OR long exceeds INT_MAX (the maximum value of an integer). Upon error, long returns 0.
    if ((errno == ERANGE && longToParse == LONG_MAX) || longToParse > INT_MAX) {
        errorResult = OVERFLOW;
    } else if ((errno == ERANGE && longToParse == LONG_MIN) || longToParse < INT_MIN) { // Determine if errno is out of range AND long returns LONG_MIN (the minimum value of a long) OR long exceeds INT_MIN (the minimum value of an integer). Upon error, long returns 0.
        errorResult = UNDERFLOW;
    } else if (*stringInputPointer == '\0' || *end != '\0') { // Determine if byte string or character pointer of last pointer returns null. Prevents input such as "5g".
        errorResult = INCONVERTIBLE;
    } else { // Input is a valid integer.
        errorResult = SUCCESS;
        // Cast valid long to integer.
        parsedInteger = static_cast<int>(longToParse);
    }

    // Return error result.
    return errorResult;
}

/**
 * @brief validateInput takes a given string and attempts to parse and return an integer. Checks if the integer is between 1 and 9. Upon error, integer is 0. Upon low input, integer is -1. Upon high input, integer is -2.
 * @param stringInput = Input string to be parsed
 * @return = an integer parsed from the input string
 */

int validateInput(std::string stringInput) {
    // Convert string to c-string and then convert to constant byte string to pass to validation function.
    const char * stringInputPointer = stringInput.c_str();

    // Declare integer to pass by reference and to store parsed result from input string.
    int integerFromString = 0;

    // Call validation function and store error result to enum variable.
    stringToIntegerError errorResult = stringToIntegerValidation(integerFromString, stringInputPointer);

    // Determine if parsed integer is invalid.
    if (errorResult != SUCCESS) {
        integerFromString = INVALID;
    } else if (integerFromString < 1) {
        integerFromString = TOO_LOW;
    } else if (integerFromString > 9) {
        integerFromString = TOO_HIGH;
    }

    // Returns parsed integer.
    return integerFromString;
}

/**
 * @brief getValidInput gets input as a string, validates the parsed integer until 1-9 is selected, and returns an integer between 1-9.
 * @param playerNumber = player number to use to refer to the current player
 * @return = a parsed integer between 1-9
 */

int getValidInput(int playerNumber) {
    // Input string to parse to integer
    std::string stringInput;
    // Integer parsed from input string
    int integerFromString;

    // Initialize valid input boolean for do-while loop.
    bool isValidInput = false;

    // Validate parsed integer until integer is valid.
    do {
        // Prompt user and get input string.
        std::cout << "Player " << playerNumber << " select cell (1 - 9): " << std::flush;
        std::getline(std::cin, stringInput);

        // Parse integer from input string.
        integerFromString = validateInput(stringInput);

        // Determine if parsed integer is valid.
        if (integerFromString == INVALID || stringInput.length() > 1) { // Second condition prevents input such as " 6".
            std::cout << "Invalid input. Please enter an integer." << std::endl;
        } else if (integerFromString == TOO_LOW) {
            std::cout << "Input is too low. Please enter an integer greater than or equal to 1." << std::endl;
        } else if (integerFromString == TOO_HIGH) { // Not attainable due to second condition in first condition above
            std::cout << "Input is too high. Please enter an integer less than or equal to 9." << std::endl;
        } else {
            isValidInput = true;
        }
    } while (!isValidInput);

    // Return valid integer.
    return integerFromString;
}
// =========================================================================================================================================================================================================================================================================

// Test(s) =============================================================
// 00
// ---------------------------------------------------------------------
// Console Output:
//    |   |
//  -----------
//    |   |
//  -----------
//    |   |
//
// Player 0 select cell (1 - 9):
// ---------------------------------------------------------------------
// Input:
// "1"
// ---------------------------------------------------------------------
// Console Output:
// X |   |
// -----------
//   |   |
// -----------
//   |   |
//
// Player 1 select cell (1 - 9):
// ---------------------------------------------------------------------
// Actual Output == Expected Output
// =====================================================================
// 01
// ---------------------------------------------------------------------
// Console Output:
// Player 1 select cell (1 - 9):
// ---------------------------------------------------------------------
// Input:
// " 2"
// ---------------------------------------------------------------------
// Console Output:
// Invalid input. Please enter an integer.
// Player 1 select cell (1 - 9):
// ---------------------------------------------------------------------
// Actual Output == Expected Output
// =====================================================================
// 02
// ---------------------------------------------------------------------
// Console Output:
// Player 1 select cell (1 - 9):
// ---------------------------------------------------------------------
// Input:
// "2 "
// ---------------------------------------------------------------------
// Console Output:
// Invalid input. Please enter an integer.
// Player 1 select cell (1 - 9):
// ---------------------------------------------------------------------
// Actual Output == Expected Output
// =====================================================================
// 03
// ---------------------------------------------------------------------
// Console Output:
// Player 1 select cell (1 - 9):
// ---------------------------------------------------------------------
// Input:
// "2g"
// ---------------------------------------------------------------------
// Console Output:
// Invalid input. Please enter an integer.
// Player 1 select cell (1 - 9):
// ---------------------------------------------------------------------
// Actual Output == Expected Output
// =====================================================================
// 04
// ---------------------------------------------------------------------
// Console Output:
// Player 1 select cell (1 - 9):
// ---------------------------------------------------------------------
// Input:
// "g2"
// ---------------------------------------------------------------------
// Console Output:
// Invalid input. Please enter an integer.
// Player 1 select cell (1 - 9):
// ---------------------------------------------------------------------
// Actual Output == Expected Output
// =====================================================================
// 05
// ---------------------------------------------------------------------
// Console Output:
// Player 1 select cell (1 - 9):
// ---------------------------------------------------------------------
// Input:
// "10"
// ---------------------------------------------------------------------
// Console Output:
// Invalid input. Please enter an integer.
// Player 1 select cell (1 - 9):
// ---------------------------------------------------------------------
// Actual Output == Expected Output
// =====================================================================
// 06
// ---------------------------------------------------------------------
// Console Output:
// Player 1 select cell (1 - 9):
// ---------------------------------------------------------------------
// Input:
// "0"
// ---------------------------------------------------------------------
// Console Output:
// Input is too low. Please enter an integer greater than or equal to 1.
// Player 1 select cell (1 - 9):
// ---------------------------------------------------------------------
// Actual Output == Expected Output
// =====================================================================
// 07
// ---------------------------------------------------------------------
// Console Output:
// X |   |
// -----------
//   |   |
// -----------
//   |   |
//
// Player 1 select cell (1 - 9):
// ---------------------------------------------------------------------
// Input:
// "1"
// ---------------------------------------------------------------------
// Console Output:
// Sorry but that cell is taken! You lose the game.
// Game Over.
// ---------------------------------------------------------------------
// Actual Output == Expected Output
// =====================================================================
// 08
// ---------------------------------------------------------------------
// Console Output:
// X | O | X
// -----------
// O | O | X
// -----------
//   | X | O
//
// Player 0 select cell (1 - 9):
// ---------------------------------------------------------------------
// Input:
// "7"
// ---------------------------------------------------------------------
// Console Output:
// Tie!
// Game Over.
// ---------------------------------------------------------------------
// Actual Output == Expected Output
// =====================================================================
// 09
// ---------------------------------------------------------------------
// Console Output:
// X | X | O
// -----------
// O | X |
// -----------
//   |   | O
//
// Player 0 select cell (1 - 9):
// ---------------------------------------------------------------------
// Input:
// "8"
// ---------------------------------------------------------------------
// Console Output:
// Player 0 wins!
// Game Over.
// ---------------------------------------------------------------------
// Actual Output == Expected Output
// =====================================================================
// 10
// ---------------------------------------------------------------------
// Console Output:
// O |   |
// -----------
// O | X | X
// -----------
//   | X |
//
// Player 1 select cell (1 - 9):
// ---------------------------------------------------------------------
// Input:
// "7"
// ---------------------------------------------------------------------
// Console Output:
// Player 1 wins!
// Game Over.
// ---------------------------------------------------------------------
// Actual Output == Expected Output
// =====================================================================
