/**
 * @file user_interface.hpp
 * @brief Handles all user interface operations for the 1A2B game
 */

#pragma once

#include <cstdint>

/**
 * @class UserInterface
 * @brief Manages all display and messaging operations for the 1A2B game
 *
 * This class centralizes all user interface operations including welcome
 * messages, game status displays, and result presentations. It provides a clean
 * separation between game logic and presentation logic.
 */
class UserInterface {
public:
  /**
   * @brief Display welcome message and game rules
   */
  static void displayWelcome();

  /**
   * @brief Display game start message with attempt count
   * @param maxAttempts Number of attempts allowed for this game
   */
  static void displayGameStart(int32_t maxAttempts);

  /**
   * @brief Display game over message when player runs out of attempts
   * @param secretNumber The secret number that was being guessed
   */
  static void displayGameOver(int32_t secretNumber);

  /**
   * @brief Display congratulations message when player wins
   * @param secretNumber The secret number that was successfully guessed
   */
  static void displayWin(int32_t secretNumber);

  /**
   * @brief Display the result of a guess (XaYb format)
   * @param As Number of correct digits in correct positions
   * @param Bs Number of correct digits in wrong positions
   */
  static void displayGuessResult(int32_t As, int32_t Bs);

  /**
   * @brief Display remaining attempts and prompt for next guess
   * @param attemptsLeft Number of attempts remaining
   */
  static void displayAttemptsLeft(int32_t attemptsLeft);

  /**
   * @brief Display goodbye message
   */
  static void displayGoodbye();

  /**
   * @brief Display initial guess prompt
   */
  static void displayInitialGuessPrompt();

  /**
   * @brief Display next guess prompt
   */
  static void displayNextGuessPrompt();
};
