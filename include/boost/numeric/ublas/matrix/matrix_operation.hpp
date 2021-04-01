#include <boost/numeric/ublas/matrix/unary_expression.hpp>
#include <boost/numeric/ublas/matrix/binary_expression.hpp>
#include <boost/numeric/ublas/matrix/matrix_multiplication.hpp>
#include <boost/numeric/ublas/matrix/transpose.hpp>
#include <boost/numeric/ublas/matrix/scalar.hpp>

#include <cstddef>
#include <functional>
#include <iostream>


template <typename T, typename left_type, typename right_type>
point_binary_expression<T, left_type, right_type> operator+(
  const matrix_expression<T, left_type>& left,
  const matrix_expression<T, right_type>& right)
{
  return point_binary_expression<T, left_type, right_type>(

    static_cast<const left_type&>(left),
    static_cast<const right_type&>(right),
    [](const T& left, const T& right) { return left + right; },
    left.size());
}
template <typename T, typename left_type, typename right_type>
point_binary_expression<T, left_type, right_type> operator-(
  const matrix_expression<T, left_type>& left,
  const matrix_expression<T, right_type>& right)
{
  return point_binary_expression<T, left_type, right_type>(

    static_cast<const left_type&>(left),
    static_cast<const right_type&>(right),
    [](const T& left, const T& right) { return left - right; },
    left.size());
}
template <typename T, typename left_type, typename right_type>
point_binary_expression<T, left_type, right_type> operator==(
  const matrix_expression<T, left_type>& left,
  const matrix_expression<T, right_type>& right)
{
  return point_binary_expression<T, left_type, right_type>(

    static_cast<const left_type&>(left),
    static_cast<const right_type&>(right),
    [](const T& left, const T& right) { return left == right; },
    left.size());
}
template <typename T, typename exp_type>
point_binary_expression<T, scalar<T>, exp_type> operator*(
  const T& left, const matrix_expression<T, exp_type>& right)
{
  return point_binary_expression<T, scalar<T>, exp_type>(

    scalar<T>(left),
    static_cast<const exp_type&>(right),
    [](const T& left, const T& right) { return left * right; },
    right.size());
}

template <typename T, typename left_type, typename right_type>
matrix_multiplication<T, left_type, right_type> operator*(
  const matrix_expression<T, left_type>& left,
  const matrix_expression<T, right_type>& right)
{
  return matrix_multiplication<T, left_type, right_type>(left, right);
}

template <typename T, typename exp_type>
Transpose<T, exp_type> transpose(const matrix_expression<T, exp_type>& exp)
{
  return Transpose<T, exp_type>(exp);
}
