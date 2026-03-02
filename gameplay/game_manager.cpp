#include "game_manager.hpp"
#include "difficulty_selector.hpp"
#include "game.hpp"
#include "secret_number_generator.hpp"
#include "solver_game.hpp"
#include "user_interface.hpp"

void GameManager::run() {
  UserInterface::displayWelcome();

  do {
    // Get game mode selection
    UserInterface::displayGameModeSelection();

    if (const GameMode mode{UserInterface::getGameModeChoice()};
        mode == GameMode::manualPlay) {

      const int32_t secret{
          SecretNumberGenerator::getInstance().generateSecretNumber()};

      // Get difficulty level
      const int32_t maxAttempts{DifficultySelector::getMaxAttempts()};

      UserInterface::displayGameStart(maxAttempts);

      Game game{secret, maxAttempts};
      game.start();

      // Check if player ran out of attempts
      if (!game.isGameWon() && game.getAttemptsLeft() == 0) {
        UserInterface::displayGameOver(secret);
      }
    } else {
      // Solver mode
      constexpr int32_t maxAttempts{10};

      UserInterface::displaySolverStrategySelection();
      const int32_t strategyChoice{UserInterface::getSolverStrategyChoice()};
      const auto strategy{
          static_cast<HeuristicSolver::GuessStrategy>(strategyChoice)};

      SolverGame solverGame{maxAttempts, strategy};
      solverGame.start();
    }

  } while (DifficultySelector::playAgain());

  UserInterface::displayGoodbye();
}
