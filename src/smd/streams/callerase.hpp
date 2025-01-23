// smd/streams/callerase.hpp                                          -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef INCLUDED_SMD_STREAMS_CALLERASE
#define INCLUDED_SMD_STREAMS_CALLERASE

#include <memory>

namespace smd {
namespace streams {

template <typename> struct callerase;

template <typename R, typename... Args> struct callerase<R(Args...)> {
  template <typename Callable>
  constexpr callerase(Callable callable)
      : ptr{std::make_unique<implementation<Callable>>(callable)} {}

  constexpr auto operator()(Args... args) const -> R { return (*ptr)(args...); }

private:
  struct interface {
    constexpr virtual auto operator()(Args...) -> R = 0;
    constexpr virtual ~interface() = default;
  };

  template <typename Callable> struct implementation final : interface {
    constexpr explicit(true) implementation(Callable callable)
        : callable{callable} {}
    constexpr auto operator()(Args... args) -> R override {
      return callable(args...);
    }

  private:
    Callable callable;
  };

  std::unique_ptr<interface> ptr;
};

// https://en.cppreference.com/w/cpp/utility/functional/function/deduction_guides

template <class> struct callerase_traits {};

template <class R, class G, class... A>
struct callerase_traits<R (G::*)(A...) const> {
  using callerase_type = R(A...);
};

template <class Callable>
using callerase_type_t = typename callerase_traits<Callable>::callerase_type;

// This overload participates in overload resolution only if
// &Callable::operator() is well-formed when treated as an unevaluated operand
// and decltype(&Callable::operator()) is of the form R(G::*)(A...)
// (optionally cv-qualified, optionally noexcept, optionally lvalue reference
// qualified). The deduced type is std::function<R(A...)>.
template <typename Callable>
callerase(Callable)
    -> callerase<callerase_type_t<decltype(&Callable::operator())>>;

} // namespace streams
} // namespace smd

#endif
