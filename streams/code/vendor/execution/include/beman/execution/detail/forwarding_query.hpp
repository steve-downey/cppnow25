// include/beman/execution/detail/forwarding_query.hpp              -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef INCLUDED_BEMAN_EXECUTION_DETAIL_FORWARDING_QUERY
#define INCLUDED_BEMAN_EXECUTION_DETAIL_FORWARDING_QUERY

#include <beman/execution/detail/common.hpp>
#include <concepts>
#include <type_traits>
#include <utility>

// ----------------------------------------------------------------------------

namespace beman::execution::detail {
/*!
 * \brief Actual implementation of the forwarding_query customization point object
 * \headerfile beman/execution/execution.hpp <beman/execution/execution.hpp>
 * \internal
 */
struct forwarding_query_t {
    template <typename Object>
        requires requires(Object&& object, const forwarding_query_t& query) {
            { ::std::forward<Object>(object).query(query) } noexcept -> ::std::same_as<bool>;
        }
    constexpr auto operator()(Object&& object) const noexcept -> bool {
        return ::std::forward<Object>(object).query(*this);
    }
    template <typename Object>
    constexpr auto operator()(Object&&) const noexcept -> bool {
        return ::std::derived_from<::std::remove_cvref_t<Object>, ::beman::execution::detail::forwarding_query_t>;
    }
};
} // namespace beman::execution::detail

namespace beman::execution {
/*!
 * \brief Type of the forwarding_query customization point object
 * \headerfile beman/execution/execution.hpp <beman/execution/execution.hpp>
 */
using forwarding_query_t = beman::execution::detail::forwarding_query_t;
/*!
 * \brief The customizatoin point object to determine whether queries should be forwarded
 * \headerfile beman/execution/execution.hpp <beman/execution/execution.hpp>
 *
 * \details
 * The `constexpr` call `forwarding_query(q)` determines whether the query `q` passed
 * as argument should be forwarded. The result is determined as follows:
 *
 * * If the `q.query(forwarding_query)` is a `noexcept` expression of type `bool` the result of this call.
 * * If the type of `q` is derived from `forwarding_query_t`.
 * * `false` otherwise.
 */
inline constexpr forwarding_query_t forwarding_query{};
} // namespace beman::execution

// ----------------------------------------------------------------------------

#endif
