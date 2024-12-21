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

#endif // CppICM_H
