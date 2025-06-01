/**
 * @file cache_manager.hpp
 * @brief Generic cache management for strategy calculations
 */

#pragma once

#include <optional>
#include <unordered_map>

/**
 * @class CacheManager
 * @brief Template class for managing calculation caches
 * @tparam T The type of values to cache
 */
template <typename T> class CacheManager {
public:
  /**
   * @brief Default constructor
   */
  CacheManager() = default;

  /**
   * @brief Cache a value with the given key
   * @param key The key to associate with the value
   * @param value The value to cache
   */
  void cache(int32_t key, const T& value) { m_cache.at(key) = value; }

  /**
   * @brief Retrieve a cached value by key
   * @param key The key to look up
   * @return The cached value if found, nullopt otherwise
   */
  [[nodiscard]] std::optional<T> get(int32_t key) const {
    if (const auto it{m_cache.find(key)}; it != m_cache.end()) {
      return it->second;
    }
    return std::nullopt;
  }

  /**
   * @brief Clear all cached values
   */
  void clear() { m_cache.clear(); }

  /**
   * @brief Check if a key exists in the cache
   * @param key The key to check
   * @return true if the key exists in the cache, false otherwise
   */
  [[nodiscard]] bool contains(int32_t key) const {
    return m_cache.contains(key);
  }

  /**
   * @brief Get the number of cached entries
   * @return The size of the cache
   */
  [[nodiscard]] size_t size() const { return m_cache.size(); }

  /**
   * @brief Check if the cache is empty
   * @return true if the cache is empty, false otherwise
   */
  [[nodiscard]] bool empty() const { return m_cache.empty(); }

private:
  mutable std::unordered_map<int32_t, T>
      m_cache; ///< The underlying cache storage
};
