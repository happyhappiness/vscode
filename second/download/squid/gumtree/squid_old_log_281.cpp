storeAppendPrintf(sentry, "\tStorage Swap capacity:\t%4.1f%% used, %4.1f%% free\n",
                      Math::doublePercent(store_swap_size, Store::Root().maxSize()),
                      Math::doublePercent((Store::Root().maxSize() - store_swap_size), Store::Root().maxSize()));