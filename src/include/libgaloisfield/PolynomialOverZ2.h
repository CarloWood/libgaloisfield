// libgaloisfield -- A small C++ library to play with finite fields.
//
//! @file PolynomialOverZ2.h This file contains the declaration of class PolynomialOverZ2.
//
// Copyright (C) 2011, by
// 
// Carlo Wood, Run on IRC <carlo@alinoe.com>
// RSA-1024 0x624ACAD5 1997-01-26                    Sign & Encrypt
// Fingerprint16 = 32 EC A7 B6 AC DB 65 A6  F6 F6 55 DD 1C DC FF 61
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef POLYNOMIALOVERZ2_H
#define POLYNOMIALOVERZ2_H

#ifndef USE_PCH
#include <bitset>
#include <cassert>
#endif

#include "libgaloisfield/bithacks.h"
#include "config.h"

extern unsigned long irreducible_bits[max_degree];

template<unsigned int max_degree>
class PolynomialOverZ2 {
  public:
    static unsigned long const characteristic = 2;

  private:
    int M_degree;				// Or -1 when zero.
    std::bitset<max_degree> M_coefficients;

  public:
    // Construct a polynomial over Z_2 and set it to 0.
    PolynomialOverZ2(void) : M_degree(-1) { }
    // Construct an arbitrary polynomial over Z_2.
    explicit PolynomialOverZ2(unsigned long bits) : M_coefficients(bits) { M_degree = bits ? log2(bits) : -1; }
    // Construct an irreducible polynomial over Z_2 of degree `degree'.
    PolynomialOverZ2(int degree) : M_degree(degree), M_coefficients(irreducible_bits[degree]) { }

    void pow_characteristic(void);
    void reset(void) { M_coefficients.reset(); M_degree = -1; }
    void next(int degree);

    std::bitset<max_degree> const& as_bitset(void) const { return M_coefficients; }

    bool is_zero(void) const { return M_degree == -1; }
    bool is_one(void) const { return M_degree == 0; }
    int degree(void) const { return M_degree; }

    PolynomialOverZ2& operator+=(PolynomialOverZ2 const& pol);
    template<unsigned int md> friend PolynomialOverZ2<md> operator+(PolynomialOverZ2<md> const& pol1, PolynomialOverZ2<md> const& pol2) { PolynomialOverZ2 tmp(pol1); tmp += pol2; return tmp; }

    PolynomialOverZ2& operator*=(PolynomialOverZ2 const& pol) { if (&pol == this) { pow_characteristic(); return *this; } PolynomialOverZ2 tmp(*this * pol); return *this = tmp; }
    template<unsigned int md> friend PolynomialOverZ2<md> operator*(PolynomialOverZ2<md> const& pol1, PolynomialOverZ2<md> const& pol2);

    PolynomialOverZ2& operator-=(PolynomialOverZ2 const& pol) { return operator+=(pol); }
    template<unsigned int md> friend PolynomialOverZ2<md> operator-(PolynomialOverZ2<md> const& pol1, PolynomialOverZ2<md> const& pol2) { PolynomialOverZ2 tmp(pol1); tmp += pol2; return tmp; }

    PolynomialOverZ2& operator%=(PolynomialOverZ2 const& pol);
    template<unsigned int md> friend PolynomialOverZ2<md> operator%(PolynomialOverZ2<md> const& pol1, PolynomialOverZ2<md> const& pol2) { PolynomialOverZ2 tmp(pol1); tmp %= pol2; return tmp; }

    template<unsigned int md> friend PolynomialOverZ2<md> gcd(PolynomialOverZ2<md> const& pol1, PolynomialOverZ2<md> const& pol2);

    friend bool operator==(PolynomialOverZ2 const& pol1, PolynomialOverZ2 const& pol2) { return pol1.M_coefficients == pol2.M_coefficients; }
    friend bool operator!=(PolynomialOverZ2 const& pol1, PolynomialOverZ2 const& pol2) { return pol1.M_coefficients != pol2.M_coefficients; }

