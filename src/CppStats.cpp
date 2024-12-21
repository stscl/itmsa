#include <string>
#include <cmath>
#include <limits>

// Function to calculate the logarithm of x with a specified base (default is "e")
double CppLog(double x, const std::string& unit = "e") {
  // Check if x is less than or equal to 0, which is invalid for logarithm
  if (x <= 0) {
    return std::numeric_limits<double>::quiet_NaN(); // Return NaN for invalid input
  }

  // Calculate the logarithm based on the specified unit
  if (unit == "e") {
    return std::log(x);
  } else if (unit == "2") {
    return std::log2(x);
  } else {
    return std::log10(x);
  }
}
