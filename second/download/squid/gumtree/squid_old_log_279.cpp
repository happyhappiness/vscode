storeAppendPrintf(sentry, "\tDisk hits as %% of hit requests:\t5min: %3.1f%%, 60min: %3.1f%%\n",
                      statRequestHitDiskRatio(5),
                      statRequestHitDiskRatio(60));