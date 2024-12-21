#ifndef CppICM_H
#define CppICM_H

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
              const std::string& unit = "e");

// CppICMP: Parallel computation of CppICM over permutations, returning IN value and p-value
std::vector<double> CppICMP(const std::vector<int>& d,
                            const std::vector<int>& s,
                            const std::string& unit = "e",
                            const int& seed = 123456789,
                            const int& permutation_number = 999);

#endif // CppICM_H
