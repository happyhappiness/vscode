storeAppendPrintf(sentry, "\tMemory hits as %% of hit requests:\t5min: %3.1f%%, 60min: %3.1f%%\n",
                      statRequestHitMemoryRatio(5),
                      statRequestHitMemoryRatio(60));