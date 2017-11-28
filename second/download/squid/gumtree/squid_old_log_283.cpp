storeAppendPrintf(sentry, "\tStorage Mem capacity:\t%4.1f%% used, %4.1f%% free\n",
                      Math::doublePercent(mem_node::InUseCount(), store_pages_max),
                      mFree);