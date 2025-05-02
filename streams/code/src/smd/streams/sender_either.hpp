// sender_either.hpp                                                  -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#ifndef INCLUDED_CODE_SRC_SMD_STREAMS_SENDER_EITHER
#define INCLUDED_CODE_SRC_SMD_STREAMS_SENDER_EITHER

#include <beman/execution/execution.hpp>
#include <cassert>
#include <iostream>

namespace ex = beman::execution;

namespace smd {
namespace churchsender {

/*
  left   = λa.λl r.l a
  right  = λb.λl r.r b

  either = λl r.λe.e l r

 */

namespace senderEither {
inline constexpr auto left = [](int a) {
        return ex::let_value(
                [a](auto l, auto _) { return ex::just(a) | ex::then(l); });
};

inline constexpr auto right = [](int a) {
        return ex::let_value(
                [a](auto _, auto r) { return ex::just(a) | ex::then(r); });
};

inline constexpr auto isLeft = [](auto e) {
        return ex::just([](auto _) { return true; },
                        [](auto _) { return false; }) |
               e;
};

inline constexpr auto isRight = [](auto e) {
        return ex::just([](auto _) { return false; },
                        [](auto _) { return true; }) |
               e;
};

inline constexpr auto fromLeft = [](auto d, auto e) {
        return ex::just([](auto l) { return l; }, [d](auto r) { return d; }) |
               e;
};

inline constexpr auto fromRight = [](auto d, auto e) {
        return ex::just([d](auto l) { return d; }, [](auto r) { return r; }) |
               e;
};

inline constexpr auto either = [](auto l, auto r) {
        return ex::let_value([l, r](auto e) { return ex::just(l, r) | e; });
};

} // namespace senderEither
} // namespace churchsender
} // namespace smd

#endif
