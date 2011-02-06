#include <fstream>
#include <iostream>
#include <cctype>
#include <vector>
#include <utility>
#include <cassert>
#include <cstdlib>
#include <algorithm>

int const max_degree = 64;

using std::cout;
using std::cerr;
using std::endl;

// This file generates the table of irreducible_bits.cc.

struct poly {
  unsigned int m;
  unsigned int k;
  unsigned int k1;
  unsigned int k2;
  poly(unsigned int _m, unsigned int _k, unsigned int _k1 = 0, unsigned int _k2 = 0) : m(_m), k(_k), k1(_k1), k2(_k2) { }
};

bool operator<(poly const& p1, poly const& p2) { return p1.m < p2.m; }

int main(int argc, char* argv[])
{
  std::ifstream trinomials;
  if (argc == 2)
    trinomials.open((std::string(argv[1]) + "/TRINOMIALS").c_str());   
 
  if (argc != 2 || !trinomials)
  {
    cerr << "Usage: " << argv[0] << " pathto/TRINOMIALS" << endl;
    return 1;
  }

  unsigned int m = 0;
  unsigned int k = 0;	// Initialize to avoid compiler warning.

  std::vector<poly> mk;

  std::string line;
  while(getline(trinomials, line))
  {
    int pos = 0;
    while(std::isdigit(line[pos]))
      ++pos;
    if (pos == 0 || !std::isspace(line[pos]))
      continue;
    unsigned int next_m = atoi(line.data());
    while(std::isspace(line[pos]))
      ++pos;
    if (!std::isdigit(line[pos]))
      continue;
    unsigned int next_k = atoi(line.data() + pos);
    if (next_m != m)
    {
      if (m >= 2)
	mk.push_back(poly(m, k));
      k = 0;
    }
    m = next_m;
    if (k == 0 || (k < 8 * sizeof(unsigned long) && next_k > 8 * sizeof(unsigned long)))
      k = next_k;
  }
  mk.push_back(poly(m, k));
  trinomials.close();

  std::ifstream pentanomials;
  if (argc == 2)
    pentanomials.open((std::string(argv[1]) + "/PENTANOMIALS").c_str());   

  unsigned int k1, k2;

  while(getline(pentanomials, line))
  {
    if (!std::isdigit(line[0]))
      continue;
    int pos = 0;
    for (;;)
    {
      m = atoi(line.data() + pos);
      while(std::isdigit(line[pos]))
	++pos;
      assert(line[pos] == ',');
      ++pos;
      k = atoi(line.data() + pos);
      k1 = k2 = 0;
      while(std::isdigit(line[pos]))
	++pos;
      if (line[pos] == ',')
      {
        ++pos;
	k1 = atoi(line.data() + pos);
	while(std::isdigit(line[pos]))
	  ++pos;
	assert(line[pos] == ',');
        ++pos;
	k2 = atoi(line.data() + pos);
	while(std::isdigit(line[pos]))
	  ++pos;
        mk.push_back(poly(m, k, k1, k2));
      }
      else if (m >= 1200)
        mk.push_back(poly(m, k));
      if (line[pos] == 0)
	break;
      assert(line[pos] == ' ');
      ++pos;
    }
  }
  pentanomials.close();

  std::sort(mk.begin(), mk.end());
  // Sanity check.
  unsigned int next = 2;
  for (std::vector<poly>::iterator iter = mk.begin(); iter != mk.end(); ++iter)
  {
    if (iter->m != next)
    {
      cerr << "Unexpected: " << iter->m << endl;
      exit(1);
    }
    ++next;
  }
  assert(mk.size() == 9999);
 
  cout <<
"// libgaloisfield -- A small C++ library to play with finite fields.\n"
"//\n"
"//! @file irreducible_bits.cc Table with irreducible polynomials over Z_2.\n"
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
"unsigned long irreducible_bits[max_degree] = {\n\t0x1UL,\n\t0x3UL,\n";

  int count = 2;
  for (std::vector<poly>::iterator iter = mk.begin(); iter != mk.end(); ++iter)
  {
    unsigned long val = 1UL << iter->m;
    val |= 1UL << iter->k;
    if (iter->k1 > 0)
    {
      val |= 1UL << iter->k1;
      val |= 1UL << iter->k2;
    }
    val |= 1UL;
    cout << "\t0x" << std::hex << val << "UL";
    if (++count == max_degree)
      break;
    cout << ",\n";
  }

  cout << "\n};\n";

  return 0;
}
