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


// 85dedb42-2c9c-43d5-8157-edc8dbc1df34
inline constexpr auto pair = [](auto l, auto r) {
  return [l, r](auto p) { return p(l, r); };
};
// 85dedb42-2c9c-43d5-8157-edc8dbc1df34 end


// d7eb7f23-6f65-42c7-9814-9f85163d755f
inline constexpr auto fst = [](auto p) {
  return p([](auto l, auto r) { return l; });
};

inline constexpr auto snd = [](auto p) {
  return p([](auto l, auto r) { return r; });
};
// d7eb7f23-6f65-42c7-9814-9f85163d755f end

} // namespace streams
} // namespace smd

#endif
