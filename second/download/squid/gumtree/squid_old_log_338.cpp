storeAppendPrintf(sentry, "\tNear Hits:            %2d%%  %8.5f %8.5f\n",
                          p,
                          statPctileSvc((double) p / 100.0, 5, PCTILE_NH) / 1000.0,
                          statPctileSvc((double) p / 100.0, 60, PCTILE_NH) / 1000.0);