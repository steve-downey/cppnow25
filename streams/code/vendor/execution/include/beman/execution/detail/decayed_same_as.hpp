// include/beman/execution/detail/decayed_same_as.hpp               -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef INCLUDED_BEMAN_EXECUTION_DETAIL_DECAYED_SAME_AS
#define INCLUDED_BEMAN_EXECUTION_DETAIL_DECAYED_SAME_AS

#include <concepts>

// ----------------------------------------------------------------------------

namespace beman::execution::detail {
//-dk:TODO thoroughly test the concept
/*!
 * \brief Helper concept to determine if the result of decaying two types results in the same type
 * \headerfile beman/execution/execution.hpp <beman/execution/execution.hpp>
 * \internal
 */
template <typename T0, typename T1>
concept decayed_same_as = ::std::same_as<::std::remove_cvref_t<T0>, ::std::remove_cvref_t<T1>>;
} // namespace beman::execution::detail

// ----------------------------------------------------------------------------

#endif
