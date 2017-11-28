storeAppendPrintf(sentry, "\tHits as %% of all requests:\t5min: %3.1f%%, 60min: %3.1f%%\n",
                      statRequestHitRatio(5),
                      statRequestHitRatio(60));