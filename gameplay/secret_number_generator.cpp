#include "secret_number_generator.hpp"
#include "../utils/utils.hpp"
#include <algorithm>
#include <array>
#include <stdexcept>

SecretNumberGenerator::SecretNumberGenerator()
    : m_generator{m_randomDevice()} {}

SecretNumberGenerator& SecretNumberGenerator::getInstance() {
  static SecretNumberGenerator instance{};
  return instance;
}

int32_t SecretNumberGenerator::generateSecretNumber() {
  // Create array of digits 0-9
  std::array digits{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  // Shuffle the digits
  std::ranges::shuffle(digits, m_generator);

  // Ensure first digit is not 0
  if (digits.at(0) == 0) {
    // Find first non-zero digit and swap
    for (int32_t i{1}; i < 10; ++i) {
      if (digits.at(i) != 0) {
        std::swap(digits.at(0), digits.at(i));
        break;
      }
    }
  }

  // Build the number
  int32_t secret{0};
  for (int32_t i{0}; i < utils::numberSize; ++i) {
    secret = secret * 10 + digits.at(i);
  }

  // Validate the generated number
  if (secret < utils::minValidNumber || secret > utils::maxValidNumber) {
    throw std::runtime_error("Generated secret number is out of valid range");
  }

  return secret;
}
