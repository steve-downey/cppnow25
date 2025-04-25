// include/beman/execution/detail/decays_to.hpp                     -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef INCLUDED_BEMAN_EXECUTION_DETAIL_DECAYS_TO
#define INCLUDED_BEMAN_EXECUTION_DETAIL_DECAYS_TO

#include <concepts>
#include <type_traits>

// ----------------------------------------------------------------------------

namespace beman::execution::detail {
/*!
 * \brief Helper concept to determine if the first argument decays to the second argument
 * \headerfile beman/execution/execution.hpp <beman/execution/execution.hpp>
 * \internal
 */
template <typename From, typename To>
concept decays_to = ::std::same_as<::std::decay_t<From>, To>;
} // namespace beman::execution::detail

// ----------------------------------------------------------------------------

#endif
