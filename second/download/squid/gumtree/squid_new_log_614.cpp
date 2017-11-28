storeAppendPrintf(sentry, "sample_time = %d.%d (%s)\n",
                      (int) stats.sample_time.tv_sec,
                      (int) stats.sample_time.tv_usec,
                      mkrfc1123(stats.sample_time.tv_sec));