    static bool is_less(PolynomialOverZ2 const& pol1, PolynomialOverZ2 const& pol2) { return pol1.M_coefficients.to_ulong() < pol2.M_coefficients.to_ulong(); }
};

template<unsigned int max_degree>
PolynomialOverZ2<max_degree>& PolynomialOverZ2<max_degree>::operator+=(PolynomialOverZ2<max_degree> const& pol)
{
  M_coefficients ^= pol.M_coefficients;
  if (M_degree < pol.M_degree)
    M_degree = pol.M_degree;
  else if (M_degree == pol.M_degree)
    while(--M_degree >= 0 && !M_coefficients[M_degree]);
  return *this;
}

template<unsigned int max_degree>
PolynomialOverZ2<max_degree> operator*(PolynomialOverZ2<max_degree> const& pol1, PolynomialOverZ2<max_degree> const& pol2)
{
  PolynomialOverZ2<max_degree> result;
  if (pol1.M_degree >= 0 && pol2.M_degree >= 0)
  {
    result.M_degree = pol1.M_degree + pol2.M_degree;
    assert((unsigned int)result.M_degree < max_degree);
    for (int d = 0; d <= pol1.M_degree; ++d)
      if (pol1.M_coefficients[d])
	result.M_coefficients ^= pol2.M_coefficients << d;
  }
  return result;
}

template<unsigned int max_degree>
void PolynomialOverZ2<max_degree>::pow_characteristic(void)
{
  if (M_degree <= 1)
  {
    if (M_degree == 1)
    {
      M_coefficients.set(2);
      M_coefficients.reset(1);
      M_degree = 2;
    }
    return;
  }
  int d = M_degree;
  M_degree *= 2;
  assert((unsigned int)M_degree < max_degree);
  int dd = M_degree;
  M_coefficients.set(dd);
  while(--d >= 0)
  {
    M_coefficients.set(--dd, false);
    M_coefficients.set(--dd, M_coefficients[d]);
  }
}

template<unsigned int max_degree>
PolynomialOverZ2<max_degree>& PolynomialOverZ2<max_degree>::operator%=(PolynomialOverZ2<max_degree> const& pol)
{
  assert(pol.M_degree >= 0);
  int shift = M_degree - pol.M_degree;
  if (shift < 0)
    return *this;
  std::bitset<max_degree> tmp(pol.as_bitset());
  tmp <<= shift;
  for(;;)
  {
    M_coefficients ^= tmp;
    while(--M_degree >= 0 && !M_coefficients[M_degree]);
    int newshift = M_degree - pol.M_degree;
    if (newshift < 0)
      break;
    tmp >>= shift - newshift;
    shift = newshift;
  }
  return *this;
}

template<unsigned int md>
PolynomialOverZ2<md> gcd(PolynomialOverZ2<md> const& pol1, PolynomialOverZ2<md> const& pol2)
{
  PolynomialOverZ2<md> tmp1(pol1);
  PolynomialOverZ2<md> tmp2(pol2);
  PolynomialOverZ2<md>* x = &tmp1;
  PolynomialOverZ2<md>* y = &tmp2;
  do
  {
    if (x->M_degree > y->M_degree)
      std::swap(x ,y);
    *y %= *x;
  }
  while (!y->is_zero());
  return *x;
}

template<unsigned int max_degree>
void PolynomialOverZ2<max_degree>::next(int degree)
{
  unsigned long const mask = (degree == sizeof(unsigned long) * 8) ? (unsigned long)-1 : (1UL << degree) - 1;
  unsigned long const val = (M_coefficients.to_ulong() + 1) & mask;
  if (!val)
    reset();
  else
  {
    M_coefficients = val;
    if (M_coefficients[M_degree + 1])
      ++M_degree;
  }
}

#endif	// POLYNOMIALOVERZ2_H
