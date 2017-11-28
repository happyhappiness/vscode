storeAppendPrintf(sentry, "\tHits as %% of all requests:\t5min: %3.1f%%, 60min: %3.1f%%\n",
                      stats.request_hit_ratio5 / fct,
                      stats.request_hit_ratio60 / fct);