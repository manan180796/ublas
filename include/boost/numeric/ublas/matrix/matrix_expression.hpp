#if !defined(matrix_expression_hpp)
#define matrix_expression_hpp

#include <cstddef>
#include <tuple>
#include <iostream>
template <typename T> class matrix;

template <typename T, typename derived_type> class matrix_expression {
public:
  T operator()(size_t i, size_t j) const
  {
    return static_cast<const derived_type&>(*this)(i, j);
  }


  T operator[](size_t i) const
  {
    return static_cast<const derived_type&>(*this)[i];
  }


  matrix<T> eval() const
  {
    return static_cast<const derived_type&>(*this).eval();
  };
  std::tuple<size_t, size_t> size() const
  {
    return static_cast<const derived_type&>(*this).size();
  }
};
#endif
