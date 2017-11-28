storeAppendPrintf(sentry, "\tmemPool unaccounted:   %6.0f KB %3.0f%%\n",
                          (t - stats.mem_pool_allocated) / 1024,
                          Math::doublePercent(iFree, t));