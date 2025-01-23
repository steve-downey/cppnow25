// pair.hpp                                                          -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef INCLUDED_SMD_STREAMS_PAIR
#define INCLUDED_SMD_STREAMS_PAIR

namespace smd {
namespace streams {

// PAIR

/*
    pair = λl r p. p l r
    fst = λp. p (λl r. l)
    snd = λp. p (λl r. r)
*/

inline constexpr auto pair = [](auto l, auto r) {
  return [l, r](auto p) { return p(l, r); };
};

inline constexpr auto fst = [](auto p) {
  return p([](auto l, auto r) { return l; });
};

inline constexpr auto snd = [](auto p) {
  return p([](auto l, auto r) { return r; });
};

} // namespace streams
} // namespace smd

#endif
