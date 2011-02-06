// libgaloisfield -- A small C++ library to play with finite fields.
//
//! @file GaloisField.h This file contains the declaration of class GaloisField.
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

#ifndef GALOISFIELD_H
#define GALOISFIELD_H

#ifndef USE_PCH
#include <map>
#endif

#include "libgaloisfield/config.h"

class GaloisField {
  public:
    static unsigned long const characteristic = polynomial_type::characteristic;

  private:
    struct PolyCompare { bool operator()(polynomial_type const& pol1, polynomial_type const& pol2) const { return polynomial_type::is_less(pol1, pol2); } };
    typedef std::map<polynomial_type, GaloisField, PolyCompare> S_fields_type;

    polynomial_type const M_modulo;
    static S_fields_type S_fields;

  private:
    // Construct a field Z/pZ[T]/F(T), where p is the characteristic and F(T) the irreducible polynomial passed as argument 'modulo'.
    GaloisField(polynomial_type const& modulo) : M_modulo(modulo) { }

  public:
    // Accessor.
    polynomial_type const& reduction_polynomial(void) const { return M_modulo; }

    // Return the dimension of the field as vector space over Z/pZ, where p is the characteristic.
    unsigned int degree(void) const __attribute__((const)) { return M_modulo.degree(); }
    // Return the order (size) of the field.
    inline unsigned long q(void) const __attribute__((const));
    // Return the order of the field minus one.
    inline unsigned long q_minus_one(void) const __attribute__((const));

    // Return a reference to a unique instantiation of a field with reduction polynomial 'modulo'.
    static GaloisField const& get(polynomial_type const& modulo) __attribute__((const));
};

unsigned long GaloisField::q(void) const
{
  int const m = M_modulo.degree();
  // FIXME
  //if (characteristic != 2)
  //  return characteristic to the power m;
  return 1UL << m;
}

unsigned long GaloisField::q_minus_one(void) const
{
  int const m = M_modulo.degree();
  // FIXME
  //if (characteristic != 2)
  //  return characteristic to the power m - 1;
  return (m == sizeof(unsigned long) * 8) ? (unsigned long)-1 : (1UL << m) - 1;
}

#endif	// GALOISFIELD_H
