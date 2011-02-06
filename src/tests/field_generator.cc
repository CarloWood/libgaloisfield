#include "libgaloisfield/GFElement.h"
#include "debug_ostream_operators.h"

// http://oeis.org/A053287
// Euler totient function of 2^n - 1.
unsigned long A053287[33] = {
  1, 2, 6, 8, 30, 36, 126, 128,
  432, 600, 1936, 1728, 8190, 10584, 27000, 32768,
  131070, 139968, 524286, 480000, 1778112, 2640704, 8210080, 6635520,
  32400000, 44717400, 113467392, 132765696, 533826432, 534600000, 2147483646, 2147483648,
  6963536448
};

int main()
{
  for (int m = 1; m <= 18; ++m)
  {
    polynomial_type irreducible_polynomial(m);
    GFElement const t(polynomial_type(2UL), irreducible_polynomial);
    unsigned int n = 0;
    for (GFElement x = t; !x.is_zero(); ++x)
    {
      if (x.is_generator())
      {
        if (++n == 1)
	  std::cout << "First generator of GF(" << polynomial_type::characteristic << "^" << m << "): " << x << std::flush;
      }
    }
    assert(n == A053287[m - 1]);
    std::cout << "; total number of generators: " << n << std::endl;
  }
  std::cout << "Success!\n";
}
