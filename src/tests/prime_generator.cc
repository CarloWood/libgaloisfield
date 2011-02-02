#include "libgaloisfield/config.h"
#include "debug_ostream_operators.h"
#include "Prime.h"

int main()
{
  Prime p;
  for (int i = 0; i < 100000; ++i)
    std::cout << p++ << std::endl;
}
