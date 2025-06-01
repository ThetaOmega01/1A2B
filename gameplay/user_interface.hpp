/**
 * @file user_interface.hpp
 * @brief Handles all user interface operations
 */

#pragma once

#include <string>

/**
 * @enum GameMode
 * @brief Represents different game modes available
 */
enum class GameMode { manualPlay, solver };

/**
 * @class UserInterface
 * @brief Manages all display and messaging operations
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

  /**
   * @brief Display game mode selection menu
   */
  static void displayGameModeSelection();

  /**
   * @brief Get game mode choice from user
   * @return Selected game mode
   */
  static GameMode getGameModeChoice();

  /**
   * @brief Display solver strategy selection menu
   */
  static void displaySolverStrategySelection();

  /**
   * @brief Get solver strategy choice from user
   * @return Selected strategy index (0-3)
   */
  static int32_t getSolverStrategyChoice();

  /**
   * @brief Display solver start message
   * @param strategy The strategy being used
   * @param maxAttempts Maximum attempts allowed
   */
  static void displaySolverStart(std::string_view strategy,
                                 int32_t maxAttempts);

  /**
   * @brief Display solver's guess and ask for feedback
   * @param guessNumber The guess number (1, 2, 3, etc.)
   * @param guess The guess made by solver
   * @param attemptsLeft Number of attempts remaining
   */
  static void displaySolverGuess(int32_t guessNumber, int32_t guess,
                                 int32_t attemptsLeft);

  /**
   * @brief Get feedback input from user
   * @return User's feedback string (e.g., "2A1B", "reset")
   */
  static std::string getFeedbackInput();

  /**
   * @brief Display invalid feedback message
   */
  static void displayInvalidFeedback();

  /**
   * @brief Display remaining possibilities count
   * @param count Number of remaining possibilities
   */
  static void displayRemainingPossibilities(size_t count);

  /**
   * @brief Display solver success message
   * @param secretNumber The secret number that was solved
   * @param totalGuesses Total number of guesses made
   */
  static void displaySolverSuccess(int32_t secretNumber, int32_t totalGuesses);

  /**
   * @brief Display solver failure message
   * @param totalGuesses Total number of guesses made
   */
  static void displaySolverFailure(int32_t totalGuesses);

  /**
   * @brief Display solver reset message
   */
  static void displaySolverReset();

  /**
   * @brief Display message when solver has no more guesses
   * @param totalGuesses Total number of guesses made
   */
  static void displaySolverNoMoreGuesses(int32_t totalGuesses);
};
