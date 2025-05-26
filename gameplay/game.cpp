#include "game.hpp"
#include "../utils/utils.hpp"
#include "input_validator.hpp"
#include "user_interface.hpp"
#include <algorithm>
#include <array>
#include <cstdint>

Game::Game(const int32_t secret, const int32_t maxAttempts)
    : GameSessionBase{secret, maxAttempts} {
  m_secretDigits = utils::getDigits(getSecret());
}

std::array<int32_t, 2> Game::makeGuess(const int32_t guess) {
  decrementAttempts();

  int32_t As{0};
  int32_t Bs{0};

  std::array<int32_t, 10> secretCount{};
  std::array<int32_t, 10> guessCount{};

  const std::array<int32_t, utils::numberSize> guessDigits =
      utils::getDigits(guess);

  for (int32_t digitIndex{0}; digitIndex < utils::numberSize; ++digitIndex) {

    if (m_secretDigits.at(digitIndex) == guessDigits.at(digitIndex)) {
      ++As;
    } else {
      ++secretCount.at(m_secretDigits.at(digitIndex));
      ++guessCount.at(guessDigits.at(digitIndex));
    }
  }

  // Check if game is won
  if (As == utils::numberSize) {
    setGameWon();
  }

  for (int32_t countIndex{0}; countIndex < 10; ++countIndex) {
    Bs += std::min(secretCount.at(countIndex), guessCount.at(countIndex));
  }

  return {As, Bs};
}

void Game::start() {
  UserInterface::displayInitialGuessPrompt();

  // Get initial guess using InputValidator
  int32_t guess{InputValidator::getValidGuess(
      "Invalid guess. Please enter a four-digit number with no "
      "repeating digits and starting with a non-zero digit: ")};

  // Main game loop
  while (!isGameOver()) {
    auto [As, Bs]{makeGuess(guess)};

    if (isGameWon()) {
      UserInterface::displayWin(getSecret());
      return;
    }

    UserInterface::displayGuessResult(As, Bs);

    if (getAttemptsLeft() > 0) {
      UserInterface::displayAttemptsLeft(getAttemptsLeft());

      // Get next guess using InputValidator
      guess = InputValidator::getValidGuess(
          "Invalid guess. Please enter a four-digit number with no "
          "repeating digits and starting with a non-zero digit: ");
    }
  }
}
