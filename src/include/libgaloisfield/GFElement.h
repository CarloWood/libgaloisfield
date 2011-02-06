// libgaloisfield -- A small C++ library to play with finite fields.
//
//! @file GFElement.h This file contains the declaration of class GFElement.
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

#ifndef GFELEMENT_H
#define GFELEMENT_H

#ifndef USE_PCH
#endif

#include "libgaloisfield/GaloisField.h"

#ifdef CWDEBUG
#define FIELD_ASSERT(x) assert(x)
#endif

class GFElement {
  public:
    static unsigned long const characteristic = polynomial_type::characteristic;

  private:
    polynomial_type M_field_element;
    GaloisField const& M_field;

  public:
    // Construct the zero of Z/2Z[T]/F(T), where F(T) is the polynomial passed as argument 'modulo'.
    // modulo must be an irreducible polynomial over Z/2Z.
    GFElement(polynomial_type const& modulo) : M_field(GaloisField::get(modulo)) { }

    // Copy-constructor.
    GFElement(GFElement const& x) : M_field_element(x.M_field_element), M_field(x.M_field) { }

    // Construct the element f(T) of Z/2Z[T]/F(T), where F(T) is the polynomial passed as argument 'modulo', and f(T) is the polynomial passed as argument 'field_element'.
    GFElement(polynomial_type const& field_element, polynomial_type const& modulo) : M_field_element(field_element % modulo), M_field(GaloisField::get(modulo)) { }

    // Assign element x to this element.
    GFElement& operator=(GFElement const& x) { FIELD_ASSERT(&M_field == &x.M_field); M_field_element = x.M_field_element; return *this; }

  public:
    GFElement& operator+=(GFElement const& x) { FIELD_ASSERT(&M_field == &x.M_field); M_field_element += x.M_field_element; return *this; }
    friend GFElement operator+(GFElement const& x, GFElement const& y) { GFElement result(x); result += y; return result; }

    GFElement& operator-=(GFElement const& x) { FIELD_ASSERT(&M_field == &x.M_field); M_field_element -= x.M_field_element; return *this; }
    friend GFElement operator-(GFElement const& x, GFElement const& y) { GFElement result(x); result -= y; return result; }
    
    GFElement& operator*=(GFElement const& x) { FIELD_ASSERT(&M_field == &x.M_field); M_field_element *= x.M_field_element; M_field_element %= M_field.reduction_polynomial(); return *this; }
    friend GFElement operator*(GFElement const& x, GFElement const& y) { return GFElement(x.M_field_element * y.M_field_element, x.M_field.reduction_polynomial()); }

    GFElement& pow_characteristic(void) { M_field_element.pow_characteristic(); M_field_element %= M_field.reduction_polynomial(); return *this; }
    GFElement& pow(unsigned long n);

    // Return the smallest positive number n such that pow(n) = 1.
    unsigned long order(void) const;

    bool is_zero(void) const { return M_field_element.is_zero(); }
    bool is_one(void) const { return M_field_element.is_one(); }
    bool is_generator(void) const { return order() == M_field.q_minus_one(); }

    // Accessors.
    polynomial_type const& as_polynomial(void) const { return M_field_element; }
    GaloisField const& field(void) const { return M_field; }

    friend bool operator==(GFElement const& x, GFElement const& y) { return x.M_field_element == y.M_field_element; }
    friend bool operator!=(GFElement const& x, GFElement const& y) { return x.M_field_element != y.M_field_element; }

    // Iterate over all field elements.
    GFElement& operator++(void) { M_field_element.next(M_field.degree()); return *this; }
    GFElement operator++(int) { GFElement ret(*this); M_field_element.next(M_field.degree()); return ret; }
};

#endif	// GFELEMENT_H
