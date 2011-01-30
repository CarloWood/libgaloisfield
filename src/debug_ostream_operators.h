// libgaloisfield -- A small C++ library to play with finite fields.
//
//! @file debug_ostream_operators.h
//! @brief This file contains the declaration of debug serializers.
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

#ifndef DEBUG_OSTREAM_OPERATORS_H
#define DEBUG_OSTREAM_OPERATORS_H

#ifdef CWDEBUG

#ifndef USE_PCH
#include <sys/time.h>
#include <iosfwd>                       // std::ostream&
#include <utility>                      // std::pair
#include <map>
#include <boost/shared_ptr.hpp>         // boost::shared_ptr
#include <boost/weak_ptr.hpp>           // boost::weak_ptr
#endif

struct timeval;

extern std::ostream& operator<<(std::ostream& os, timeval const& time);                         //!< Print debug info for timeval instance \a time.

#ifdef USE_LIBBOOST
//! Print debug info for boost::shared_ptr&lt;T&gt;.
template<typename T>
std::ostream& operator<<(std::ostream& os, boost::shared_ptr<T> const& data)
{
  os << "(boost::shared_ptr<" << libcwd::type_info_of<T>().demangled_name() << ">)({";
  if (data.get())
    os << *data;
  else
    os << "<NULL>";
  return os << "})";
}

//! Print debug info for boost::weak_ptr&lt;T&gt;.
template<typename T>
std::ostream& operator<<(std::ostream& os, boost::weak_ptr<T> const& data)
{
  return os << "(boost::weak_ptr<" << libcwd::type_info_of<T>().demangled_name() << ">)({ " << *boost::shared_ptr<T>(data) << "})";
}
#endif // USE_LIBBOOST

//! Print debug info for std::pair&lt;&gt; instance \a data.
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, std::pair<T1, T2> const& data)
{
  return os << "{first:" << data.first << ", second:" << data.second << '}';
}

//! Print a whole map.
template<typename T1, typename T2, typename T3>
std::ostream& operator<<(std::ostream& os, std::map<T1, T2, T3> const& data)
{
  os << "{map<" << libcwd::type_info_of<T1>().demangled_name() <<
      ", " << libcwd::type_info_of<T2>().demangled_name() <<
      ", " << libcwd::type_info_of<T3>().demangled_name() <<">:";
  typedef std::map<T1, T2, T3> map_type;
  for (typename map_type::const_iterator iter = data.begin(); iter != data.end(); ++iter)
    os << '{' << *iter << '}';
  return os << '}';
}

#endif // CWDEBUG
#endif // DEBUG_OSTREAM_OPERATORS_H
