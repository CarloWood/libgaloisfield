// libgaloisfield -- A small C++ library to play with finite fields.
//
//! @file GFElement.cc This file contains the implementation of class GFElement.
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

#ifndef USE_PCH
#include "sys.h"
#endif

#include "libgaloisfield/GFElement.h"
#include "libgaloisfield/MultiLoop.h"
#include "debug_ostream_operators.h"

GFElement& GFElement::pow(unsigned long n)
{
  n %= M_field.q_minus_one();				// x^(2^m - 1) = 1, so do n modulo 2^m - 1.
  if (n == 0)
  {
    M_field_element = polynomial_type(1UL);
    return *this;
  }
  int frobs = 0;
  while(n % characteristic == 0)			// If n = k * characteristic^frobs, set n = k.
  {
    n /= characteristic;
    ++frobs;
  }
  GFElement poc(*this);				// Store this to the power 1.
  int delayed_frobs = 0;				// Times that we need to apply Frobenius.
  while((n /= characteristic))				// Move out processed bits.
  {
    ++delayed_frobs;
    if (n % characteristic != 0)
    {
      while(delayed_frobs)
      {
	poc.pow_characteristic();
	--delayed_frobs;
      }
      *this *= poc;
    }
  }
  while(frobs--)
    pow_characteristic();
  return *this;
}

extern unsigned long* factorized[max_degree + 1];

unsigned long GFElement::order(void) const
{
  int const m = M_field.degree();
  if (m < 2)
    return 1;
  unsigned long const q_minus_one = M_field.q_minus_one();
  unsigned long* factors = factorized[m];
  unsigned int number_of_distinct_primes = *factors++;
  if (number_of_distinct_primes == 1 && factors[1] == 1)				// Speed up for Mersenne primes.
    return q_minus_one;
  unsigned long exponent_vector[number_of_distinct_primes];				// The exponent up till and including current loop (as index).
  std::vector<GFElement> power_vector(number_of_distinct_primes, *this);		// A vector of GFElement objects with the right modulo set.
  // Initialize for *ml == 0 here instead of in the loop.
  // Note that power_vector[0] is already initialized.
  exponent_vector[0] = 1;
  for (MultiLoop ml(number_of_distinct_primes); !ml.finished(); ml.next_loop())		// One loop for each prime.
  {
    unsigned int const multiplicity = factors[*ml * 2 + 1];
    for(; ml() <= multiplicity; ++ml)							// Each loop runs from 0 to the maximum exponent of this prime.
    {
      if (ml() == 0)									// Did this loop just start?
      {
	// Loop *ml == 0 is already initialized.
	if (*ml)
	{
	  // We start with this prime to the power 0 (ml() == 0), so the current power and exponent are the same as those of the previous loop.
	  power_vector[*ml] = power_vector[*ml - 1];
	  exponent_vector[*ml] = exponent_vector[*ml - 1];
	}
      }
      else
      {
	// Raise 'power' (again) to the power 'prime'. If it is 1, we are done.
	unsigned long const prime = factors[*ml * 2];
	unsigned long& exponent(exponent_vector[*ml]);
	GFElement& power(power_vector[*ml]);
	if ((exponent *= prime) == q_minus_one || power.pow(prime).is_one())
	  return exponent;
      }
    }
  }
  return 0;
}

