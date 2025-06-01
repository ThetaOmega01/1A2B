#include "user_interface.hpp"
#include "input_validator.hpp"
#include <format>
#include <iostream>

void UserInterface::displayWelcome() {
  const std::string message{
      std::format("═════════════════════════════════\n"
                  "    Welcome to 1A2B Game!\n"
                  "═════════════════════════════════\n\n"
                  "Rules:\n"
                  "- Guess a 4-digit number with unique digits\n"
                  "- The first digit cannot be 0\n"
                  "- 'A' means correct digit in correct position\n"
                  "- 'B' means correct digit in wrong position\n"
                  "- Example: Secret=1234, Guess=1324 → 2A2B\n\n")};
  std::cout << message;
}

void UserInterface::displayGameStart(const int32_t maxAttempts) {
  std::cout << "\nGame started! You have " << maxAttempts << " attempts.\n\n";
}

void UserInterface::displayGameOver(const int32_t secretNumber) {
  std::cout << "\nGame Over! You've run out of attempts.\n";
  std::cout << "The secret number was: " << secretNumber << "\n";
}

void UserInterface::displayWin(const int32_t secretNumber) {
  std::cout << "Congratulations! You've guessed the number: " << secretNumber
            << "\n";
}

void UserInterface::displayGuessResult(const int32_t As, const int32_t Bs) {
  std::cout << As << "A" << Bs << "B\n";
}

void UserInterface::displayAttemptsLeft(const int32_t attemptsLeft) {
  std::cout << "Attempts left: " << attemptsLeft << ". Enter your next guess: ";
}

void UserInterface::displayGoodbye() {
  std::cout << "\nThanks for playing 1A2B! Goodbye!\n";
}

void UserInterface::displayInitialGuessPrompt() {
  std::cout << "Enter a four-digit number with no repeating digits and start "
               "with a non-zero digit to guess: ";
}

void UserInterface::displayNextGuessPrompt() {
  std::cout << "Enter your next guess: ";
}

void UserInterface::displayGameModeSelection() {
  const std::string message{std::format("Choose game mode:\n"
                                        "1. Play manually\n"
                                        "2. Use solver\n"
                                        "Enter your choice (1-2): ")};
  std::cout << message;
}

GameMode UserInterface::getGameModeChoice() {
  const int32_t choice{InputValidator::getIntegerInRange(
      1, 2, "Invalid choice. Please enter 1 or 2: ")};
  return static_cast<GameMode>(choice - 1); // Convert 1-2 to 0-1
}

void UserInterface::displaySolverStrategySelection() {
  const std::string message{
      std::format("Choose solver strategy:\n"
                  "1. Entropy-based (Information Theory)\n"
                  "2. Minimax (Worst-case Optimization)\n"
                  "3. Frequency-based (Statistical)\n"
                  "4. Hybrid (Combines all strategies)\n"
                  "Enter your choice (1-4): ")};
  std::cout << message;
}

int32_t UserInterface::getSolverStrategyChoice() {
  return InputValidator::getIntegerInRange(
             1, 4, "Invalid choice. Please enter a number (1-4): ") -
         1; // Convert 1-4 to 0-3
}

void UserInterface::displaySolverStart(std::string_view strategy,
                                       int32_t maxAttempts) {
  std::cout << std::format("\nSolver started.\n");
  std::cout << std::format("Strategy: {}\n", strategy);
  std::cout << std::format("Maximum attempts: {}\n", maxAttempts);
  std::cout << "\nThink of a 4-digit secret number with unique digits (first "
               "digit cannot be 0).\n";
  std::cout << "The solver will make guesses and you provide feedback in the "
               "format 'XaYb' (e.g., '2A1B' or '2a1b').\n";
  std::cout << "Type 'reset' at any time to start over.\n\n";
}

void UserInterface::displaySolverGuess(int32_t guessNumber, int32_t guess,
                                       int32_t attemptsLeft) {
  std::cout << std::format("Guess #{}: {} (Attempts left: {})\n", guessNumber,
                           guess, attemptsLeft);
}

std::string UserInterface::getFeedbackInput() {
  std::cout << "Enter feedback (e.g., '2A1B', '0a4b') or 'reset': ";
  std::string input;

  // Clear any leftover input from previous operations
  if (std::cin.peek() == '\n') {
    std::cin.ignore();
  }

  std::getline(std::cin, input);

  // Handle potential stream issues
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    return "";
  }

  return input;
}

void UserInterface::displayInvalidFeedback() {
  std::cout << "Invalid feedback format. Please use format like '2A1B', "
               "'0a4b', etc.\n";
  std::cout << "Valid examples: 0A0B, 1A2B, 4A0B, 0a3b, 2A1b\n";
}

void UserInterface::displayRemainingPossibilities(size_t count) {
  if (count > 0) {
    std::cout << std::format("Remaining possibilities: {}\n\n", count);
  } else {
    std::cout << "No remaining possibilities - there may be an error in the "
                 "feedback.\n\n";
  }
}

void UserInterface::displaySolverSuccess(int32_t secretNumber,
                                         int32_t totalGuesses) {
  std::cout << std::format("\nSolution found.\n");
  std::cout << std::format("Your secret number {} was solved in {} guess{}!\n",
                           secretNumber, totalGuesses,
                           totalGuesses == 1 ? "" : "es");
}

void UserInterface::displaySolverFailure(int32_t totalGuesses) {
  std::cout << std::format("\nSolver failed\n");
  std::cout << std::format(
      "Could not solve your secret number in {} attempts.\n", totalGuesses);
  std::cout
      << "This might happen if there were errors in the feedback provided.\n";
}

void UserInterface::displaySolverReset() {
  std::cout << "\nSolver reset. Starting over...\n\n";
}

void UserInterface::displaySolverNoMoreGuesses(int32_t totalGuesses) {
  std::cout << std::format(
      "\nSolver has no more valid guesses after {} attempts.\n", totalGuesses);
  std::cout << "This usually means there were inconsistencies in the feedback "
               "provided.\n";
}
