#include <cstddef>
#include <iostream>
#if !defined(binary_expression_hpp)
#define binary_expression_hpp

#include <boost/numeric/ublas/matrix/matrix.hpp>
#include <functional>

template <typename T, typename left_type, typename right_type>
class point_binary_expression
  : public matrix_expression<
      T,
      point_binary_expression<T, left_type, right_type>> {
  using op_type = std::function<T(const T&, const T&)>;
  const left_type& left;
  const right_type& right;
  const op_type op;
  const std::tuple<size_t, size_t> dimensions;

public:
  point_binary_expression(const left_type& left,
                          const right_type& right,
                          op_type op,
                          std::tuple<size_t, size_t> dimensions)
    : left(left)
    , right(right)
    , op(op)
    , dimensions(dimensions)
  {
  }
  T operator()(std::size_t i, std::size_t j) const
  {
    return op(left(i, j), right(i, j));
  }

  T operator[](std::size_t i) const
  {
    auto [rows, columns] = size();
    return op(left(i / rows, i % columns), right(i / rows, i % columns));
  }
  std::tuple<size_t, size_t> size() const { return dimensions; }
  matrix<T> eval() const
  {
    auto dimensions = size();
    matrix<T> result(dimensions);
    // matrix<T> left  = this->left.eval();
    // matrix<T> right = this->right.eval();
    std::cout << "value of left is" << std::endl;
    std::cout << left(0, 0) << std::endl;
    for (size_t i = 0; i < std::get<0>(dimensions); ++i)
      for (size_t j = 0; j < std::get<1>(dimensions); ++j)
        result(i, j) = op(left(i, j), right(i, j));
    return result;
  }
};
#endif
