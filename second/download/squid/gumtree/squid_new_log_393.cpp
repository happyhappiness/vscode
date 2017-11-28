storeAppendPrintf(sentry, "\tmemPool accounted:     %6.0f KB %3.0f%%\n",
                          stats.mem_pool_allocated / 1024,
                          Math::doublePercent(stats.mem_pool_allocated, t));