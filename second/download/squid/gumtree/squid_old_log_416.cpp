storeAppendPrintf(sentry, "sample_end_time = %d.%d (%s)\n",
                      (int) f->timestamp.tv_sec,
                      (int) f->timestamp.tv_usec,
                      mkrfc1123(f->timestamp.tv_sec));