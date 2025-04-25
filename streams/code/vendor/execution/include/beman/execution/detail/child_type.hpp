// include/beman/execution/detail/child_type.hpp                    -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef INCLUDED_BEMAN_EXECUTION_DETAIL_CHILD_TYPE
#define INCLUDED_BEMAN_EXECUTION_DETAIL_CHILD_TYPE

#include <cstddef>
#include <type_traits>

// ----------------------------------------------------------------------------

namespace beman::execution::detail {
/*!
 * \brief Auxiliary type alias used to determine the type of a child sender.
 * \headerfile beman/execution/execution.hpp <beman/execution/execution.hpp>
 * \internal
 */
template <typename Sender, ::std::size_t I = 0u>
using child_type = decltype(::std::declval<Sender>().template get<I + 2>());
} // namespace beman::execution::detail

// ----------------------------------------------------------------------------

#endif
