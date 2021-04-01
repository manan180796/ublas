#include <boost/numeric/ublas/matrix/matrix_operation.hpp>
#include <iostream>
int main()
{
  auto one = matrix<double>({10, 9}, 1);
  auto zne = matrix<double>({10, 9}, 1);
  // one(0, 1)        = 2;
  matrix<double> k = transpose(2.0 * one);
  std::cout << k.eval();
  // std::cout << zeros<double>(10, 10).eval();
}
