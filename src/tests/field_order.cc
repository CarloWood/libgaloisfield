#include "libgaloisfield/GFElement.h"
#include "debug_ostream_operators.h"

int main()
{
  for (int m = 1; m <= 12; ++m)
  {
    polynomial_type irreducible_polynomial(m);
    //GFElement const one(polynomial_type(1UL), irreducible_polynomial);
    GFElement const t(polynomial_type(2UL), irreducible_polynomial);
    std::cout << "Checking the order of all elements of GF(" << polynomial_type::characteristic << "^" << m << ") brute force..." << std::flush;
    for (GFElement x = t; !x.is_zero(); ++x)
    {
      // Find the order the brute force way.
      unsigned int n = 1;
      GFElement xn = x;
      while (!xn.is_one())
      {
	++n;
	xn *= x;
      }
      assert(n == x.order());
    }
    std::cout << " OK!" << std::endl;
  }
  std::cout << "Success!\n";
}
