// smd/streams/maybe.hpp                                              -*-C++-*-
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


// 0e278f9f-4092-4c87-a751-43e3e04a9c27
inline constexpr auto nothing = []() {
  return [](auto n) { return [n](auto _) { return n(); }; };
};

inline constexpr auto just = [](auto x) {
  return [x](auto _) { return [x](auto j) { return j(x); }; };
};
// 0e278f9f-4092-4c87-a751-43e3e04a9c27 end

// inline constexpr auto nothing = []() {
//     return [](auto n, auto _) { return n(); };
// };

// inline constexpr auto just = [](auto x) {
//     return [x](auto _, auto j) { return j(x); };
// };


// 916b4ab3-1779-42fc-a912-022bd1bbb468
inline constexpr auto isNothing = [](auto m) {
  return m([]() { return true; })([](auto _) { return false; });
};
inline constexpr auto isJust = [](auto m) {
  return m([]() { return false; })([](auto _) { return true; });
};
inline constexpr auto fromJust = [](auto m) {
  return m([]() { std::abort(); })([](auto x) { return x; });
};
// 916b4ab3-1779-42fc-a912-022bd1bbb468 end


// 4fa184e0-691e-4068-9d6b-158338a51640
inline constexpr auto maybe = [](auto d) {
  return [d](auto f) {
    return [d, f](auto m) { return m([d]() { return d; })(f); };
  };
};
// 4fa184e0-691e-4068-9d6b-158338a51640 end
} // namespace streams
} // namespace smd

#endif
