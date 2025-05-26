#include "user_interface.hpp"
#include <format>
#include <iostream>

void UserInterface::displayWelcome() {
  const std::string message{
      std::format("=================================\n"
                  "    Welcome to 1A2B Game!\n"
                  "=================================\n\n"
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
