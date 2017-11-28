storeAppendPrintf(sentry, "\tStorage Swap capacity:\t%4.1f%% used, %4.1f%% free\n",
                      Math::doublePercent(stats.store.swap.size, stats.store.swap.capacity),
                      Math::doublePercent(stats.store.swap.available(), stats.store.swap.capacity));