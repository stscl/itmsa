#include <vector>
#include "CppICM.h"
#include <Rcpp.h>

// Rcpp wrapper for IN_SSH
// [[Rcpp::export]]
double RcppICM(Rcpp::IntegerVector d,
               Rcpp::IntegerVector s,
               Rcpp::String unit) {
  // Convert Rcpp::IntegerVector to std::vector<int>
  std::vector<int> d_std = Rcpp::as<std::vector<int>>(d);
  std::vector<int> s_std = Rcpp::as<std::vector<int>>(s);
  // Convert Rcpp::String to std::string
  std::string unit_std = unit.get_cstring();

  // Call the IN_SSH function
  double result = CppICM(d_std, s_std, unit_std);

  // Return the result as a double
  return result;
}

// Rcpp wrapper for RcppICMP
// [[Rcpp::export]]
Rcpp::NumericVector RcppICMP(Rcpp::IntegerVector d,
                             Rcpp::IntegerVector s,
                             Rcpp::String unit,
                             int seed,
                             int permutation_number) {
  // Convert Rcpp::IntegerVector to std::vector<int>
  std::vector<int> d_std = Rcpp::as<std::vector<int>>(d);
  std::vector<int> s_std = Rcpp::as<std::vector<int>>(s);
  // Convert Rcpp::String to std::string
  std::string unit_std = unit.get_cstring();

  // Call the IN_SSHICM function
  std::vector<double> result = CppICMP(d_std, s_std, unit_std, seed, permutation_number);

  // Convert the std::vector<double> result to Rcpp::NumericVector with names
  Rcpp::NumericVector named_result(result.begin(), result.end());
  named_result.names() = Rcpp::CharacterVector::create("Ic", "Pv");

  return named_result;
}
