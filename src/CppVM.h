#ifndef CppVM_H
#define CppVM_H

#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
#include <stdexcept>
#include <random>
#include "CppStats.h"
#include <RcppThread.h>

// Function to calculate the CppVMBase value
double CppVMBase(const std::vector<int>& R,
                 const std::vector<int>& Z,
                 const std::string& unit = "e");

// Function to calculate the Information-theoretical V-measure (VM)
double CppVM(const std::vector<int>& R,
             const std::vector<int>& Z,
             const std::string& unit = "e",
             const double& beta = 1);

// CppVMP: Parallel computation of CppVM over permutations, returning IN value and p-value
std::vector<double> CppVMP(const std::vector<int>& d,
                           const std::vector<int>& s,
                           const std::string& unit = "e",
                           const double& beta = 1,
                           const int& seed = 123456789,
                           const int& permutation_number = 999);

#endif // CppVM_H
