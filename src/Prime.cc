// libgaloisfield -- A small C++ library to play with finite fields.
//
//! @file Prime.cc This file contains the implementation of class Prime.
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
#include <bitset>
#endif

#include "libgaloisfield/Prime.h"

std::vector<prime_t> Prime::S_primes;

static inline unsigned int prime_to_index(prime_t p) { return (p - 3) / 2; }
static inline prime_t index_to_prime(unsigned int i) { return i * 2 + 3; }

void Prime::generate(unsigned int index)
{
  while (S_primes.size() <= index)
  {
    // 2 and 3 need to be already there.
    if (S_primes.size() < 2)
    {
      if (S_primes.empty())
	S_primes.push_back(2);
      S_primes.push_back(3);
    }
    // Get the last prime in the table.
    prime_t last_prime = S_primes[S_primes.size() - 1];
    // Get the corresponding index.
    unsigned int last_index = prime_to_index(last_prime);
    // Prepare an inserter to add new primes to the table.
    std::back_insert_iterator<std::vector<prime_t> > inserter(std::back_inserter(S_primes));
    // Create a sieve of Eratosthenes.
    unsigned int const sieve_size = 1024;
    std::bitset<sieve_size> sieve;
    // The first bit of this sieve is actually last_index + 1.
    unsigned int index_offset = last_index + 1;
    // Fill the sieve with all previous primes.
    for (std::vector<prime_t>::iterator iter = S_primes.begin() + 1; iter != S_primes.end(); ++iter)
    {
      prime_t p = *iter;
      for (unsigned int index1 = prime_to_index(((last_prime - p + 1) / (2 * p) + 1) * 2 * p + p) - index_offset;
	   index1 < sieve_size; index1 += p)
	sieve[index1] = true;
    }
    for (unsigned int index1 = 0; index1 < sieve_size; ++index1)
    {
      if (!sieve[index1])
      {
	prime_t p = index_to_prime(index1 + index_offset);
	*inserter++ = p;
	for (unsigned int index2 = index1 + p; index2 < sieve_size; index2 += p)
	  sieve[index2] = true;
      }
    }
  }
}

