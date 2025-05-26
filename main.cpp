#include "gameplay/game_manager.hpp"
#include <exception>
#include <iostream>

/**
 * @brief Main entry point for 1A2B game
 */
int main() {
  try {
    GameManager::run();
    return 0;
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
}
