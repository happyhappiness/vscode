storeAppendPrintf(sentry, "\tNear Hits:            %2d%%  %8.5f %8.5f\n",
                          (i + 1) * 5,
                          stats.near_hits5[i] / fct,
                          stats.near_hits60[i] / fct);