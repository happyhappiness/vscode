storeAppendPrintf(sentry, "sample_start_time = %d.%d (%s)\n",
                      (int)stats.sample_start_time.tv_sec,
                      (int)stats.sample_start_time.tv_usec,
                      mkrfc1123(stats.sample_start_time.tv_sec));