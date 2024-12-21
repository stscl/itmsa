#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
#include <limits>
#include <stdexcept>
#include "CppStats.h"

// Function to calculate the Information Content Measure (ICM)
double CppICM(const std::vector<int>& d,
              const std::vector<int>& s,
              const std::string& unit = "e") {
  // Validate input: d and s must have the same size
  if (d.size() != s.size()) {
    throw std::invalid_argument("Input vectors d and s must have the same size.");
  }

  // Step 1: Calculate probabilities p(x), p(s_i, x), and p(x | s_i)
  std::unordered_map<int, double> p_x; // Probability of x
  std::unordered_map<int, std::unordered_map<int, double>> p_si_x; // Probability of s_i and x
  std::unordered_map<int, std::unordered_map<int, double>> p_x_given_si; // Probability of x given s_i

  // Count occurrences of each x and (s_i, x) pair
  std::unordered_map<int, int> count_x;
  std::unordered_map<int, std::unordered_map<int, int>> count_si_x;

  for (size_t i = 0; i < d.size(); ++i) {
    int x = d[i];
    int si = s[i];
    count_x[x]++;
    count_si_x[si][x]++;
  }

  // Total number of observations
  double total = static_cast<double>(d.size());

  // Calculate p(x)
  for (const auto& pair : count_x) {
    p_x[pair.first] = pair.second / total;
  }

  // Calculate p(s_i, x) and p(x | s_i)
  for (const auto& si_pair : count_si_x) {
    int si = si_pair.first;
    double total_si = 0.0;
    for (const auto& x_pair : si_pair.second) {
      total_si += x_pair.second;
    }
    for (const auto& x_pair : si_pair.second) {
      int x = x_pair.first;
      p_si_x[si][x] = x_pair.second / total;
      p_x_given_si[si][x] = x_pair.second / total_si;
    }
  }

  // Step 2: Calculate the numerator and denominator of the formula
  double numerator = 0.0;
  double denominator = 0.0;

  // Calculate the denominator: sum_{x in V_d} p(x) * log(p(x))
  for (const auto& pair : p_x) {
    double px = pair.second;
    denominator += px * CppLog(px, unit);
  }

  // Calculate the numerator: sum_{s_i in S} sum_{x in V_d} p(s_i, x) * log(p(x | s_i))
  for (const auto& si_pair : p_si_x) {
    int si = si_pair.first;
    for (const auto& x_pair : si_pair.second) {
      int x = x_pair.first;
      double psi_x = x_pair.second;
      double px_given_si = p_x_given_si[si][x];
      numerator += psi_x * CppLog(px_given_si, unit);
    }
  }

  // Step 3: Calculate the final result
  if (denominator == 0.0) {
    return std::numeric_limits<double>::quiet_NaN(); // Avoid division by zero
  }
  return 1.0 - (numerator / denominator);
}
