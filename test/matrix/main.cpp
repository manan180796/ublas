#include "boost/numeric/ublas/matrix/indexer.hpp"
#include "boost/numeric/ublas/matrix/matrix_expression.hpp"
#include <boost/numeric/ublas/matrix/matrix_operation.hpp>
#include <cstddef>
#include <iostream>
int main()
{
  auto one                  = matrix<double>({10, 9}, 1);
  auto zne                  = matrix<double>({10, 9}, 1);
  one(size_t(0), size_t(1)) = 2 * 2;
  matrix<double> k          = zeros<double>(10, 10);
  k(splice(2), splice(3))   = 1;
  std::cout << k.eval();
  // B b;
  // b.hello();
  // std::cout << zeros<double>(10, 10).eval();
}
