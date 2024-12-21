#include <vector>
#include "CppICM.h"
#include "CppVM.h"
#include <Rcpp.h>

// Rcpp wrapper for CppICM
// [[Rcpp::export]]
double RcppICM(Rcpp::IntegerVector d,
               Rcpp::IntegerVector s,
               Rcpp::String unit) {
  // Convert Rcpp::IntegerVector to std::vector<int>
  std::vector<int> d_std = Rcpp::as<std::vector<int>>(d);
  std::vector<int> s_std = Rcpp::as<std::vector<int>>(s);
  // Convert Rcpp::String to std::string
  std::string unit_std = unit.get_cstring();

  // Call the CppICM function
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

  // Call the CppICMP function
  std::vector<double> result = CppICMP(d_std, s_std, unit_std, seed, permutation_number);

  // Convert the std::vector<double> result to Rcpp::NumericVector with names
  Rcpp::NumericVector named_result(result.begin(), result.end());
  named_result.names() = Rcpp::CharacterVector::create("Iv", "Pv");

  return named_result;
}

// Rcpp wrapper for CppVMBase
// [[Rcpp::export]]
double RcppVMBase(Rcpp::IntegerVector d,
                  Rcpp::IntegerVector s,
                  Rcpp::String unit) {
  // Convert Rcpp::IntegerVector to std::vector<int>
  std::vector<int> d_std = Rcpp::as<std::vector<int>>(d);
  std::vector<int> s_std = Rcpp::as<std::vector<int>>(s);
  // Convert Rcpp::String to std::string
  std::string unit_std = unit.get_cstring();

  // Call the CppVMBase function
  double result = CppVMBase(d_std, s_std, unit_std);

  // Return the result as a double
  return result;
}

// Rcpp wrapper for CppVM
// [[Rcpp::export]]
double RcppVM(Rcpp::IntegerVector d,
              Rcpp::IntegerVector s,
              Rcpp::String unit,
              double beta = 1) {
  // Convert Rcpp::IntegerVector to std::vector<int>
  std::vector<int> d_std = Rcpp::as<std::vector<int>>(d);
  std::vector<int> s_std = Rcpp::as<std::vector<int>>(s);
  // Convert Rcpp::String to std::string
  std::string unit_std = unit.get_cstring();

  // Call the CppVM function
  double result = CppVM(d_std, s_std, unit_std, beta);

  // Return the result as a double
  return result;
}

// Rcpp wrapper for RcppVMP
// [[Rcpp::export]]
Rcpp::NumericVector RcppVMP(Rcpp::IntegerVector d,
                            Rcpp::IntegerVector s,
                            Rcpp::String unit,
                            double beta,
                            int seed,
                            int permutation_number) {
  // Convert Rcpp::IntegerVector to std::vector<int>
  std::vector<int> d_std = Rcpp::as<std::vector<int>>(d);
  std::vector<int> s_std = Rcpp::as<std::vector<int>>(s);
  // Convert Rcpp::String to std::string
  std::string unit_std = unit.get_cstring();

  // Call the CppVMP function
  std::vector<double> result = CppVMP(d_std, s_std, unit_std, beta, seed, permutation_number);

  // Convert the std::vector<double> result to Rcpp::NumericVector with names
  Rcpp::NumericVector named_result(result.begin(), result.end());
  named_result.names() = Rcpp::CharacterVector::create("Iv", "Pv");

  return named_result;
}
