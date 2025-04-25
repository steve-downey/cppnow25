// include/beman/execution/detail/valid_specialization.hpp          -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef INCLUDED_BEMAN_EXECUTION_DETAIL_VALID_SPECIALIZATION
#define INCLUDED_BEMAN_EXECUTION_DETAIL_VALID_SPECIALIZATION

// ----------------------------------------------------------------------------

namespace beman::execution::detail {
template <template <typename...> class T, typename... Args>
concept valid_specialization = requires { typename T<Args...>; };
} // namespace beman::execution::detail

// ----------------------------------------------------------------------------

#endif
