#if !defined(submatrix_hpp)
#define submatrix_hpp
#include <tuple>
#include <cstddef>
#include <boost/numeric/ublas/matrix/matrix_expression.hpp>
#include <boost/numeric/ublas/matrix/assignable_matrix.hpp>
#include <boost/numeric/ublas/matrix/indexer.hpp>


template <typename T, class exp_type, class indexer1, class indexer2>
class const_submatrix
  : public matrix_expression<T,
                             const_submatrix<T, exp_type, indexer1, indexer2>> {
  const matrix_expression<T, exp_type>& exp;
  const std::tuple<indexer1, indexer2> ind;

public:
  const_submatrix(const matrix_expression<T, exp_type>& exp,
                  std::tuple<indexer1, indexer2> ind)
    : exp(exp)
    , ind(ind)
  {
  }
  std::tuple<size_t, size_t> size() const
  {
    auto [ind1, ind2] = ind;
    return {ind1.size(), ind2.size()};
  }
  T operator()(size_t i, size_t j) const
  {
    auto [ind1, ind2] = ind;
    return exp(ind1(i), ind2(j));
  }
  matrix<T> eval() const
  {
    auto [ind1, ind2] = ind;
    // matrix<T> exp     = this->exp.eval();
    matrix<T> result(size());
    for (size_t i = 0; i < ind1.size(); ++i)
      for (size_t j = 0; j < ind2.size(); ++j)
        result(i, j) = exp(ind1(i), ind2(j));
    return result;
  }
  template <class internal_indexer1, class internal_indexer2>
  auto operator()(internal_indexer1 ind1, internal_indexer2 ind2) const
  {
    return const_submatrix<T,
                           const_submatrix<T, exp_type, indexer1, indexer2>,
                           internal_indexer1,
                           internal_indexer2>(*this, {ind1, ind2});
  }
};
template <typename T, class exp_type, class indexer1, class indexer2>
auto make_const_submatrix(const matrix_expression<T, exp_type>& exp,
                          indexer1 ind1,
                          indexer2 ind2)
{
  return const_submatrix<T, exp_type, indexer1, indexer2>(exp, {ind1, ind2});
}


template <typename T, class exp_type, class indexer1, class indexer2>
class submatrix
  : public assignable_expression<T,
                                 submatrix<T, exp_type, indexer1, indexer2>> {
  assignable_expression<T, exp_type>& exp;
  const std::tuple<indexer1, indexer2> ind;

public:
  submatrix(assignable_expression<T, exp_type>& exp,
            std::tuple<indexer1, indexer2> ind)
    : exp(exp)
    , ind(ind)
  {
  }

  std::tuple<size_t, size_t> size() const
  {
    auto [ind1, ind2] = ind;
    return {ind1.size(), ind2.size()};
  }
  T operator()(size_t i, size_t j) const
  {
    auto [ind1, ind2] = ind;
    return exp(ind1(i), ind2(j));
  }
  T& operator()(size_t i, size_t j)
  {
    auto [ind1, ind2] = ind;
    return exp(ind1(i), ind2(j));
  }
  matrix<T> eval() const
  {
    auto [ind1, ind2] = ind;
    // matrix<T> exp     = this->exp.eval();
    matrix<T> result(size());
    for (size_t i = 0; i < ind1.size(); ++i)
      for (size_t j = 0; j < ind2.size(); ++j)
        result(i, j) = exp(ind1(i), ind2(j));
    return result;
  }
  template <typename other_type>
  auto operator=(const matrix_expression<T, other_type>& other)
  {
    auto [ind1, ind2] = ind;
    for (size_t i = 0; i < ind1.size(); ++i)
      for (size_t j = 0; j < ind2.size(); ++j) { (*this)(i, j) = other(i, j); };
    *this;
  }
  auto operator=(const T& other)
  {
    auto [ind1, ind2] = ind;
    for (size_t i = 0; i < ind1.size(); ++i)
      for (size_t j = 0; j < ind2.size(); ++j) (*this)(i, j) = other;
    *this;
  }
  template <class internal_indexer1, class internal_indexer2>
  auto operator()(internal_indexer1 ind1, internal_indexer2 ind2)
  {
    return submatrix<T,
                     submatrix<T, exp_type, indexer1, indexer2>,
                     internal_indexer1,
                     internal_indexer2>(*this, {ind1, ind2});
  }
  template <class internal_indexer1, class internal_indexer2>
  auto operator()(internal_indexer1 ind1, internal_indexer2 ind2) const
  {
    return const_submatrix<T,
                           submatrix<T, exp_type, indexer1, indexer2>,
                           internal_indexer1,
                           internal_indexer2>(*this, {ind1, ind2});
  }
};
template <typename T, class exp_type, class indexer1, class indexer2>
auto make_submatrix(assignable_expression<T, exp_type>& exp,
                    indexer1 ind1,
                    indexer2 ind2)
{
  return submatrix<T, exp_type, indexer1, indexer2>(exp, {ind1, ind2});
}
#endif
