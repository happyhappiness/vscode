storeAppendPrintf(sentry, "\tCache Misses:         %2d%%  %8.5f %8.5f\n",
                          (i + 1) * 5,
                          stats.cache_misses5[i] / fct,
                          stats.cache_misses60[i] / fct);