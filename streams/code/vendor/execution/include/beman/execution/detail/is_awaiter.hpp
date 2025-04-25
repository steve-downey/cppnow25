// include/beman/execution/detail/is_awaiter.hpp                    -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef INCLUDED_BEMAN_EXECUTION_DETAIL_IS_AWAITER
#define INCLUDED_BEMAN_EXECUTION_DETAIL_IS_AWAITER

#include <beman/execution/detail/await_suspend_result.hpp>
#include <coroutine>

// ----------------------------------------------------------------------------

namespace beman::execution::detail {
template <typename Awaiter, typename Promise>
concept is_awaiter = requires(Awaiter& awaiter, ::std::coroutine_handle<Promise> handle) {
    awaiter.await_ready() ? 1 : 0;
    { awaiter.await_suspend(handle) } -> ::beman::execution::detail::await_suspend_result;
    awaiter.await_resume();
};
} // namespace beman::execution::detail

// ----------------------------------------------------------------------------

#endif
