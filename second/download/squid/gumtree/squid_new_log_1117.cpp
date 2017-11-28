storeAppendPrintf(s, "start %ld.%06d (%f seconds ago)\n",
                          (long int) http->al->cache.start_time.tv_sec,
                          (int) http->al->cache.start_time.tv_usec,
                          tvSubDsec(http->al->cache.start_time, current_time));