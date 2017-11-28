storeAppendPrintf(sentry, "\tDisk hits as %% of hit requests:\t5min: %3.1f%%, 60min: %3.1f%%\n",
                      stats.request_hit_disk_ratio5 / fct,
                      stats.request_hit_disk_ratio60 / fct);