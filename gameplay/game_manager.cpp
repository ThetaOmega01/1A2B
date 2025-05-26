#include "game_manager.hpp"
#include "difficulty_selector.hpp"
#include "game.hpp"
#include "secret_number_generator.hpp"
#include "user_interface.hpp"

void GameManager::run() {
  UserInterface::displayWelcome();

  do {
    // Generate secret number using the singleton generator
    const int32_t secret{
        SecretNumberGenerator::getInstance().generateSecretNumber()};

    // Get difficulty level using the difficulty selector
    const int32_t maxAttempts{DifficultySelector::getMaxAttempts()};

    UserInterface::displayGameStart(maxAttempts);

    // Create and start game
    Game game{secret, maxAttempts};
    game.start();

    // Check if player ran out of attempts
    if (!game.isGameWon() && game.getAttemptsLeft() == 0) {
      UserInterface::displayGameOver(secret);
    }

  } while (DifficultySelector::playAgain());

  UserInterface::displayGoodbye();
}
