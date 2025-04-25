// include/beman/execution/detail/write_env.hpp                     -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef INCLUDED_BEMAN_EXECUTION_DETAIL_WRITE_ENV
#define INCLUDED_BEMAN_EXECUTION_DETAIL_WRITE_ENV

#include <beman/execution/detail/default_impls.hpp>
#include <beman/execution/detail/get_env.hpp>
#include <beman/execution/detail/impls_for.hpp>
#include <beman/execution/detail/join_env.hpp>
#include <beman/execution/detail/make_sender.hpp>
#include <beman/execution/detail/queryable.hpp>
#include <beman/execution/detail/sender.hpp>
#include <type_traits>
#include <utility>

// ----------------------------------------------------------------------------

namespace beman::execution::detail {
struct write_env_t {
    template <::beman::execution::sender Sender, ::beman::execution::detail::queryable Env>
    constexpr auto operator()(Sender&& sender, Env&& env) const {
        return ::beman::execution::detail::make_sender(
            *this, ::std::forward<Env>(env), ::std::forward<Sender>(sender));
    }
    static auto name() { return "write_env_t"; }
};

template <typename NewEnv, typename Child, typename Env>
struct completion_signatures_for_impl<
    ::beman::execution::detail::basic_sender<::beman::execution::detail::write_env_t, NewEnv, Child>,
    Env> {
    using type = decltype(::beman::execution::get_completion_signatures(
        ::std::declval<Child>(),
        ::beman::execution::detail::join_env(::std::declval<NewEnv>(), ::std::declval<Env>())));
};

template <>
struct impls_for<write_env_t> : ::beman::execution::detail::default_impls {
    static constexpr auto get_env = [](auto, const auto& state, const auto& receiver) noexcept {
        return ::beman::execution::detail::join_env(state, ::beman::execution::get_env(receiver));
    };
};

inline constexpr write_env_t write_env{};
} // namespace beman::execution::detail

// ----------------------------------------------------------------------------

#endif
