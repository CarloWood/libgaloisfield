#include "libgaloisfield/GFElement.h"
#include "debug_ostream_operators.h"

int main()
{
  for (int m = 1; m <= 32; ++m)
  {
    polynomial_type irreducible_polynomial(m);
    polynomial_type polynomial(0x2UL);
    GFElement x(polynomial, irreducible_polynomial);
    for (int i = 0; i < m; ++i)
      x.pow_characteristic();
    assert(x == GFElement(polynomial, irreducible_polynomial));
  }

  for (int m = 1; m <= 32; ++m)
  {
    polynomial_type irreducible_polynomial(m);
    GFElement one(polynomial_type(1UL), irreducible_polynomial);	// 1
    GFElement xn(one);
    GFElement x(polynomial_type(2UL), irreducible_polynomial);	// t
    for (int n = 1; n < 10000; ++n)
    {
      xn *= x;
      assert(n % ((1UL << m) - 1) != 0 || xn == one);
      GFElement ypow(x);
      ypow.pow(n);
      assert(xn == ypow);
    }
  }

  std::cout << "Success!\n";
}
