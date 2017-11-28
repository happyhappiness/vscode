storeAppendPrintf(sentry, "\tMemory hits as %% of hit requests:\t5min: %3.1f%%, 60min: %3.1f%%\n",
                      stats.request_hit_mem_ratio5 / fct,
                      stats.request_hit_mem_ratio60 / fct);