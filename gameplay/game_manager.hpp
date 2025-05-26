#pragma once

/**
 * @brief Manages the overall game flow and orchestrates game components
 *
 * Responsibilities to specialized classes: SecretNumberGenerator,
 * UserInterface, DifficultySelector, and InputValidator.
 */
class GameManager {
public:
  /**
   * @brief Run the complete game session with welcome, game loop, and replay
   */
  static void run();
};
