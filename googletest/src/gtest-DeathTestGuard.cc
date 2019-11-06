#include "gtest/internal/gtest-CoreRLimiter.h"

#include <sys/resource.h>
#include <cerrno>
#include <memory>

namespace testing {
namespace internal {

namespace {

static void logged_prlimit(const struct rlimit* new_limit,
                           struct rlimit* old_limit)
{
  const auto result = prlimit(0, RLIMIT_CORE, new_limit, old_limit);
  if (result != 0) {
    GTEST_LOG_(WARNING) << "prlimit failed with " << result
                        << " and errno " << errno
                        << " while setting rlim_cur=" << new_limit->rlim_cur
                        << " and rlim_max=" << new_limit->rlim_max;
  }
}

}  // namespace

class DeathTestGuard
{
public:
  DeathTestGuard()
  {
    const struct rlimit new_limit{0, 0};
    logged_prlimit(&new_limit, &old_limit);
  }

  ~DeathTestGuard();
  {
    logged_prlimit(&old_limit, nullptr);
  }

  DeathTestGuard(DeathTestGuard&&) = delete;
  DeathTestGuard& operator =(DeathTestGuard&&) = delete;

  DeathTestGuard(const DeathTestGuard&) = delete;
  DeathTestGuard& operator =(const DeathTestGuard&) = delete;

private:
  struct rlimit old_limit{0, 0};
};

GTEST_API_ std::shared_ptr<DeathTestGuard> CreateDeathTestGuard()
{
  return std::make_shared<DeathTestGuard>();
}

}  // namespace internal
}  // namespace testing
