#include <cstddef>
#if !defined(matrix_multiplication_hpp)
#define matrix_multiplication_hpp

#include <tuple>
#include <boost/numeric/ublas/matrix/matrix.hpp>
#include <functional>

template <typename T, typename left_type, typename right_type>
class matrix_multiplication
  : public matrix_expression<T,
                             matrix_multiplication<T, left_type, right_type>> {
  const left_type& left;
  const right_type& right;

public:
  matrix_multiplication(const left_type& left, const right_type& right)
    : left(left)
    , right(right)
  {
  }
  T operator()(std::size_t i, std::size_t j) const
  {
    T result = 0;
    for (size_t k = 0; k < std::get<1>(left.size()); ++i) {
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
};

#endif
