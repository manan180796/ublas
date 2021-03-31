#if !defined(matrix_hpp)
#define matrix_hpp


#include <vector>
#include <stdexcept>
#include <ostream>
#include <tuple>
#include <cstddef>
#include <boost/numeric/ublas/matrix/matrix_expression.hpp>

template <typename T> class matrix : public matrix_expression<T, matrix<T>> {
  std::vector<T> data;
  std::tuple<size_t, size_t> dimensions;

public:
  matrix(std::tuple<size_t, size_t> dimensions, const T& value)
    : dimensions(dimensions)
    , data(std::get<0>(dimensions) * std::get<1>(dimensions), value)
  {
  }
  matrix(std::tuple<size_t, size_t> dimensions)
    : dimensions(dimensions)
    , data(std::get<0>(dimensions) * std::get<1>(dimensions))
  {
  }
  template <typename derived_type>
  matrix(const matrix_expression<T, derived_type>& m)
    : matrix(m.eval())
  {
  }

  const T& at(size_t i, size_t j) const
  {
    auto [rows, columns] = dimensions;
    if (i >= rows || j >= columns)
      throw std::out_of_range("indices are out of range");
    return data[i * columns + j];
  }
  const T& operator()(size_t i, size_t j) const
  {
    auto [rows, columns] = dimensions;
    return data[i * columns + j];
  }

  T& at(size_t i, size_t j)
  {
    auto [rows, columns] = dimensions;
    if (i >= rows || j >= columns)
      throw std::out_of_range("indices are out of range");
    return data[i * columns + j];
  }
  T& operator()(size_t i, size_t j)
  {
    return data[i * std::get<1>(dimensions) + j];
  }

  T& at(size_t i) { return data.at(i); }
  T& operator[](size_t i) { return data[i]; }
  const T& at(size_t i) const { return data.at(i); }
  const T& operator[](size_t i) const { return data[i]; }


  matrix<T> eval() const
  {
    matrix<T> copy = (*this);
    return copy;
  }


  std::tuple<size_t, size_t> size() const { return dimensions; }
};

template <typename T> matrix<T> zeros(size_t rows, size_t columns)
{
  return matrix<T>({rows, columns}, 0);
}

template <typename T>
std::ostream& operator<<(std::ostream& cout, const matrix<T>& m)
{
  size_t rows    = 0;
  size_t columns = 0;

  std::tie(rows, columns) = m.size();

  cout << rows << " X " << columns << "\n";
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < columns; ++j) cout << m(i, j) << "\t";
    cout << std::endl;
  }
  return cout;
}
#endif
