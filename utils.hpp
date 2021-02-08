#pragma once

#include <string>
#include <vector>

template <typename Alloc>
std::string vec8toHex(const std::vector<uint8_t, Alloc>& v) {
  std::string result;
  result.reserve(v.size() * 2);
  static constexpr char hex[] = "0123456789ABCDEF";
  for (uint8_t c : v) {
    result.push_back(hex[c / 16]);
    result.push_back(hex[c % 16]);
  }
  return result;
}
