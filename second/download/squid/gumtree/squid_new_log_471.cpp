storeAppendPrintf(sentry, "sample_end_time = %d.%d (%s)\n",
                      (int)stats.sample_end_time.tv_sec,
                      (int)stats.sample_end_time.tv_usec,
                      mkrfc1123(stats.sample_end_time.tv_sec));