#include "boost/numeric/ublas/matrix/matrix_expression.hpp"
#include <cstddef>
#if !defined(transpose_hpp)
#define transpose_hpp

#include <boost/numeric/ublas/matrix/matrix.hpp>

template <typename T, typename exp_type>
class Transpose : public matrix_expression<T, Transpose<T, exp_type>> {
  const exp_type& exp;

public:
  Transpose(const matrix_expression<T, exp_type>& exp)
    : exp(static_cast<const exp_type&>(exp))
  {
  }
  T operator()(size_t i, size_t j) const { return exp(j, i); }


  T operator[](size_t i) const
  {
    auto [rows, columns] = exp.size();

    size_t new_index = (i % rows) * columns + i / rows;

    return exp[new_index];
  }


  matrix<T> eval() const
  {
    auto [rows, columns] = exp.size();
    matrix<T> internal   = exp.eval();
    matrix<T> result({columns, rows});
    for (size_t i = 0; i < columns; ++i)
      for (size_t j = 0; j < rows; ++j) result(i, j) = internal(j, i);
    return result;
  };
  std::tuple<size_t, size_t> size() const
  {
    auto [rows, columns] = exp.size();
    return {columns, rows};
  }
};


#endif
