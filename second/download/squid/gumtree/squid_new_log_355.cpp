storeAppendPrintf(sentry, "\tHits as %% of bytes sent:\t5min: %3.1f%%, 60min: %3.1f%%\n",
                      stats.byte_hit_ratio5 / fct,
                      stats.byte_hit_ratio60 / fct);