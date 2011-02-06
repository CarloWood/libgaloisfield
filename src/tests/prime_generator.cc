#include <iostream>
#include "libgaloisfield/config.h"
#include "libgaloisfield/Prime.h"
#include "debug_ostream_operators.h"

int main()
{
  int i = 0;
  unsigned long sum = 0;
  Prime p;
  for (; i < 100000 && p < 1299721; ++p, ++i)
  {
    sum += p;
    std::cout << p << std::endl;
  }
  assert(p == 1299721);
  assert(sum == 62260698721UL);

  std::cout << "Success!\n";
}
