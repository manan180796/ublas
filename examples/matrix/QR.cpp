#include "boost/numeric/ublas/matrix/indexer.hpp"
#include "boost/numeric/ublas/matrix/matrix_expression.hpp"
#include <boost/numeric/ublas/matrix/matrix_operation.hpp>
#include <iostream>
#include <tuple>
template <typename T> std::tuple<matrix<T>, matrix<T>> qr(const matrix<T>& A)
{
  auto [m, n] = A.size();

  auto Q = zeros<T>(m, n);
  auto R = zeros<T>(n, n);
  for (size_t k = 0; k < n; ++k) {
    std::cout << k << std::endl;
    if (k > 0)
      R(splice(0, k), splice(k, k + 1)) =
        transpose(Q(splice(0, m), splice(0, k))) *
        A(splice(0, m), splice(k, k + 1));
    matrix<double> v = A(splice(0, m), splice(k, k + 1));
    if (k > 0)
      v = matrix<double>(v - Q(splice(0, m), splice(0, k)) *
                               R(splice(0, k), splice(k, k + 1)));

    R(k, k)                           = norm(v);
    Q(splice(0, m), splice(k, k + 1)) = v / R(k, k);
  }

  return {Q, R};
}
int main()
{
  matrix<double> A({2, 2}, 1);
  A(size_t(0), size_t(1)) = 0;
  // A(size_t(2), size_t(1)) = 1;
  std::cout << A << std::endl;
  auto [Q, R] = qr(A);
  std::cout << "Q=" << Q;
  std::cout << "R=" << R;
  std::cout << (Q * R).eval() << std::endl;
  return 0;
}
