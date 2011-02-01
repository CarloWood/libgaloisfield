// libgaloisfield -- A small C++ library to play with finite fields.
//
//! @file bithacks.h Bit fiddling utilities.
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

#ifndef BITHACKS_H
#define BITHACKS_H

#ifndef USE_PCH
#include <endian.h>
#endif

// Convert the size of a linked list to it's 'size class':
// this function returns log2(val) - 1.
// See http://graphics.stanford.edu/~seander/bithacks.html#IntegerLogIEEE64Float for the used magic.
inline unsigned int log2(uint32_t val)
{
  union { uint32_t u[2]; double d; } t;
  t.u[__FLOAT_WORD_ORDER == __LITTLE_ENDIAN] = 0x43300000;
  t.u[__FLOAT_WORD_ORDER != __LITTLE_ENDIAN] = val;
  t.d -= 4503599627370496.0;
  return (t.u[__FLOAT_WORD_ORDER == __LITTLE_ENDIAN] >> 20) - 0x3ff;
}

inline unsigned int log2(uint64_t val)
{
  union { uint32_t u[2]; uint64_t v; } t;
  t.v = val;
  return t.u[__BYTE_ORDER == __LITTLE_ENDIAN] ? log2(t.u[__BYTE_ORDER == __LITTLE_ENDIAN]) + 32 : log2(t.u[__BYTE_ORDER != __LITTLE_ENDIAN]);
}

#endif // BITHACKS_H
