// boolean.hpp                                                        -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef INCLUDED_SMD_STREAMS_BOOLEAN
#define INCLUDED_SMD_STREAMS_BOOLEAN

namespace smd {
namespace streams {

/*
    data Bool
      = True
      | False

Church, Scott:

    true  = λt f . t
    false = λt f . f

    and = λa b . a b a
    or  = λa b . a a b
    not = λa . a false true
*/

inline constexpr auto tru = []() { return [](auto t, auto f) { return t; }; };
inline constexpr auto fls = []() { return [](auto t, auto f) { return f; }; };

inline constexpr auto And = [](auto a, auto b) { return a(b, a); };
inline constexpr auto Or = [](auto a, auto b) { return a(a, b); };
inline constexpr auto Not = [](auto a) { return a(fls(), tru()); };

inline constexpr auto toBool = [](auto b) { return b(true, false); };

} // namespace streams
} // namespace smd

#endif
