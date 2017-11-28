storeAppendPrintf(sentry, "\tCache Hits:           %2d%%  %8.5f %8.5f\n",
                          (i + 1) * 5,
                          stats.cache_hits5[i] / fct,
                          stats.cache_hits60[i] / fct);