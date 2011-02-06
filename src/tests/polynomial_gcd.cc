#include "libgaloisfield/config.h"
#include "debug_ostream_operators.h"

int main()
{
  polynomial_type c(0x34UL);
  polynomial_type x(0x1a39UL);
  polynomial_type y(0x7012bUL);

  polynomial_type cx = c * x;
  polynomial_type cy = c * y;
  polynomial_type q = gcd(cx, cy);

  polynomial_type r = gcd(x, y) * c;

  std::cout << "c                 = " << c << std::endl;
  std::cout << "x                 = " << x << std::endl;
  std::cout << "y                 = " << y << std::endl;
  std::cout << "c * x             = " << cx << std::endl;
  std::cout << "c * y             = " << cy << std::endl;
  std::cout << "gcd(c * x, c * y) = " << q << std::endl;
  std::cout << "c * gcd(x, y)     = " << r << std::endl;

  assert(q == r);
  std::cout << "Success!\n";
}
