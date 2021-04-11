#if !defined(matrix_expression_hpp)
#define matrix_expression_hpp

#include <cstddef>
#include <tuple>
#include <iostream>
#include <boost/numeric/ublas/matrix/indexer.hpp>

template <typename T> class matrix;
template <typename T, class exp_type, class indexer1, class indexer2>
class submatrix;

template <typename T, class derived_type> class matrix_expression {
public:
  static constexpr bool is_assignable()
  {
    return derived_type::is_assignable();
  }
  T operator()(size_t i, size_t j) const
  {
    // std::cout << "matrix_expression point expression" << std::endl;
    return static_cast<const derived_type&>(*this)(i, j);
  }

  T& operator()(size_t i, size_t j)
  {
    // if (is_assignable())
    return static_cast<derived_type&>(*this)(i, j);
  }
  matrix<T> eval() const
  {
    return static_cast<const derived_type&>(*this).eval();
  };
  std::tuple<size_t, size_t> size() const
  {
    return static_cast<const derived_type&>(*this).size();
  }

  // definition in submatrix.hpp
  template <class indexer1, class indexer2>
  auto operator()(indexer1 ind1, indexer2 ind2) const
  {
    return static_cast<const derived_type&>(*this)(ind1, ind2);
  }
};

#endif
