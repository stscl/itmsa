#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <random>
#include "CppStats.h"
#include <RcppThread.h>

// [[Rcpp::plugins(cpp11)]]
// [[Rcpp::depends(RcppThread)]]

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

// CppICMP: Parallel computation of CppICM over permutations, returning IN value and p-value
std::vector<double> CppICMP(const std::vector<int>& d,
                            const std::vector<int>& s,
                            const std::string& unit = "e",
                            const int& seed = 123456789,
                            const int& permutation_number = 999) {
  if (s.size() != d.size()) {
    throw std::invalid_argument("Vectors s and d must have the same length.");
  }

  // Step 1: Calculate the true IN value using the original d and s
  double true_IN = CppICM(d, s, unit);

  // Step 2: Generate random permutations of d and compute IN for each
  std::vector<double> IN_results(permutation_number, 0.0);  // Store IN values for each permutation

  // Step 3: Generate a random seed using the input seed
  std::mt19937 seed_gen(seed);  // Initialize random number generator with the input seed
  // std::uniform_int_distribution<> dis(1, std::numeric_limits<int>::max());  // Define a distribution for random integers
  std::uniform_int_distribution<> dis(1, 100);
  int randomseed = dis(seed_gen);  // Generate a random integer using the input seed

  // Step 4: Perform parallel computation
  RcppThread::parallelFor(0, permutation_number, [&](size_t i) {
    // Step 4.1: Generate a unique seed for each permutation by adding the iteration index to the randomseed
    std::mt19937 local_gen(randomseed + i);  // Modify seed for each thread

    // Step 4.2: Permute d
    std::vector<int> permuted_d = d;  // Copy the original d
    std::shuffle(permuted_d.begin(), permuted_d.end(), local_gen); // Shuffle based on the unique seed for each thread

    // Step 4.3: Compute IN_SSH for the permuted d
    IN_results[i] = CppICM(permuted_d, s, unit);
  });

  // Step 5: Compute p-value by comparing permuted IN_SSH values to the true IN_SSH value
  int greater_count = 0;
  for (size_t i = 0; i < IN_results.size(); ++i) {
    if (IN_results[i] >= true_IN) {
      greater_count++;
    }
  }

  double p_value = static_cast<double>(greater_count) / permutation_number;

  // Return a vector containing the true IN_SSH and p-value
  return {true_IN, p_value};
}
