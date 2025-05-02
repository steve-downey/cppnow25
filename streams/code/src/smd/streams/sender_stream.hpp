// sender_stream.hpp                                                  -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#ifndef INCLUDED_CODE_SRC_SMD_STREAMS_SENDER_STREAM
#define INCLUDED_CODE_SRC_SMD_STREAMS_SENDER_STREAM

#include <beman/execution/execution.hpp>

namespace smd {
namespace churchsender {
namespace senderStream {
namespace ex = beman::execution;

// STREAM co-inductively
/*
  StrA := ∃α . α × (α → A × α)

  data Stream a = S a (Stream a)

  hd (S a as) = a
  tl (S a as) = as

  S = λ a as . λ s . s a as
  hd = λ s . s λ a as . a
  tl = λ s . s λ a as . as
*/

inline constexpr auto hd = [](auto s) {
        // return s([](auto a, auto as) { return a; });
        return ex::just([](auto a, auto as) { return a; }) | s;
};

inline constexpr auto tl = [](auto s) {
        // return s([](auto a, auto as) { return as; });
        return ex::just([](auto a, auto as) { return as; }) | s;
};

inline constexpr auto S = [](auto a, auto as) {
        // return [a, as](auto s) { return s(a, as); };
        return ex::let_value(
                [a, as](auto s) { return ex::just(a, as) | ex::then(s); });
};

inline constexpr auto constStream = [](auto k) {
        // return [k](this const auto &self, auto s) { return s(k, self); };
        return ex::let_value([k](this const auto &self, auto s) {
                return ex::just(self) | ex::then(s);
        });
};
} // namespace senderStream
} // namespace churchsender
} // namespace smd

#endif
