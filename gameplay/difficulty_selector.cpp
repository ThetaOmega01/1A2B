#include "difficulty_selector.hpp"
#include "input_validator.hpp"
#include <iostream>
#include <format>

int32_t DifficultySelector::getMaxAttempts() {
  displayDifficultyOptions();
  const DifficultyLevel level{getDifficultyChoice()};

  if (level == DifficultyLevel::Custom) {
    return getCustomAttempts();
  }

  return getAttemptsForDifficulty(level);
}

int32_t
DifficultySelector::getAttemptsForDifficulty(const DifficultyLevel level) {
  switch (level) {
  case DifficultyLevel::Easy:
    return 15;
  case DifficultyLevel::Medium:
    return 10;
  case DifficultyLevel::Hard:
    return 7;
  case DifficultyLevel::Expert:
    return 5;
  case DifficultyLevel::Custom:
    // This should not be called for custom difficulty
    return getCustomAttempts();
  }
  return 10; // Default fallback
}

int32_t DifficultySelector::getCustomAttempts() {
  std::cout << "Enter custom number of attempts (1-50): ";
  return InputValidator::getIntegerInRange(
      1, 50, "Please enter a number between 1 and 50: ");
}

bool DifficultySelector::playAgain() {
  std::cout << "\nWould you like to play again? (y/n): ";
  return InputValidator::getYesNoChoice(
      "Please enter 'y' for yes or 'n' for no: ");
}

void DifficultySelector::displayDifficultyOptions() {
  const std::string message{std::format("Choose difficulty level:\n"
                                    "1. Easy (15 attempts)\n"
                                    "2. Medium (10 attempts)\n"
                                    "3. Hard (7 attempts)\n"
                                    "4. Expert (5 attempts)\n"
                                    "5. Custom\n"
                                    "Enter your choice (1-5): ")};
  std::cout << message;
}

DifficultyLevel DifficultySelector::getDifficultyChoice() {
  const int32_t choice{InputValidator::getIntegerInRange(
      1, 5, "Invalid choice. Please enter a number (1-5): ")};
  return static_cast<DifficultyLevel>(choice - 1); // Convert 1-5 to 0-4
}
