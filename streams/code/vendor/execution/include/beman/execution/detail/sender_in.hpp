// include/beman/execution/detail/sender_in.hpp                     -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef INCLUDED_BEMAN_EXECUTION_DETAIL_SENDER_IN
#define INCLUDED_BEMAN_EXECUTION_DETAIL_SENDER_IN

#include <beman/execution/detail/empty_env.hpp>
#include <beman/execution/detail/get_completion_signatures.hpp>
#include <beman/execution/detail/queryable.hpp>
#include <beman/execution/detail/sender.hpp>
#include <beman/execution/detail/valid_completion_signatures.hpp>

// ----------------------------------------------------------------------------

namespace beman::execution {
template <typename Sender, typename Env = ::beman::execution::empty_env>
concept sender_in =
    ::beman::execution::sender<Sender> && ::beman::execution::detail::queryable<Env> &&
    requires(Sender&& sender, Env&& env) {
        {
            ::beman::execution::get_completion_signatures(::std::forward<Sender>(sender), ::std::forward<Env>(env))
        } -> ::beman::execution::detail::valid_completion_signatures;
    };
} // namespace beman::execution

// ----------------------------------------------------------------------------

#endif
