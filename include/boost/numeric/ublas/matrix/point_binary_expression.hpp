#if !defined(point_binary_expression_hpp)
#define point_binary_expression_hpp
#include <boost/numeric/ublas/matrix/matrix_expression.hpp>
#include <cstddef>
#include <iostream>

#include <boost/numeric/ublas/matrix/matrix.hpp>
#include <functional>

template <typename T, class left_type, class right_type>
class point_binary_expression;


template <typename T, class left_type, class right_type>
class point_binary_expression<T,
                              matrix_expression<T, left_type>,
                              matrix_expression<T, right_type>>
  : public matrix_expression<
      T,
      point_binary_expression<T,
                              matrix_expression<T, left_type>,
                              matrix_expression<T, right_type>>> {
  using op_type = std::function<T(const T&, const T&)>;
  const matrix_expression<T, left_type>& left;
  const matrix_expression<T, right_type>& right;
  const op_type op;

public:
  point_binary_expression(const matrix_expression<T, left_type>& left,
                          const matrix_expression<T, right_type>& right,
                          op_type op)
    : left(left)
    , right(right)
    , op(op)
  {
  }
  T operator()(std::size_t i, std::size_t j) const
  {
    return op(left(i, j), right(i, j));
  }

  std::tuple<size_t, size_t> size() const { return left.size(); }
  matrix<T> eval() const
  {
    auto dimensions = size();
    matrix<T> result(dimensions);
    matrix<T> left  = this->left.eval();
    matrix<T> right = this->right.eval();
    for (size_t i = 0; i < std::get<0>(dimensions); ++i)
      for (size_t j = 0; j < std::get<1>(dimensions); ++j)
        result(i, j) = op(left(i, j), right(i, j));
    return result;
  }
  template <class internal_indexer1, class internal_indexer2>
  auto operator()(internal_indexer1 ind1, internal_indexer2 ind2) const
  {
    return make_const_submatrix(*this, ind1, ind2);
  }
};

template <typename T, class right_type>
class point_binary_expression<T, T, matrix_expression<T, right_type>>
  : public matrix_expression<
      T,
      point_binary_expression<T, T, matrix_expression<T, right_type>>> {
  using op_type = std::function<T(const T&, const T&)>;
  const T left;
  const matrix_expression<T, right_type>& right;
  const op_type op;

public:
  point_binary_expression(const T& left,
                          const matrix_expression<T, right_type>& right,
                          op_type op)
    : left(left)
    , right(right)
    , op(op)
  {
  }
  T operator()(std::size_t i, std::size_t j) const
  {
    return op(left, right(i, j));
  }

  std::tuple<size_t, size_t> size() const { return right.size(); }
  matrix<T> eval() const
  {
    auto dimensions = size();
    matrix<T> result(dimensions);
    matrix<T> right = this->right.eval();
    for (size_t i = 0; i < std::get<0>(dimensions); ++i)
      for (size_t j = 0; j < std::get<1>(dimensions); ++j)
        result(i, j) = op(left, right(i, j));
    return result;
  }
  template <class internal_indexer1, class internal_indexer2>
  auto operator()(internal_indexer1 ind1, internal_indexer2 ind2) const
  {
    return make_const_submatrix(*this, ind1, ind2);
  }
};
template <typename T, class left_type>
class point_binary_expression<T, matrix_expression<T, left_type>, T>
  : public matrix_expression<
      T,
      point_binary_expression<T, matrix_expression<T, left_type>, T>> {
  using op_type = std::function<T(const T&, const T&)>;
  const matrix_expression<T, left_type>& left;
  const T right;
  const op_type op;

public:
  point_binary_expression(const matrix_expression<T, left_type>& left,
                          const T& right,
                          op_type op)
    : left(left)
    , right(right)
    , op(op)
  {
  }
  T operator()(std::size_t i, std::size_t j) const
  {
    return op(left(i, j), right);
  }

  T operator[](std::size_t i) const
  {
    auto [rows, columns] = size();
    return op(left(i / rows, i % columns), right);
  }
  std::tuple<size_t, size_t> size() const { return left.size(); }
  matrix<T> eval() const
  {
    auto dimensions = size();
    matrix<T> result(dimensions);
    matrix<T> left = this->left.eval();
    for (size_t i = 0; i < std::get<0>(dimensions); ++i)
      for (size_t j = 0; j < std::get<1>(dimensions); ++j)
        result(i, j) = op(left(i, j), right);
    return result;
  }
  template <class internal_indexer1, class internal_indexer2>
  auto operator()(internal_indexer1 ind1, internal_indexer2 ind2) const
  {
    return make_const_submatrix(*this, ind1, ind2);
  }
};
#endif
