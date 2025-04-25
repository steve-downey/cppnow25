// include/beman/execution/detail/sender.hpp                        -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef INCLUDED_BEMAN_EXECUTION_DETAIL_SENDER
#define INCLUDED_BEMAN_EXECUTION_DETAIL_SENDER

#include <beman/execution/detail/empty_env.hpp>
#include <beman/execution/detail/get_env.hpp>
#include <beman/execution/detail/queryable.hpp>
#include <beman/execution/detail/is_awaitable.hpp>
#include <beman/execution/detail/env_promise.hpp>
#include <concepts>
#include <type_traits>

// ----------------------------------------------------------------------------

namespace beman::execution {
struct sender_t {};
} // namespace beman::execution
namespace beman::execution::detail {
template <typename Sender>
concept is_sender = ::std::derived_from<typename Sender::sender_concept, ::beman::execution::sender_t>;

template <typename Sender>
concept enable_sender =
    ::beman::execution::detail::is_sender<Sender> ||
    ::beman::execution::detail::is_awaitable<Sender,
                                             ::beman::execution::detail::env_promise<::beman::execution::empty_env>>;
} // namespace beman::execution::detail
namespace beman::execution {
template <typename Sender>
concept sender = ::beman::execution::detail::enable_sender<::std::remove_cvref_t<Sender>> &&
                 requires(const ::std::remove_cvref_t<Sender>& sndr) {
                     { ::beman::execution::get_env(sndr) } -> ::beman::execution::detail::queryable;
                 } && ::std::move_constructible<::std::remove_cvref_t<Sender>> &&
                 ::std::constructible_from<::std::remove_cvref_t<Sender>, Sender>;
} // namespace beman::execution

// ----------------------------------------------------------------------------

#endif
