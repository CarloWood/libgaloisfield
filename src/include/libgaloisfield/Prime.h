// libgaloisfield -- A small C++ library to play with finite fields.
//
//! @file Prime.h This file contains the declaration of class Prime.
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

#ifndef PRIME_H
#define PRIME_H

#ifndef USE_PCH
#include <vector>
#endif

typedef unsigned long prime_t;

class Prime {
  public:
    static std::vector<prime_t> S_primes;
    unsigned int M_index;
  
  public:
    Prime(void) : M_index(0) { S_primes.push_back(2); }
    Prime(Prime const& p) : M_index(p.M_index) { }
    Prime(unsigned int index) : M_index(index) { generate(M_index); }

    unsigned long as_ulong(void) const { return S_primes[M_index]; }
    operator prime_t() const { return S_primes[M_index]; }

    Prime& operator++(void) { ++M_index; generate(M_index); return *this; }
    Prime operator++(int) { generate(M_index + 1); return Prime(M_index++); }
    Prime& operator--(void) { --M_index; return *this; }
    Prime operator--(int) { return Prime(M_index--); }

  private:
    void generate(unsigned int index);
};

#endif	// PRIME_H
