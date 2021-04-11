#if !defined(indexer_hpp)
#define indexer_hpp
#include <cstddef>
#include <iostream>
struct end {
};

template <typename derived_type> class indexer {
public:
  size_t operator()(size_t index) const
  {
    return static_cast<const derived_type&>(*this)(index);
  }
  size_t size() const { return static_cast<const derived_type&>(*this).size(); }
};

class splice : public indexer<splice> {
  long long int start;
  long long int stop;
  long long int stride;

public:
  splice(long long int stop)
    : start(0)
    , stop(stop)
    , stride(1){};
  splice(long long int start, long long int stop)
    : start(start)
    , stop(stop)
    , stride(start < stop ? 1 : -1){};
  splice(long long int start, long long int stop, long long int stride)
    : start(start)
    , stop(stop)
    , stride(stride){};
  size_t size() const
  {
    if (stride > 0)
      return (stop - start + stride - 1) / stride;
    else
      return (stop - start + stride + 1) / stride;
  }
  size_t operator()(size_t index) const { return start + index * stride; }
};

// class splice

#endif
