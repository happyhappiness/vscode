storeAppendPrintf(sentry, "\tCache Hits:           %2d%%  %8.5f %8.5f\n",
                          p,
                          statPctileSvc((double) p / 100.0, 5, PCTILE_HIT) / 1000.0,
                          statPctileSvc((double) p / 100.0, 60, PCTILE_HIT) / 1000.0);