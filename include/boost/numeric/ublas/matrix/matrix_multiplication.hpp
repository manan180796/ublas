#include "boost/numeric/ublas/matrix/matrix_expression.hpp"
#include "boost/numeric/ublas/matrix/submatrix.hpp"
#include <cstddef>
#if !defined(matrix_multiplication_hpp)
#define matrix_multiplication_hpp

#include <tuple>
#include <boost/numeric/ublas/matrix/matrix.hpp>
#include <functional>

template <typename T, class left_type, class right_type>
class matrix_multiplication
  : public matrix_expression<T,
                             matrix_multiplication<T, left_type, right_type>> {
  const matrix_expression<T, left_type>& left;
  const matrix_expression<T, right_type>& right;

public:
  matrix_multiplication(const matrix_expression<T, left_type>& left,
                        const matrix_expression<T, right_type>& right)
    : left(left)
    , right(right)
  {
  }
  T operator()(size_t i, size_t j) const
  {
    // std::cout << "matrix_multiplication point expression" << std::endl;
    T result = 0;
    for (size_t k = 0; k < std::get<1>(left.size()); ++k) {
      // std::cout << k << std::endl;
      result += left(i, k) * right(k, j);
    }
    return result;
  }

  T operator[](std::size_t i) const
  {
    auto [rows, columns] = size();
    return (*this)(i / rows, i % rows);
  }
  std::tuple<size_t, size_t> size() const
  {
    return std::make_tuple(std::get<0>(left.size()), std::get<1>(right.size()));
  }
  matrix<T> eval() const
  {
    auto dimensions = size();
    matrix<T> left  = this->left.eval();
    matrix<T> right = this->right.eval();
    matrix<T> result(dimensions);
    size_t intermediate_axis = std::get<1>(left.size());
    for (size_t i = 0; i < std::get<0>(dimensions); ++i)
      for (size_t j = 0; j < std::get<1>(dimensions); ++j) {
        result(i, j) = 0;
        for (size_t k = 0; k < intermediate_axis; ++k) {
          result(i, j) += left(i, k) * right(k, j);
        }
      }
    return result;
  }
  template <class internal_indexer1, class internal_indexer2>
  auto operator()(internal_indexer1 ind1, internal_indexer2 ind2) const
  {
    return make_const_submatrix(*this, ind1, ind2);
  }
};

#endif
