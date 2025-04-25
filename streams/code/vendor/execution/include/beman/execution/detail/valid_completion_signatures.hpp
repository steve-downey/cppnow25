// include/beman/execution/detail/valid_completion_signatures.hpp   -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef INCLUDED_BEMAN_EXECUTION_DETAIL_VALID_COMPLETION_SIGNATURES
#define INCLUDED_BEMAN_EXECUTION_DETAIL_VALID_COMPLETION_SIGNATURES

#include <beman/execution/detail/completion_signatures.hpp>
#include <type_traits>

// ----------------------------------------------------------------------------

namespace beman::execution::detail {
template <typename>
struct valid_completion_signatures_helper : ::std::false_type {};
template <typename... Sigs>
struct valid_completion_signatures_helper<::beman::execution::completion_signatures<Sigs...>> : ::std::true_type {};

template <typename Signatures>
concept valid_completion_signatures = valid_completion_signatures_helper<Signatures>::value;
} // namespace beman::execution::detail

// ----------------------------------------------------------------------------

#endif
