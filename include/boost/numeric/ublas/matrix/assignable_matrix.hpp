#include <cstddef>
#if !defined(assignable_matrix_hpp)
#define assignable_matrix_hpp
#include <boost/numeric/ublas/matrix/matrix_expression.hpp>
template <typename T, class derived_type>
class assignable_expression
  : public matrix_expression<T, assignable_expression<T, derived_type>> {
public:
  T& operator()(size_t i, size_t j)
  {
    return static_cast<derived_type&>(*this)(i, j);
  }
  T operator()(size_t i, size_t j) const
  {
    return static_cast<const derived_type&>(*this)(i, j);
  }
  std::tuple<size_t, size_t> size() const
  {
    return static_cast<const derived_type&>(*this).size();
  }
  matrix<T> eval() const
  {
    return static_cast<const derived_type&>(*this).eval();
  }

  // definition in submatrix.hpp
  template <class indexer1, class indexer2>
  auto operator()(indexer1 ind1, indexer2 ind2)
  {
    return static_cast<derived_type&>(*this)(ind1, ind2);
  }
  template <class indexer1, class indexer2>
  auto operator()(indexer1 ind1, indexer2 ind2) const
  {
    return static_cast<const derived_type&>(*this)(ind1, ind2);
  }
};

#endif
