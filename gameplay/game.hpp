/**
 * @file game.hpp
 * @brief Core game logic
 */

#pragma once

#include "../interface/interface.hpp"
#include <array>

/**
 * @class Game
 * @brief Main game class
 * This class inherits from GameSessionBase.
 */
class Game final : public GameSessionBase {
public:
  /**
   * @brief Constructs a new Game instance
   * @param secret The secret number to be guessed
   * @param maxAttempts Maximum number of attempts allowed
   */
  Game(int32_t secret, int32_t maxAttempts);

  /**
   * @brief Processes a player's guess and returns the score
   * @param guess The player's guess as an integer
   * @return Array containing [aCount, bCount], number of A's and B's.
   */
  std::array<int32_t, 2> makeGuess(int32_t guess) override;

  /**
   * @brief Starts the game loop
   */
  void start() override;
};
