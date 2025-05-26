#pragma once

#include <array>
#include <cstdint>

/**
 * @interface IGameSession
 * @brief Virtual interface for game session management
 */
class IGameSession {
public:
  /**
   * @brief Virtual destructor
   */
  virtual ~IGameSession() = default;

  /**
   * @brief Get the maximum number of attempts allowed
   * @return The total number of attempts allowed for this game session
   */
  [[nodiscard]] virtual int32_t getMaxAttempts() const = 0;

  /**
   * @brief Get the number of attempts remaining
   * @return The number of guessing attempts left for the player
   * @note When this reaches 0, the game should end if the player hasn't won
   */
  [[nodiscard]] virtual int32_t getAttemptsLeft() const = 0;

  /**
   * @brief Process a player's guess and return the score
   * @param guess The player's guess as an integer
   * @return Array containing [A_count, B_count] where A is correct digits in
   *         correct positions and B is correct digits in wrong positions
   */
  virtual std::array<int32_t, 2> makeGuess(int32_t guess) = 0;

  /**
   * @brief Start the game session
   */
  virtual void start() = 0;

  /**
   * @brief Check if the game has been won
   * @return true if the secret number has been guessed correctly
   */
  [[nodiscard]] virtual bool isGameWon() const = 0;

  /**
   * @brief Check if the game is over (won or out of attempts)
   * @return true if the game session has ended
   */
  [[nodiscard]] virtual bool isGameOver() const = 0;
};

/**
 * @class GameSessionBase
 * @brief Base implementation class for game sessions
 */
class GameSessionBase : public IGameSession {
public:
  /**
   * @brief Initialize the game session with a secret number and maximum
   * attempts
   * @param secret The secret number that the player needs to guess
   * @param maxAttempts Maximum number of attempts allowed for the player
   */
  explicit GameSessionBase(int32_t secret, int32_t maxAttempts);

  /**
   * @brief Virtual destructor
   */
  ~GameSessionBase() override = default;

  // IGameSession interface implementation
  [[nodiscard]] int32_t getMaxAttempts() const override {
    return m_maxAttempts;
  }
  [[nodiscard]] int32_t getAttemptsLeft() const override {
    return m_attemptsLeft;
  }
  [[nodiscard]] bool isGameWon() const override { return m_gameWon; }
  [[nodiscard]] bool isGameOver() const override {
    return m_gameWon || m_attemptsLeft <= 0;
  }

  /**
   * @brief Get the secret number
   * @return The secret number that the player is trying to guess
   */
  [[nodiscard]] int32_t getSecret() const { return m_secret; }

protected:
  /**
   * @brief Set the maximum number of attempts and reset current attempts
   * @param maxAttempts The new maximum number of attempts allowed
   * @pre maxAttempts should be a positive integer
   * @post m_attemptsLeft is reset to maxAttempts
   */
  void setMaxAttempts(int32_t maxAttempts);

  /**
   * @brief Decrement the attempts counter
   * @note Should be called by derived classes when processing a guess
   */
  void decrementAttempts() { --m_attemptsLeft; }

  /**
   * @brief Mark the game as won
   * @note Should be called by derived classes when the correct guess is made
   */
  void setGameWon() { m_gameWon = true; }

private:
  int32_t m_secret{}; ///< The secret number that the player is trying to guess
  int32_t m_maxAttempts{}; ///< Maximum number of attempts allowed for this game
                           ///< session
  int32_t m_attemptsLeft{}; ///< Number of attempts remaining for the player
  bool m_gameWon{false};    ///< Flag indicating if the game has been won
};
