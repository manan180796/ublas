#if !defined(scalar_hpp)
#define scalar_hpp
#include <cstddef>
#include <iostream>
template <typename T> class scalar {
  const T value;

public:
  scalar(const T& value)
    : value(value)
  {
    std::cout << value << std::endl;
  }
  T operator()(size_t i, size_t j) const { return value; }
};

#endif
