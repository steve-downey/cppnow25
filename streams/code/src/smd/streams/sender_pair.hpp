// sender_pair.hpp                                                    -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#ifndef INCLUDED_CODE_SRC_SMD_STREAMS_SENDER_PAIR
#define INCLUDED_CODE_SRC_SMD_STREAMS_SENDER_PAIR

#include <beman/execution/execution.hpp>
#include <cassert>
#include <iostream>

namespace ex = beman::execution;

namespace smd {
namespace churchsender {

/*
  pair = λl r p. p l r
  fst = λp. p (λl r. l)
  snd = λp. p (λl r. r)
*/

namespace senderPair {

inline constexpr auto pair = [](auto l, auto r) {
        // return [l, r](auto p) { return p(l, r); };
        return ex::let_value(
                [l, r](auto p) { return ex::just(l, r) | ex::then(p); });
};

inline constexpr auto fst = [](auto p) {
        // return p([](auto l, auto r) { return l; });
        return ex::just([](auto l, auto r) { return l; }) | p;
};

inline constexpr auto snd = [](auto p) {
        // return p([](auto l, auto r) { return r; });
        return ex::just([](auto l, auto r) { return r; }) | p;
};
} // namespace senderPair
} // namespace churchsender
} // namespace smd

#endif
