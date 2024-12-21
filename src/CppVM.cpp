#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
#include <stdexcept>
#include <random>
#include "CppStats.h"
#include <RcppThread.h>

// [[Rcpp::plugins(cpp11)]]
// [[Rcpp::depends(RcppThread)]]

// Function to calculate the CppVMBase value
double CppVMBase(const std::vector<int>& R,
                 const std::vector<int>& Z,
                 const std::string& unit = "e") {
  // Validate input sizes
  if (R.size() != Z.size()) {
    throw std::invalid_argument("Input vectors R and Z must have the same size.");
  }

  // Step 1: Calculate the total area A
  size_t A = R.size();

  // Step 2: Calculate A_i (number of elements in R where R == i)
  std::unordered_map<int, size_t> A_i_map;
  for (int r : R) {
    A_i_map[r]++;
  }

  // Step 3: Calculate A_j (number of elements in Z where Z == j)
  std::unordered_map<int, size_t> A_j_map;
  for (int z : Z) {
    A_j_map[z]++;
  }

  // Step 4: Calculate S^R
  double S_R = 0.0;
  for (const auto& pair : A_i_map) {
    double p_i = static_cast<double>(pair.second) / A;
    S_R -= p_i * CppLog(p_i, unit);
  }

  // Step 5: Calculate a_{i,j} (count of elements where R == i and Z == j)
  std::unordered_map<int, std::unordered_map<int, size_t>> a_ij_map;
  for (size_t k = 0; k < R.size(); ++k) {
    a_ij_map[R[k]][Z[k]]++;
  }

  // Step 6: Calculate S_j^R for each j
  std::unordered_map<int, double> S_j_R_map;
  for (const auto& A_j_pair : A_j_map) {
    int j = A_j_pair.first;
    size_t A_j = A_j_pair.second;
    double S_j_R = 0.0;

    for (const auto& a_ij_pair : a_ij_map) {
      // int i = a_ij_pair.first;
      // Use find instead of operator[] for const map
      auto it = a_ij_pair.second.find(j);
      size_t a_ij = (it != a_ij_pair.second.end()) ? it->second : 0;

      if (a_ij > 0) {
        double p_ij = static_cast<double>(a_ij) / A_j;
        S_j_R -= p_ij * CppLog(p_ij, unit);
      }
    }

    S_j_R_map[j] = S_j_R;
  }

  // Step 7: Calculate h
  double h = 1.0;
  for (const auto& A_j_pair : A_j_map) {
    int j = A_j_pair.first;
    size_t A_j = A_j_pair.second;
    double S_j_R = S_j_R_map[j];
    h -= (static_cast<double>(A_j) / A) * (S_j_R / S_R);
  }

  return h;
}

// Function to calculate the Information-theoretical V-measure (VM)
double CppVM(const std::vector<int>& R,
             const std::vector<int>& Z,
             const std::string& unit = "e",
             const double& beta = 1) {
  double h = CppVMBase(R,Z,unit);
  double c = CppVMBase(Z,R,unit);
  double V_beta = (1 + beta) * h * c / (beta * h + c);
  return V_beta;
}

// CppVMP: Parallel computation of CppVM over permutations, returning IN value and p-value
std::vector<double> CppVMP(const std::vector<int>& d,
                           const std::vector<int>& s,
                           const std::string& unit = "e",
                           const double& beta = 1,
                           const int& seed = 123456789,
                           const int& permutation_number = 999){
  if (s.size() != d.size()) {
    throw std::invalid_argument("Vectors s and d must have the same length.");
  }

  // Step 1: Calculate the true IN value using the original d and s
  double true_IN = CppVM(d, s, unit, beta);

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
    IN_results[i] = CppVM(permuted_d, s, unit, beta);
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
