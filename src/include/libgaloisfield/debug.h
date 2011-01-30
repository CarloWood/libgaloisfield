// libgaloisfield -- A small C++ library to play with finite fields.
//
//! @file debug.h
//! @brief This file contains the declaration of debug related macros, objects and functions that are part of the API of the library.
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

#ifndef LIBGALOISFIELD_DEBUG_H
#define LIBGALOISFIELD_DEBUG_H

#ifdef CWDEBUG
#include <libcwd/libraries_debug.h>

namespace libgaloisfield {
 namespace channels {
   namespace dc {
     using namespace libcwd::channels::dc;
     //extern libcwd::channel_ct custom;
     // Add new channels here...
   }
 }
}
#endif // CWDEBUG

// Define private debug output macros for use in header files of the library,
// there is no reason to do this for normal applications.
// We use a literal libgaloisfield::channels here and not LIBCWD_DEBUGCHANNELS!
#define LibgaloisfieldDebug(STATEMENT...) LibcwDebug(libgaloisfield::channels, STATEMENT)
#define LibgaloisfieldDout(cntrl, data) LibcwDout(libgaloisfield::channels, libcwd::libcw_do, cntrl, data)
#define LibgaloisfieldDoutFatal(cntrl, data) LibcwDoutFatal(libgaloisfield::channels, libcwd::libcw_do, cntrl, data)
#define LibgaloisfieldForAllDebugChannels(STATEMENT...) LibcwdForAllDebugChannels(libgaloisfield::channels, STATEMENT)
#define LibgaloisfieldForAllDebugObjects(STATEMENT...) LibcwdForAllDebugObjects(libgaloisfield::channels, STATEMENT)

// All other macros might be used in header files of libgaloisfield, but need to be
// defined by the debug.h of the application that uses it.
// LIBGALOISFIELD_INTERNAL is defined when the library itself is being compiled.
#if !defined(Debug) && !defined(LIBGALOISFIELD_INTERNAL)
#error The application source file (.cc or .cpp) must use '#include "debug.h"' _before_ including the header file that it includes now, that led to this error.
#endif

#endif // LIBGALOISFIELD_DEBUG_H
