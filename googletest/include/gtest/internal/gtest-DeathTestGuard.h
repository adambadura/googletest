#ifndef GTEST_INCLUDE_GTEST_INTERNAL_GTEST_DEATHTESTGUARD_H_
#define GTEST_INCLUDE_GTEST_INTERNAL_GTEST_DEATHTESTGUARD_H_

#include "gtest/internal/gtest-port.h"
#include <memory>

namespace testing {
namespace internal {

class DeathTestGuard;

GTEST_API_ std::shared_ptr<DeathTestGuard> CreateDeathTestGuard();

}  // namespace internal
}  // namespace testing

#endif  // GTEST_INCLUDE_GTEST_INTERNAL_GTEST_DEATHTESTGUARD_H_
