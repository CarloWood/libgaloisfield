#include "libgaloisfield/GFElement.h"
#include "debug_ostream_operators.h"

int main()
{
  for (int m = 1; m <= 32; ++m)
  {
    polynomial_type irreducible_polynomial(m);
    GFElement const t(polynomial_type(2UL), irreducible_polynomial);
    unsigned int count = 10000;
    char const* const number = (t.field().q_minus_one() < count) ? "all" : "10,000";
    std::cout << "Checking the Frobenius order of " << number << " elements of GF(" << polynomial_type::characteristic << "^" << m << ")..." << std::flush;
    for (GFElement x = t; !x.is_zero() && count; ++x, --count)
    {
      int n = 0;
      GFElement xpn = x;
      do
      {
	++n;
	xpn.pow_characteristic();
      }
      while (xpn != x);
      // The Frobenius order of t is always equal to the degree of the field.
      // These are the m roots of the irreducial polynomail.
      assert(n == m || x != t);
      // Any Frobenius order must be a divisior of the field.
      assert(m % n == 0);
      // All generators have Frobenius order equal to the degree of the field.
      assert(n == m || !x.is_generator());
    }
    std::cout << " OK!" << std::endl;
  }
  std::cout << "Success!\n";
}
