// libgaloisfield -- A small C++ library to play with finite fields.
//
//! @file PolynomialOverZ2.cc Table with irreducible polynomials over Z_2.
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

#include "libgaloisfield/config.h"

unsigned long irreducible_bits[max_degree] = {
	0x1,
	0x3,
	0x7,
	0xb,
	0x13,
	0x25,
	0x43,
	0x83,
	0x11b,
	0x203,
	0x409,
	0x805,
	0x1009,
	0x201b,
	0x4021,
	0x8003,
	0x1002b,
	0x20009,
	0x40009,
	0x80027,
	0x100009,
	0x200005,
	0x400003,
	0x800021,
	0x100001b,
	0x2000009,
	0x400001b,
	0x8000027,
	0x10000003,
	0x20000005,
	0x40000003,
	0x80000009,
	0x10000008d,
	0x200000401,
	0x400000081,
	0x800000005,
	0x1000000201,
	0x2000000053,
	0x4000000063,
	0x8000000011,
	0x10000000039,
	0x20000000009,
	0x40000000081,
	0x80000000059,
	0x100000000021,
	0x20000000001b,
	0x400000000003,
	0x800000000021,
	0x100000000002d,
	0x2000000000201,
	0x400000000001d,
	0x800000000004b,
	0x10000000000009,
	0x20000000000047,
	0x40000000000201,
	0x80000000000081,
	0x100000000000095,
	0x200000000000011,
	0x400000000080001,
	0x800000000000095,
	0x1000000000000003,
	0x2000000000000027,
	0x4000000020000001,
	0x8000000000000003
};
