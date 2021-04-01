#if !defined(unary_expression_hpp)
#define unary_expression_hpp

#include <boost/numeric/ublas/matrix/matrix.hpp>
#include <functional>
template <typename T, typename opand_type>
class point_unary_expression
  : public matrix_expression<T, point_unary_expression<T, opand_type>> {
  using op_type        = std::function<T(const opand_type&, size_t, size_t)>;
  using size_calc_type = std::function<std::tuple<size_t, size_t>(
    std::tuple<size_t, size_t>, std::tuple<size_t, size_t>)>;
  const opand_type& opand;
  const op_type op;
  const size_calc_type size_calc;

public:
  point_unary_expression(const opand_type& opand,
                         const op_type& op,
                         const size_calc_type& size_calc)
    : opand(opand)
    , op(op)
    , size_calc(size_calc)
  {
  }
  T operator()(std::size_t i, std::size_t j) const { return op(opand, i, j); }

  T operator[](std::size_t i) const
  {
    auto [rows, columns] = size();
    return op(opand, i / rows, i % columns);
  }
  matrix<T> eval() const
  {
    auto dimensions = size();
    matrix<T> result(dimensions);
    for (size_t i = 0; i < std::get<0>(dimensions); ++i)
      for (size_t j = 0; j < std::get<1>(dimensions); ++j)
        result(i, j) = op(opand, i, j);
    return result;
  }
  std::tuple<size_t, size_t> size() const { return size_calc(opand.size()); }
};
#endif
