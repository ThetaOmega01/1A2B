#include "game.hpp"
#include "../utils/utils.hpp"
#include "input_validator.hpp"
#include "user_interface.hpp"
#include <array>
#include <cstdint>

Game::Game(const int32_t secret, const int32_t maxAttempts)
    : GameSessionBase{secret, maxAttempts} {}

std::array<int32_t, 2> Game::makeGuess(const int32_t guess) {
  decrementAttempts();

  const auto [aCount, bCount]{utils::calculateAB(guess, getSecret())};

  // Check if game is won
  if (aCount == utils::numberSize) {
    setGameWon();
  }

  return {aCount, bCount};
}

void Game::start() {
  UserInterface::displayInitialGuessPrompt();

  // Get initial guess using InputValidator
  int32_t guess{InputValidator::getValidGuess(
      "Invalid guess. Please enter a four-digit number with no "
      "repeating digits starting with a non-zero digit: ")};

  // Main game loop
  while (!isGameOver()) {
    auto [aCount, bCount]{makeGuess(guess)};

    if (isGameWon()) {
      UserInterface::displayWin(getSecret());
      return;
    }

    UserInterface::displayGuessResult(aCount, bCount);

    if (getAttemptsLeft() > 0) {
      UserInterface::displayAttemptsLeft(getAttemptsLeft());

      // Get next guess using InputValidator
      guess = InputValidator::getValidGuess(
          "Invalid guess. Please enter a four-digit number with no "
          "repeating digits starting with a non-zero digit: ");
    }
  }
}
