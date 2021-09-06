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
    const int MAX_MOVES = 9;

    char board[] = { ' ', ' ', ' ',
                     ' ', ' ', ' ',
                     ' ', ' ', ' ' };
    char mark[] = { 'X', 'O' };

    int move = 0;

    for (int turn = 0; turn < MAX_MOVES; ++turn) {
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
        move = getValidInput(turn % 2);

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
    } else if (*stringInputPointer == '\0' || *end != '\0') { // Determine if byte string or character pointer of last pointer returns null. Prevents output such as "5g".
        errorResult = INCONVERTIBLE;
    } else { // Output is a valid integer.
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
        if (integerFromString == INVALID) {
            std::cout << "Invalid input. Please enter an integer." << std::endl;
        } else if (integerFromString == TOO_LOW) {
            std::cout << "Input is too low. Please enter an integer greater than or equal to 1." << std::endl;
        } else if (integerFromString == TOO_HIGH) {
            std::cout << "Input is too high. Please enter an integer less than or equal to 9." << std::endl;
        } else {
            isValidInput = true;
        }
    } while (!isValidInput);

    // Return valid integer.
    return integerFromString;
}
// =========================================================================================================================================================================================================================================================================
