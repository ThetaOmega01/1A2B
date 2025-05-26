/**
 * @file secret_number_generator.hpp
 * @brief Handles generation random numbers
 */

#pragma once

#include <random>

/**
 * @class SecretNumberGenerator
 * @brief Generates secret numbers for the game
 */
class SecretNumberGenerator {
public:
  /**
   * @brief Get the singleton instance of the generator
   * @return Reference to the singleton instance
   */
  static SecretNumberGenerator& getInstance();

  /**
   * @brief Generate a random numSize-digit number with unique digits
   * @return A valid secret number
   */
  int32_t generateSecretNumber();

  SecretNumberGenerator(const SecretNumberGenerator&) = delete;
  SecretNumberGenerator& operator=(const SecretNumberGenerator&) = delete;

private:
  /**
   * @brief Private constructor
   */
  SecretNumberGenerator();

  std::random_device m_randomDevice; ///< Random number generator
  std::mt19937 m_generator;          ///< Mersenne Twister generator
};
