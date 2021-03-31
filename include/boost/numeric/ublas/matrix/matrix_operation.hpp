#include <boost/numeric/ublas/matrix/unary_expression.hpp>
#include <boost/numeric/ublas/matrix/binary_expression.hpp>
#include <boost/numeric/ublas/matrix/matrix_multiplication.hpp>
#include <cstddef>
#include <functional>
#include <iostream>


template <typename T, typename left_type, typename right_type>
point_binary_expression<T,
                        matrix_expression<T, left_type>,
                        matrix_expression<T, right_type>>
operator+(const matrix_expression<T, left_type>& left,
          const matrix_expression<T, right_type>& right)
{
  return point_binary_expression<T,
                                 matrix_expression<T, left_type>,
                                 matrix_expression<T, right_type>>(

    left,
    right,
    [](const T& left, const T& right) { return left + right; },
    left.size());
}

template <typename T, typename left_type, typename right_type>
point_binary_expression<T,
                        matrix_expression<T, left_type>,
                        matrix_expression<T, right_type>>
operator-(const matrix_expression<T, left_type>& left,
          const matrix_expression<T, right_type>& right)
{
  return point_binary_expression<T,
                                 matrix_expression<T, left_type>,
                                 matrix_expression<T, right_type>>(
    left,
    right,
    [](const T& left, const T& right) { return left - right; },
    left.size());
}

template <typename T, typename left_type, typename right_type>
point_binary_expression<T,
                        matrix_expression<T, left_type>,
                        matrix_expression<T, right_type>>
operator==(const matrix_expression<T, left_type>& left,
           const matrix_expression<T, right_type>& right)
{
  return point_binary_expression<T,
                                 matrix_expression<T, left_type>,
                                 matrix_expression<T, right_type>>(

    left,
    right,
    [](const T& left, const T& right) { return left == right; },
    left.size());
}

template <typename T, typename left_type, typename right_type>
matrix_multiplication<T,
                      matrix_expression<T, left_type>,
                      matrix_expression<T, right_type>>
operator*(const matrix_expression<T, left_type>& left,
          const matrix_expression<T, right_type>& right)
{
  return matrix_multiplication<T,
                               matrix_expression<T, left_type>,
                               matrix_expression<T, right_type>>();
}
