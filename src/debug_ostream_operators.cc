// libgaloisfield -- A small C++ library to play with finite fields.
//
//! @file debug_ostream_operators.cc
//! @brief This file contains the definition of debug serializers.
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
#include "sys.h"        // Put this outside the #ifdef CWDEBUG .. #endif in order
                        // to force recompilation after the configuration changed.
#endif

#include "libgaloisfield/config.h"
#include "libgaloisfield/PolynomialOverZ2.h"
#include "libgaloisfield/GFElement.h"

#ifdef CWDEBUG

#ifndef USE_PCH
#include <iostream>
#include "debug.h"
#include <libcwd/buf2str.h>
#include <libcwd/cwprint.h>
#endif

//! For debugging purposes. Write a timeval to \a os.
std::ostream& operator<<(std::ostream& os, timeval const& time)
{
  return os << "{tv_sec:" << time.tv_sec << ", tv_usec:" << time.tv_usec << '}';
}

#endif // CWDEBUG

std::ostream& operator<<(std::ostream& os, PolynomialOverZ2<max_degree> const& polynomial)
{
  if (polynomial.is_zero())
    return os << "0";
  std::bitset<max_degree> const& bits = polynomial.as_bitset();
  bool first = true;
  for (int d = polynomial.degree(); d >= 0; --d)
  {
    if (bits[d])
    {
      if (first)
	first = false;
      else
	os << " + ";
      if (d == 0)
	os << "1";
      else if (d == 1)
	os << "t";
      else
	os << "t^" << d;
    }
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, GFElement const& field_element)
{
  os << field_element.as_polynomial();
  return os;
}

