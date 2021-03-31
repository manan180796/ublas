#include <boost/numeric/ublas/matrix/matrix_operation.hpp>
#include <iostream>
int main()
{
  auto one         = matrix<double>({10, 10}, 1);
  auto zne         = matrix<double>({10, 10}, 1);
  matrix<double> k = (zne - one);
  one(0, 0)        = 2;
  std::cout << k.eval();
  // std::cout << zeros<double>(10, 10).eval();
}
