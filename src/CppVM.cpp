#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
#include <stdexcept>
#include "CppStats.h"

// Function to calculate the CppVMBase value
double CppVMBase(const std::vector<int>& R, const std::vector<int>& Z, const std::string& unit = "e") {
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
