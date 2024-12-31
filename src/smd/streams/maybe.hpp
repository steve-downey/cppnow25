// maybe.hpp                                                          -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#ifndef INCLUDED_SMD_STREAMS_MAYBE
#define INCLUDED_SMD_STREAMS_MAYBE

#include <cstdlib>

namespace smd {
namespace streams {

// MAYBE
/*
nothing = λ. λn.λj.n
   just = λx.λn.λj.j x
*/

inline constexpr auto nothing = []() { return [](auto n) { return [n](auto _) { return n(); }; }; };

inline constexpr auto just = [](auto x) { return [x](auto _) { return [x](auto j) { return j(x); }; }; };

// inline constexpr auto nothing = []() {
//     return [](auto n, auto _) { return n(); };
// };

// inline constexpr auto just = [](auto x) {
//     return [x](auto _, auto j) { return j(x); };
// };

inline constexpr auto isNothing = [](auto m) { return m([]() { return true; })([](auto _) { return false; }); };
inline constexpr auto isJust    = [](auto m) { return m([]() { return false; })([](auto _) { return true; }); };
inline constexpr auto fromJust  = [](auto m) { return m([]() { std::abort(); })([](auto x) { return x; }); };
inline constexpr auto maybe     = [](auto d) {
    return [d](auto f) { return [d, f](auto m) { return m([d]() { return d; })(f); }; };
};
} // namespace streams
} // namespace smd

#endif
