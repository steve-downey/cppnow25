// include/beman/execution/detail/emplace_from.hpp                  -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef INCLUDED_BEMAN_EXECUTION_DETAIL_EMPLACE_FROM
#define INCLUDED_BEMAN_EXECUTION_DETAIL_EMPLACE_FROM

#include <beman/execution/detail/call_result_t.hpp>
#include <beman/execution/detail/nothrow_callable.hpp>
#include <type_traits>
#include <utility>

// ----------------------------------------------------------------------------

namespace beman::execution::detail {
/*!
 * \brief Helper class to get the result of a function which may be only called once.
 * \headerfile beman/execution/execution.hpp <beman/execution/execution.hpp>
 * \internal
 */
template <typename Fun>
struct emplace_from {
    using type = ::beman::execution::detail::call_result_t<Fun>;
    Fun fun;

    explicit constexpr operator type() && noexcept(::beman::execution::detail::nothrow_callable<Fun>) {
        return ::std::move(fun)();
    }
};
template <typename Fun>
emplace_from(Fun&&) -> emplace_from<::std::remove_cvref_t<Fun>>;
} // namespace beman::execution::detail

// ----------------------------------------------------------------------------

#endif
