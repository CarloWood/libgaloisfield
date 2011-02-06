#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

#include <libgaloisfield/config.h>
#include <libgaloisfield/Prime.h>

using std::cout;

// This file generates the table of factorized.cc.

static unsigned long const mersenne_bits =
    1UL << 2 |
    1UL << 3 |
    1UL << 5 |
    1UL << 7 |
    1UL << 13 |
    1UL << 17 |
    1UL << 19 |
    1UL << 31 |
    1UL << 61;

static bool is_mersenne(unsigned int m)
{
  return (1UL << m) & mersenne_bits;
}

static void add_factor(std::vector<unsigned long>& output, unsigned long p, unsigned long& val)
{
  output.push_back(p);
  val /= p;
}

int main(void)
{
  size_t table1_size = 0;
  int table1_offset[max_degree + 1];
  std::stringstream table1;
  unsigned int m = 0;
  for(;;)
  {
    std::vector<unsigned long> output;
    unsigned long val;
    if (m < sizeof(unsigned long) * 8)
      val = (1UL << m) - 1;
    else
    {
      assert(m == sizeof(unsigned long) * 8);
      val = -1;
    }
    table1 << "  ";
    if (!is_mersenne(m))
    {
      if (m == 49)
	add_factor(output, 4432676798593, val);
      else if (m == 59)
	add_factor(output, 3203431780337, val);
      else if (m == 62)
      {
	add_factor(output, 715827883, val);
	add_factor(output, 2147483647, val);
      }
      unsigned long max_factor = sqrt(val) + 1;
      for (Prime p; p <= max_factor; ++p)
      {
	while (val % p == 0)
	{
	  add_factor(output, p, val);
	  max_factor = sqrt(val) + 1;
	  if (val == 1)
	    break;
	}
      }
    }
    if (val > 1)
      add_factor(output, val, val);
    std::sort(output.begin(), output.end());
    table1_offset[m] = table1_size;
    int multiplicity = 1;
    unsigned long last_factor = 0;
    int number_of_distinct_primes = 0;
    for (std::vector<unsigned long>::iterator iter = output.begin(); iter != output.end(); ++iter)
    {
      if (last_factor != *iter)
	++number_of_distinct_primes;
      last_factor = *iter;
    }
    table1 << number_of_distinct_primes << ", ";
    ++table1_size;
    last_factor = 0;
    for (std::vector<unsigned long>::iterator iter = output.begin(); iter != output.end(); ++iter)
    {
      if (last_factor == *iter)
	++multiplicity;
      else
      {
	if (last_factor != 0)
	{
	  table1 << last_factor << ", " << multiplicity << ", ";
	  table1_size += 2;
	}
	multiplicity = 1;
	last_factor = *iter;
      }
    }
    table1 << last_factor << ", " << multiplicity;
    table1_size += 2;
    if (m == max_degree)
      break;
    table1 << ",\n";
    ++m;
  }

  cout <<
    "// libgaloisfield -- A small C++ library to play with finite fields.\n"
    "//\n"
    "//! @file factorized.cc Table with factors of 2^m - 1.\n"
    "//\n"
    "// Copyright (C) 2011, by\n"
    "//\n"
    "// Carlo Wood, Run on IRC <carlo@alinoe.com>\n"
    "// RSA-1024 0x624ACAD5 1997-01-26                    Sign & Encrypt\n"
    "// Fingerprint16 = 32 EC A7 B6 AC DB 65 A6  F6 F6 55 DD 1C DC FF 61\n"
    "//\n"
    "// This program is free software: you can redistribute it and/or modify\n"
    "// it under the terms of the GNU General Public License as published by\n"
    "// the Free Software Foundation, either version 3 of the License, or\n"
    "// (at your option) any later version.\n"
    "//\n"
    "// This program is distributed in the hope that it will be useful,\n"
    "// but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
    "// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
    "// GNU General Public License for more details.\n"
    "//\n"
    "// You should have received a copy of the GNU General Public License\n"
    "// along with this program.  If not, see <http://www.gnu.org/licenses/>.\n"
    "\n"
    "#include <libgaloisfield/config.h>\n"
    "\n"
    "static unsigned long bulk_data[" << table1_size << "] = {\n";
  cout << table1.str() << '\n';
  cout <<
    "};\n"
    "\n"
    "unsigned long* factorized[max_degree + 1] = {\n";
  for (unsigned int m = 0; m <= max_degree; ++m)
    cout << "  bulk_data + " << table1_offset[m] << ",\n";
  cout <<
    "};\n";

  return 0;
}
