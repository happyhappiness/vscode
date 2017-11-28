storeAppendPrintf(sentry, "\tHits as %% of bytes sent:\t5min: %3.1f%%, 60min: %3.1f%%\n",
                      statByteHitRatio(5),
                      statByteHitRatio(60));