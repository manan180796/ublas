#include "boost/numeric/ublas/matrix/matrix_expression.hpp"
#include <boost/numeric/ublas/matrix/unary_expression.hpp>
#include <boost/numeric/ublas/matrix/point_binary_expression.hpp>
#include <boost/numeric/ublas/matrix/matrix_multiplication.hpp>
#include <boost/numeric/ublas/matrix/transpose.hpp>
#include <boost/numeric/ublas/matrix/submatrix.hpp>

#include <cmath>
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
  return {

    left, right, [](const T& left, const T& right) { return left + right; }};
}
template <typename T, typename left_type, typename right_type>
point_binary_expression<T,
                        matrix_expression<T, left_type>,
                        matrix_expression<T, right_type>>
operator-(const matrix_expression<T, left_type>& left,
          const matrix_expression<T, right_type>& right)
{
  return {

    left, right, [](const T& left, const T& right) { return left - right; }};
}
template <typename T, typename left_type, typename right_type>
point_binary_expression<T,
                        matrix_expression<T, left_type>,
                        matrix_expression<T, right_type>>
operator==(const matrix_expression<T, left_type>& left,
           const matrix_expression<T, right_type>& right)
{
  return {

    left, right, [](const T& left, const T& right) { return left == right; }};
}

// scalar operations
template <typename T, typename exp_type>
point_binary_expression<T, T, matrix_expression<T, exp_type>> operator*(
  const T& left, const matrix_expression<T, exp_type>& right)
{
  return {

    left, right, [](const T& left, const T& right) { return left * right; }};
}
template <typename T, typename exp_type>
point_binary_expression<T, matrix_expression<T, exp_type>, T> operator*(
  const matrix_expression<T, exp_type>& left, const T& right)
{
  return {

    left, right, [](const T& left, const T& right) { return left * right; }};
}
template <typename T, typename exp_type>
point_binary_expression<T, matrix_expression<T, exp_type>, T> operator/(
  const matrix_expression<T, exp_type>& left, const T& right)
{
  return {

    left, right, [](const T& left, const T& right) { return left / right; }};
}
// matrix multiplication
template <typename T, typename left_type, typename right_type>
matrix_multiplication<T, left_type, right_type> operator*(
  const matrix_expression<T, left_type>& left,
  const matrix_expression<T, right_type>& right)
{
  return {left, right};
}

template <typename T, typename exp_type>
Transpose<T, exp_type> transpose(const matrix_expression<T, exp_type>& exp)
{
  return {exp};
}
template <typename T, typename exp_type>
T norm(const matrix_expression<T, exp_type>& exp)
{
  auto result = exp.eval();
  auto [m, n] = exp.size();
  T sum       = 0;
  for (size_t i = 0; i < m; ++i)
    for (size_t j = 0; j < n; ++j) sum += result(i, j) * result(i, j);
  return std::sqrt(sum);
}
// template <typename T, typename exp_type, typename indexer1, typename
// indexer2> submatrix_reference<T, exp_type, indexer1, indexer2> operator()(
// const matrix_expression<T, exp_type>& exp,
// const indexer<indexer1>& ind1,
// const indexer<indexer2>& ind2)
//{
// return {exp, {ind1, ind2}};
//}
