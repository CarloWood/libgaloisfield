// libgaloisfield -- A small C++ library to play with finite fields.
//
//! @file GaloisField.cc This file contains the implementation of class GaloisField.
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

#include "libgaloisfield/GaloisField.h"

GaloisField::S_fields_type GaloisField::S_fields;

GaloisField const& GaloisField::get(polynomial_type const& modulo)
{
  S_fields_type::iterator iter = S_fields.find(modulo);
  if (iter == S_fields.end())
    iter = S_fields.insert(S_fields_type::value_type(modulo, GaloisField(modulo))).first;
  return iter->second;
}

