// include/beman/execution/detail/valid_completion_for.hpp          -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef INCLUDED_BEMAN_EXECUTION_DETAIL_VALID_COMPLETION_FOR
#define INCLUDED_BEMAN_EXECUTION_DETAIL_VALID_COMPLETION_FOR

#include <beman/execution/functional.hpp>
#include <beman/execution/detail/set_value.hpp>
#include <beman/execution/detail/set_error.hpp>
#include <beman/execution/detail/set_stopped.hpp>
#include <type_traits>

// ----------------------------------------------------------------------------

namespace beman::execution::detail {
template <typename, typename>
struct valid_completion_for_aux;

template <typename Rcvr, typename Tag, typename... Args>
struct valid_completion_for_aux<Rcvr, Tag (*)(Args...)> {
    static auto test(Tag (*)(Args...)) -> void
        requires ::beman::execution::detail::callable<Tag, ::std::remove_cvref_t<Rcvr>, Args...>
    {}
};

template <typename Signature, typename Rcvr>
concept valid_completion_for = requires(Signature* signature) {
#if 1
    valid_completion_for_aux<Rcvr, Signature*>::test(signature);
#else
    // This definition crashes some versions of clang.
    []<typename Tag, typename... Args>(Tag (*)(Args...))
        requires ::beman::execution::detail::callable<Tag, ::std::remove_cvref_t<Rcvr>, Args...>
    {}(signature);
#endif
};
} // namespace beman::execution::detail

// ----------------------------------------------------------------------------

#endif
