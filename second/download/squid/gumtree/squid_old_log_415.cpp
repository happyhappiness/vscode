storeAppendPrintf(sentry, "sample_start_time = %d.%d (%s)\n",
                      (int) l->timestamp.tv_sec,
                      (int) l->timestamp.tv_usec,
                      mkrfc1123(l->timestamp.tv_sec));