storeAppendPrintf(sentry, "\tStorage Mem capacity:\t%4.1f%% used, %4.1f%% free\n",
                      Math::doublePercent(stats.store.mem.size, stats.store.mem.capacity),
                      Math::doublePercent(stats.store.mem.available(), stats.store.mem.capacity));